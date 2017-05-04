#include "SceneMapEditor.h"
#include "Essential.hpp"
#include "Enemy.hpp"

SceneMapEditor::SceneMapEditor() : 
	isExit(false), isDrag(false), isMouseLeft(false), 
	objectEraser(eraseSize), objectBrush(brushSize),
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
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
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
				break;
			default:
				Essential::defHandleMsg(event);
			}
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
		for (auto& pShape : sortedpShapes) {
			Essential::wnd.draw(*pShape);
		}
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


