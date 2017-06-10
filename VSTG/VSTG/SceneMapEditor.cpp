#include "SceneMapEditor.h"
#include "Essential.hpp"
#include "ObjEnemy.hpp"
#include "ObjCreator.h"

#include "nfd.h"

#include <regex>
#include <fstream>
#include <string>

SceneMapEditor::SceneMapEditor() : 
	isExit(false), isDrag(false), isMouseLeft(false), isFocused(true), isMenuTriger(false),
	objectEraser(eraseSize),
	timeAtBottom(0.0f), timeScale(100.0f),
	dragObject(NULL),
	typeIdx(0),
	escMenu(sf::IntRect(50, 80, 206, 139), Essential::textManager.getText(4), ObjMenu::MENUFLAG::YES_NO)
{
	objectEraser.setOrigin(eraseSize, eraseSize);
	objectEraser.setOutlineColor(sf::Color::White);
	objectEraser.setFillColor(sf::Color::Transparent);
	objectEraser.setOutlineThickness(0.0f);

//	pTexBuffer = Essential::assetManager.GetTexture("Resources/Textures/rock.png");
//	objectBrush.setTexture(*pTexBuffer);
//	objectBrush.setOrigin(200.0f, 200.0f);
//	spriteScale = 0.1f;
//	objectBrush.setScale(sf::Vector2f(spriteScale,spriteScale));
//	objectBrush.setFillColor(sf::Color(255, 0, 0, 100));
	objectBrush = ObjCreator::CreateEnemy(ObjCreator::EnemyType(typeIdx), sf::Vector2f(0.0f, 0.0f));

	paintboard.setPosition(sf::Vector2f(float(Essential::GameCanvas.left), float(Essential::GameCanvas.top)));
	paintboard.setSize(sf::Vector2f(float(Essential::GameCanvas.width), float(Essential::GameCanvas.height)));
	paintboard.setFillColor(sf::Color(100,100,100));

	// Menu Context
	Button::SettingDefaultButton(butPrev, Essential::textManager.getText(9), Button::SMALL);
	butPrev.setPosition(sf::Vector2f(550.0f, 250.0f));
	Button::SettingDefaultButton(butNext, Essential::textManager.getText(10), Button::SMALL);
	butNext.setPosition(sf::Vector2f(680.0f, 250.0f));
	Button::SettingDefaultButton(butWrite, Essential::textManager.getText(11), Button::SMALL);
	butWrite.setPosition(sf::Vector2f(550.0f, 300.0f));
	Button::SettingDefaultButton(butMerge, Essential::textManager.getText(12), Button::SMALL);
	butMerge.setPosition(sf::Vector2f(680.0f, 300.0f));
	Button::SettingDefaultButton(butClear, Essential::textManager.getText(13), Button::SMALL);
	butClear.setPosition(sf::Vector2f(550.0f, 350.0f));
	Button::SettingDefaultButton(butExit, Essential::textManager.getText(14), Button::SMALL);
	butExit.setPosition(sf::Vector2f(680.0f, 350.0f));

	spritePreview = ObjCreator::CreateEnemy(ObjCreator::EnemyType(typeIdx), sf::Vector2f(previewXPos, previewYPos));
	spritePreview->FixedUpdate(0.0f);

	textPreview.setString(spritePreview->GetName());
	textPreview.setFont(Essential::textFont);
	textPreview.setPosition(sf::Vector2f(610.0f, 50.0f));

	textPos.setString("xPos: " + std::to_string(0.0f));
	textPos.setFont(Essential::textFont);
	textPos.setPosition(sf::Vector2f(530.0f, 130.0f));

	textTime.setString("time: " + std::to_string(0.0f));
	textTime.setFont(Essential::textFont);
	textTime.setPosition(sf::Vector2f(530.0f, 170.0f));
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
			case sf::Event::KeyReleased:
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
				case sf::Keyboard::Left:
					objScrollLeft();
					break;
				case sf::Keyboard::Right:
					objeScrollRight();
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

		// Update Button
		butPrev.Update();
		butNext.Update();
		butWrite.Update();
		butMerge.Update();
		butClear.Update();
		butExit.Update();

		// Handle Button
		if (butPrev.getStatus() == Button::Release) {
			objScrollLeft();
		}
		if (butNext.getStatus() == Button::Release) {
			objeScrollRight();
		}
		if (butWrite.getStatus() == Button::Release) {
			WriteToFile();
		}
		if (butMerge.getStatus() == Button::Release) {
			MergeFromFile();
		}
		if (butClear.getStatus() == Button::Release) {
			sortedpObject.clear();
		}
		if (butExit.getStatus() == Button::Release) {
			isMenuTriger = !isMenuTriger;
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

	// draw paintboard background
	Essential::wnd.draw(paintboard);

	// draw time line with offset of canvas's top only hold true when canvas is in the middle
	for (float i = timeScale - int(timeAtBottom) % int(timeScale); 
		i < Essential::GameCanvas.height + Essential::GameCanvas.top; i += timeScale) {
		DrawLine(Essential::wnd, Essential::GameCanvas.height + Essential::GameCanvas.top - i);
	}

	// draw Objects
	for (auto pObject : sortedpObject) {
		sf::Vector2f vec = pObject->getPosition();
		// Change Position accoridng timeAxis
		vec.y += timeAtBottom;

		// Draw if in paintboard
		if (inPaintboard(vec)) {
//			sf::Sprite sprite(pObject->GetSprite());
//			sprite.setPosition(vec);
//			Essential::wnd.draw(sprite);
			sf::Sprite sprite(*pObject->GetSprite());
			sprite.setPosition(vec);
			Essential::wnd.draw(sprite);
//			pObject->Draw(Essential::wnd);
		}
	}

	// draw tool
	Essential::wnd.draw(objectEraser);
//	Essential::wnd.draw(objectBrush);
	objectBrush->Draw(Essential::wnd);

	// draw menu
	if (isMenuTriger)
		escMenu.Draw(Essential::wnd);

	// draw buttons
	butPrev.Draw(Essential::wnd); 
	butNext.Draw(Essential::wnd);
	butWrite.Draw(Essential::wnd);
	butMerge.Draw(Essential::wnd);
	butClear.Draw(Essential::wnd);
	butExit.Draw(Essential::wnd);

	spritePreview->Draw(Essential::wnd);
	Essential::wnd.draw(textPreview);
	Essential::wnd.draw(textPos);
	Essential::wnd.draw(textTime);

	Essential::wnd.display();
}

bool SceneMapEditor::MergeFromFile(const std::string filepath)
{
	std::ifstream infile;
	std::string line;
	std::regex rgx("(\\d*\\.\\d*),\\s*(-?\\d*\\.\\d*),\\s*(\\d*)");
	std::smatch match;
	sf::Vector2f vec;
	try{
		infile.open(filepath);		
		while (std::getline(infile, line)) {
			const std::string s(line);
			if (std::regex_search(s.begin(), s.end(), match, rgx)) {
				
				// Get Pos
				vec.x = std::stof(match[1]);
				vec.y = std::stof(match[2]);
				
				// Pos Tranform
				vec.y = time2dim(vec.y);
				vec = offsetToCanvas(vec);
				
				// Get ObjectID
				const ObjCreator::EnemyType OID = ObjCreator::EnemyType(std::stoul(match[3]));

				// Insert Object
				if (OID < ObjCreator::COUNT && OID >= 0) {
					std::shared_ptr<ObjCharacter> pObject = ObjCreator::CreateEnemy(OID, vec);
					pObject->FixedUpdate(0.0f);
					sortedpObject.insert(pObject);
				}
			}
		}
		infile.close();
	}
	catch (...) {
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
		for (auto pObject : sortedpObject) {
			sf::Vector2f vec = pObject->getPosition();
			
			// Pos Transform
			vec = offsetOutCanvas(vec);
			vec.y = dim2time(vec.y);
			
			// Write
			sprintf_s(str, "%f,%f,%zu", vec.x, vec.y, pObject->GetOID());
			outfile << str << endl;
		}
		outfile.close();
	}
	catch (...) {
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
	// Get MousePosition which used frequently
	// Also transform the position according to the window scale
	sf::Vector2f mpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
	mpos /= Essential::windowScale;

	// if mouse inside the paintboard
	if (inPaintboard(mpos)) {
		// Update Menu
		textPos.setString("xPos: " + std::to_string(mpos.x - Essential::GameCanvas.left));
		float time = Essential::GameCanvas.top + Essential::GameCanvas.height - mpos.y + timeAtBottom;
		time /= timeScale;
		textTime.setString("time: " + std::to_string(time));

		//Handle input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!isMouseLeft) {
				// Find object around for drag
				for (auto it = sortedpObject.begin(); it != sortedpObject.end(); it++) {
					sf::Vector2f pos = mpos;
					pos.y -= timeAtBottom;
					const sf::Vector2f spos = (*it)->getPosition();
					const sf::Vector2f fDist = spos - pos;
					const float sqlen = fDist.x*fDist.x + fDist.y*fDist.y;

					const float olen = (*it)->GetColliderSize();
					if (sqlen < olen * olen) {
						dragObject = *it;
						break;
					}
				}
				if (dragObject)
					sortedpObject.erase(dragObject); // Remove and insert later to ensure sorted set
			}
			else {
				if (dragObject) {
					// Drag
					sf::Vector2f pos = mpos;
					pos.y -= timeAtBottom;
					dragObject->setPosition(pos);
				}
			}
			isMouseLeft = true;
		}
		else if (isMouseLeft == true) {
			if (dragObject) {
				sortedpObject.insert(dragObject); // Remove and insert back to ensure sorted set
			}
			else {
				// Add Object
				sf::Vector2f pos = mpos;
				if (pos.x >= 0 && pos.x < Essential::ScreenWidth &&
					pos.y >= 0 && pos.y < Essential::ScreenHeight) { // Mouse in Screen
					pos.y -= timeAtBottom;
					objectBrush->setPosition(pos);
					int tmp = ObjCreator::EnemyType(objectBrush->GetOID());
					std::shared_ptr<ObjEnemy> pObject =
						ObjCreator::CreateEnemy(ObjCreator::EnemyType(objectBrush->GetOID()), objectBrush->getPosition());
					pObject->FixedUpdate(0.0f); // Update Sprite pos
					sortedpObject.insert(pObject);
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
					sortedpObject.insert(dragObject);
				}
				dragObject = NULL;
			}
			for (auto it = sortedpObject.begin(); it != sortedpObject.end(); it++) {
				sf::Vector2f pos = mpos;
				pos.y -= timeAtBottom;
				const sf::Vector2f spos = (*it)->getPosition();
				const sf::Vector2f fDist = spos - pos;
				float sqlen = fDist.x*fDist.x + fDist.y*fDist.y;
				if (sqlen < eraseSize*eraseSize) {
					lObjectDel.push_back(*it);
				}
			}
		}
		else {
			objectEraser.setOutlineThickness(0.0f);
		}

		// Update element pos
		objectEraser.setPosition(mpos);
		objectBrush->setPosition(mpos);
		objectBrush->FixedUpdate(0.0f);
	}

	//Remove Sprite
	for (auto it = lObjectDel.begin(); it != lObjectDel.end(); it++) {
		sortedpObject.erase(*it);
	}
	lObjectDel.clear();

	// Debug Log
	system("CLS");
	std::cout << sortedpObject.size() << std::endl;
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
		sf::Vertex(sf::Vector2f(float(Essential::GameCanvas.left), y)),
		sf::Vertex(sf::Vector2f(float(Essential::GameCanvas.left + Essential::GameCanvas.width), y))
	};
	gfx.draw(line, 2, sf::LineStrip);
}

inline float SceneMapEditor::time2dim(const float & time) const
{
	return -(time * timeScale) + Essential::GameCanvas.height;
}

inline float SceneMapEditor::dim2time(const float & dim) const
{
	return -(dim - Essential::GameCanvas.height) / timeScale;
}

inline sf::Vector2f SceneMapEditor::offsetToCanvas(const sf::Vector2f & vec) const
{
	return vec + Essential::vec2i2f(Essential::GameCanvas.left, Essential::GameCanvas.top);
}

inline sf::Vector2f SceneMapEditor::offsetOutCanvas(const sf::Vector2f & vec) const
{
	return vec - Essential::vec2i2f(Essential::GameCanvas.left, Essential::GameCanvas.top);
}

inline bool SceneMapEditor::inPaintboard(const sf::Vector2f & pos) const
{
	sf::Vector2f topLeft = Essential::vec2i2f(Essential::GameCanvas.left, Essential::GameCanvas.top);
	sf::Vector2f botRight = topLeft + Essential::vec2i2f(Essential::GameCanvas.width, Essential::GameCanvas.height);
	return pos.x >= topLeft.x && pos.y >= topLeft.y && pos.x < botRight.x && pos.y < botRight.y;
}

inline void SceneMapEditor::objScrollLeft()
{
	typeIdx = (typeIdx + ObjCreator::COUNT - 1) % ObjCreator::COUNT;
	objectBrush = ObjCreator::CreateEnemy(ObjCreator::EnemyType(typeIdx), objectBrush->getPosition());
	spritePreview = ObjCreator::CreateEnemy(ObjCreator::EnemyType(typeIdx), sf::Vector2f(previewXPos, previewYPos));
	spritePreview->FixedUpdate(0.0f);
	textPreview.setString(spritePreview->GetName());
}

inline void SceneMapEditor::objeScrollRight()
{
	typeIdx = (typeIdx + 1) % ObjCreator::COUNT;
	objectBrush = ObjCreator::CreateEnemy(ObjCreator::EnemyType(typeIdx), objectBrush->getPosition());
	spritePreview = ObjCreator::CreateEnemy(ObjCreator::EnemyType(typeIdx), sf::Vector2f(previewXPos, previewYPos));
	spritePreview->FixedUpdate(0.0f);
	textPreview.setString(spritePreview->GetName());
}



