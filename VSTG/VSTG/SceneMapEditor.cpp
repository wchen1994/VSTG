#include "SceneMapEditor.h"

SceneMapEditor::SceneMapEditor() : isExit(false)
{
}

Essential::GameState SceneMapEditor::Run()
{
	sf::Event event;
	while (!isExit) {
		while (Essential::wnd.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::EventType::MouseMoved:
				break;
			case sf::Event::EventType::MouseButtonPressed:
				break;
			case sf::Event::EventType::KeyPressed:
				if (event.key.code == sf::Keyboard::Q) {
					isExit = true;
				}
				break;
			default:
				Essential::defHandleMsg(event);
			}
		}
		//Drawing
		Essential::wnd.clear();
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
