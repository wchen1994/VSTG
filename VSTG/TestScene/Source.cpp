#include <Scene.hpp>

#pragma comment(lib, "CommonResourcesMethods")

//class TMP : public sf::RectangleShape {
//public:
//	void setSize(float x, float y) { sf::RectangleShape::setSize(sf::Vector2f(x, y)); }
//};
//
//namespace sf {
//	class RectangleShape : public TMP {};
//}


int main() {

	sf::RenderWindow wnd(sf::VideoMode(300, 300), "Main");

	CommResMeth::Scene *s1 = new CommResMeth::Scene(&wnd);
	CommResMeth::Scene *s2 = new CommResMeth::Scene(s1);
	s2->setSize(10, 10);
	s2->setPosition(30, 30);

	s1->setPosition(30, 30);

	sf::RectangleShape rect1;
	sf::RectangleShape rect2;

	while (wnd.isOpen()) {
		sf::Event e;
		while (wnd.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				wnd.close();
				break;
			default:
				break;
			}
		}

		rect1.setPosition(s1->left, s1->top);
		rect1.setSize(sf::Vector2f(s1->width, s1->height));
		rect1.setFillColor(sf::Color::Blue);
//		rect1.setSize(s1->width, s1->height);

		rect2.setPosition(s2->left, s2->top);
		rect2.setSize(sf::Vector2f(s2->width, s2->height));
		rect2.setFillColor(sf::Color::Red);

		wnd.clear(sf::Color::Black);
		wnd.draw(rect1);
		wnd.draw(rect2);
		wnd.display();
	}
	return 0;
}