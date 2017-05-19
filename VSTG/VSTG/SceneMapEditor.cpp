#include "SceneMapEditor.h"
#include "Essential.hpp"
#include "Enemy.hpp"

#include "nfd.h"

#include <regex>
#include <fstream>

SceneMapEditor::SceneMapEditor() : 
	isExit(false), isDrag(false), isMouseLeft(false), isFocused(true), isMenuTriger(false),
	objectEraser(eraseSize), objectBrush(brushSize),
	timeAtBottom(0.0f), timeScale(100.0f),
	dragObject(NULL),
	escMenu(sf::IntRect(50, 80, 206, 139), Essential::textManager.getText(4), ObjMenu::MENUFLAG::YES_NO)
{
	objectEraser.setOrigin(eraseSize, eraseSize);
	objectEraser.setOutlineColor(sf::Color::White);
	objectEraser.setFillColor(sf::Color::Transparent);
	objectEraser.setOutlineThickness(0.0f);

	objectBrush.setOrigin(5.0f, 5.0f);
	objectBrush.setFillColor(sf::Color(255, 0, 0, 100));
}

Essential::GameState SceneMapEditor::Run()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	sf::Event event;

	while (Essential::wnd.isOpen() && !isExit) {
		while (Essential::wnd.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseWheelScrolled:
				timeAtBottom += scrollSpeed * event.mouseWheelScroll.delta;
				timeAtBottom = timeAtBottom < 0 ? 0.0f : timeAtBottom;
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::W:
					WriteToFile();
					break;
				case sf::Keyboard::M:
					MergeFromFile();
					break;
				case sf::Keyboard::Q:
				case sf::Keyboard::Escape:
					isMenuTriger = !isMenuTriger;
					break;
				default:
					break;
				}
				break;
			case sf::Event::LostFocus:
				isFocused = false;
				break;
			case sf::Event::GainedFocus:
				isFocused = true;
				break;
			default:
				Essential::defHandleMsg(event);
			}
		}
		if (isFocused) {
			if (!isMenuTriger) {
				Update();
			} else {
				const int rc = escMenu.MenuUpdate();
				if (rc == 1) // 1 for first button
					isExit = true;
				else if (rc == 2) // 2 for second button
					isMenuTriger = false;
			}
		}
		DrawScene();
	}

	return Essential::GameState::POP;
}

void SceneMapEditor::DrawScene()
{
	// Drawing
	Essential::wnd.clear();
	// draw time line
	for (float i = timeScale - int(timeAtBottom) % int(timeScale); i < Essential::ScreenHeight; i += timeScale) {
		DrawLine(Essential::wnd, Essential::ScreenHeight - i);
	}
	// draw Shape
	for (auto pShape : sortedpShapes) {
		sf::Vector2f vec = pShape->getPosition();
		// Change Position accoridng timeAxis
		vec.y += timeAtBottom;
		sf::CircleShape shape(*pShape);
		shape.setPosition(vec);
		Essential::wnd.draw(shape);
	}

	// draw tool
	Essential::wnd.draw(objectEraser);
	Essential::wnd.draw(objectBrush);

	// draw menu
	if (isMenuTriger)
		escMenu.Draw(Essential::wnd);

	Essential::wnd.display();
}

bool SceneMapEditor::MergeFromFile(const std::string filepath)
{
	std::ifstream infile;
	std::string line;
	std::regex rgx("(\\d*\\.\\d*),\\s*(-?\\d*\\.\\d*)");
	std::smatch match;
	sf::Vector2f vec;
	try{
		infile.open(filepath);		
		while (std::getline(infile, line)) {
			const std::string s(line);
			if (std::regex_search(s.begin(), s.end(), match, rgx)) {
				vec.x = std::stof(match[1]);
//				vec.y = std::stof(match[2]) * timeScale;
				vec.y = time2dim(std::stof(match[2]));

				// Insert Object
				sf::CircleShape *pShape = new sf::CircleShape(objectBrush);
				pShape->setPosition(vec);
				sortedpShapes.insert(pShape);
			}
		}
		infile.close();
	}
	catch (const std::ifstream::failure &e) {
		std::cout << "Exception opening/reading file." << std::endl;
	}
	return false;
}

bool SceneMapEditor::MergeFromFile()
{
	//NFD
	nfdchar_t *outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("tmap", NULL, &outPath);

	bool rc = false;
	if (result == NFD_OKAY)
	{
		rc = MergeFromFile(outPath);
		free(outPath);
	}
	else if (result == NFD_CANCEL)
	{
		puts("User pressed cancel.");
	}
	else
	{
		printf("Error: %s\n", NFD_GetError());
	}

	return rc;
}

bool SceneMapEditor::WriteToFile(const std::string filepath)
{
	std::ofstream outfile;
	try {
		using namespace std;
		ofstream outfile;
		outfile.open(filepath, ofstream::out);
		char str[1024];
		for (auto shape : sortedpShapes) {
			sf::Vector2f vec = shape->getPosition();
//			vec.y = vec.y / timeScale;
			vec.y = dim2time(vec.y);
			sprintf_s(str, "%f,%f", vec.x, vec.y);
			outfile << str << endl;
		}
		outfile.close();
	}
	catch (const std::ifstream::failure &e) {
		std::cout << "Exception opening/reading file." << std::endl;
		return false;
	}
	return true;
}

bool SceneMapEditor::WriteToFile()
{
	//NFD
	nfdchar_t *outPath = NULL;
	nfdresult_t result = NFD_SaveDialog("tmap", NULL, &outPath);

	bool rc = false;
	if (result == NFD_OKAY)
	{
		rc = WriteToFile(outPath);
		free(outPath);
	}
	else if (result == NFD_CANCEL)
	{
		puts("User pressed cancel.");
	}
	else
	{
		printf("Error: %s\n", NFD_GetError());
	}

	return rc;
}

void SceneMapEditor::Update()
{
	//Handle input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!isMouseLeft) {
			// Find object around for drag
			for (auto it = sortedpShapes.begin(); it != sortedpShapes.end(); it++) {
				sf::Vector2f mpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
				mpos.y -= timeAtBottom;
				const sf::Vector2f spos = (*it)->getPosition();
				const sf::Vector2f fDist = spos - mpos;
				const float sqlen = fDist.x*fDist.x + fDist.y*fDist.y;
				const float olen = (*it)->getRadius();
				if (sqlen < olen * olen) {
					dragObject = *it;
					break;
				}
			}
			if (dragObject)
				sortedpShapes.erase(dragObject); // Remove and insert later to ensure sorted set
		}
		else {
			if (dragObject) {
				// Drag
				sf::Vector2f vec = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
				vec.y -= timeAtBottom;
				dragObject->setPosition(vec);
			}
		}
		isMouseLeft = true;
	}
	else if (isMouseLeft == true) {
		if (dragObject) {
			sortedpShapes.insert(dragObject); // Remove and insert back to ensure sorted set
		}
		else {
			// Add Object
			sf::Vector2f vec = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
			if (vec.x >= 0 && vec.x < Essential::ScreenWidth &&
				vec.y >= 0 && vec.y < Essential::ScreenHeight) { // Mouse in Screen
				vec.y -= timeAtBottom;
				objectBrush.setPosition(vec);
				sortedpShapes.insert(new sf::CircleShape(objectBrush));
			}
		}
		dragObject = NULL;
		isMouseLeft = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		objectEraser.setOutlineThickness(1.0f);
		{ // Avoid situation both key are pressed
			isMouseLeft = false;
			if (dragObject) {
				sortedpShapes.insert(dragObject);
			}
			dragObject = NULL;
		}
		for (auto it = sortedpShapes.begin(); it != sortedpShapes.end(); it++) {
			sf::Vector2f mpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
			mpos.y -= timeAtBottom;
			const sf::Vector2f spos = (*it)->getPosition();
			const sf::Vector2f fDist = spos - mpos;
			float sqlen = fDist.x*fDist.x + fDist.y*fDist.y;
			if (sqlen < eraseSize*eraseSize) {
				lShapeDel.push_back(*it);
			}
		}
	}
	else {
		objectEraser.setOutlineThickness(0.0f);
	}

	// Update element pos
	objectEraser.setPosition(Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd)));
	objectBrush.setPosition(Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd)));

	//Remove Shape
	for (auto it = lShapeDel.begin(); it != lShapeDel.end(); it++) {
		sortedpShapes.erase(*it);
		delete *it;
	}
	lShapeDel.clear();

	// Debug Log
	system("CLS");
	std::cout << sortedpShapes.size() << std::endl;
	if (isFocused) {
		std::cout << "Focused" << std::endl;
	}
	else {
		std::cout << "Lost" << std::endl;
	}


}

void SceneMapEditor::DrawLine(sf::RenderTarget & gfx, const float y)
{
	const sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(0.0f, y)),
		sf::Vertex(sf::Vector2f(float(Essential::ScreenWidth), y))
	};
	gfx.draw(line, 2, sf::LineStrip);
}

float SceneMapEditor::time2dim(const float & time)
{
	return -(time * timeScale) + Essential::ScreenHeight;
}

float SceneMapEditor::dim2time(const float & dim)
{
	return -(dim - Essential::ScreenHeight) / timeScale;
}



