#include "SceneMapEditor.h"
#include "Essential.hpp"
#include "Enemy.hpp"

SceneMapEditor::SceneMapEditor() : 
	isExit(false), isDrag(false), isMouseLeft(false), 
	objectEraser(eraseSize), objectBrush(brushSize),
	timeAtBottom(0.0f), timeScale(100.0f),
	dragObject(NULL)
{
	objectEraser.setOrigin(eraseSize, eraseSize);
	objectEraser.setOutlineColor(sf::Color::White);
	objectEraser.setFillColor(sf::Color::Transparent);
	objectEraser.setOutlineThickness(0.0f);

	objectBrush.setOrigin(5.0f, 5.0f);
	objectBrush.setFillColor(sf::Color::Red);
}

Essential::GameState SceneMapEditor::Run()
{
	sf::Event event;

	while (Essential::wnd.isOpen() && !isExit) {
		while (Essential::wnd.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseWheelScrolled:
				timeAtBottom += scrollSpeed * event.mouseWheelScroll.delta;
				timeAtBottom = timeAtBottom < 0 ? 0.0f : timeAtBottom;
			}
			Essential::defHandleMsg(event);
		}

		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			isExit = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!isMouseLeft) {
				// Find object around for drag
				for (auto it = sortedpShapes.begin(); it != sortedpShapes.end(); it++) {
					const sf::Vector2f mpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
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
					dragObject->setPosition(Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd)));
				}
			}
			isMouseLeft = true;
		}
		else if (isMouseLeft == true){
			if (dragObject) {
				sortedpShapes.insert(dragObject); // Remove and insert back to ensure sorted set
			}
			else {
				// Add Object
				sortedpShapes.insert(new sf::CircleShape(objectBrush));
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
				const sf::Vector2f mpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
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

		// Drawing
		Essential::wnd.clear();
		// draw time line
		for (float i = timeScale - int(timeAtBottom) % int(timeScale); i < Essential::ScreenHeight; i += timeScale) {
			DrawLine(Essential::wnd, Essential::ScreenHeight - i);
		}
		// draw Shape
		for (auto& pShape : sortedpShapes) {
			Essential::wnd.draw(*pShape);
		}
		// draw tool
		Essential::wnd.draw(objectEraser);
		Essential::wnd.draw(objectBrush);	
		Essential::wnd.display();
	}

	return Essential::GameState::POP;
}

bool SceneMapEditor::LoadFromFile(const std::string filepath)
{
	try{
		infile.open("filepath");
		while (std::getline(infile, line)) {
			// line into data block
		}
		infile.close();
	}
	catch (const std::ifstream::failure &e) {
		std::cout << "Exception opening/reading file." << std::endl;
	}
	return false;
}

bool SceneMapEditor::WriteToFile(const std::string filepath)
{
	try {
		infile.open("filepath");
		for (int i = 0; i < vdata.size(); i++) {
			// data block into data;
		}
		infile.close();
	}
	catch (const std::ifstream::failure &e) {
		std::cout << "Exception opening/reading file." << std::endl;
	}
	return false;
}

void SceneMapEditor::DrawLine(sf::RenderTarget & gfx, const float y)
{
	const sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(0.0f, y)),
		sf::Vertex(sf::Vector2f(float(Essential::ScreenWidth), y))
	};
	gfx.draw(line, 2, sf::LineStrip);
}


