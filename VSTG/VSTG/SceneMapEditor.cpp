#include "SceneMapEditor.h"
#include "Essential.hpp"
#include "Enemy.hpp"

SceneMapEditor::SceneMapEditor() : isExit(false), objectEraser(eraseSize), objectBrush(brushSize)
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
			Essential::defHandleMsg(event);
		}

		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			isExit = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lShape.push_back(new sf::CircleShape(objectBrush));
			lShape.sort(compare_yaxis);
		}
		//
		// Left click need to spone only one object
		//

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			objectEraser.setOutlineThickness(1.0f);
			for (auto it = lShape.begin(); it != lShape.end(); it++) {
				const sf::Vector2f mpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
				
				//Not correct position
				const sf::Vector2f spos = (*it)->getPosition();
				const sf::Vector2f fDist = spos - mpos;
				float sqlen = fDist.x*fDist.x + fDist.y*fDist.y;
				if (sqlen < eraseSize*eraseSize) {
					lShapeBuffer.push_back(*it);
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
		for (auto it = lShapeBuffer.begin(); it != lShapeBuffer.end(); it++) {
			delete *it;
			lShape.remove(*it);
		}
		lShapeBuffer.clear();

		// Drawing
		Essential::wnd.clear();
		for (auto& shape : lShape) {
			Essential::wnd.draw(*shape);
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

bool SceneMapEditor::compare_yaxis(const sf::Shape *first, const sf::Shape *second)
{
	if (first->getPosition().y > second->getPosition().y) {
		return true;
	}
	return false;
}
