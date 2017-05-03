#include "SceneMapEditor.h"
#include "Essential.hpp"
#include "Enemy.hpp"

SceneMapEditor::SceneMapEditor() : isExit(false)
{
}

Essential::GameState SceneMapEditor::Run()
{
	sf::Event event;
	sf::CircleShape shapeDef(5.0f);
	shapeDef.setOrigin(5.0f, 5.0f);
	shapeDef.setFillColor(sf::Color::Red);
	sf::CircleShape eraser(eraseSize);
	eraser.setOrigin(eraseSize, eraseSize);
	eraser.setOutlineColor(sf::Color::White);
	eraser.setFillColor(sf::Color::Transparent);
	eraser.setOutlineThickness(0.0f);

	lShape.push_back(new sf::CircleShape(shapeDef));
	while (Essential::wnd.isOpen() && !isExit) {
		while (Essential::wnd.pollEvent(event)) {
			Essential::defHandleMsg(event);
		}

		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			isExit = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lShape.push_back(new sf::CircleShape(shapeDef));
		}
		//
		// Left click need to spone only one object
		//

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			eraser.setOutlineThickness(1.0f);
			for (auto it = lShape.begin(), it2 = --lShape.end(); it != it2; it++) {
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
			eraser.setOutlineThickness(0.0f);
		}

		// Update element pos
		eraser.setPosition(Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd)));

		const sf::Vector2f fpos = Essential::vec2i2f(sf::Mouse::getPosition(Essential::wnd));
		lShape.back()->setPosition(fpos);

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
		Essential::wnd.draw(eraser);
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
