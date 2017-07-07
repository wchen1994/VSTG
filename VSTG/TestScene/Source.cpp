#include <Scene.h>
#include <FrameTimer.h>

#pragma comment(lib, "CommonResourcesMethods")

//class TMP : public sf::RectangleShape {
//public:
//	void setSize(float x, float y) { sf::RectangleShape::setSize(sf::Vector2f(x, y)); }
//};
//
//namespace sf {
//	class RectangleShape : public TMP {};
//}

#define _TEST_3

#ifdef _TEST_1

int main() {
	sf::RenderWindow wnd(sf::VideoMode(300, 300), "Main");
	CommResMeth::FrameTimer ft;
	ft.Mark();
	float time = 0;

	CommResMeth::Scene *s1 = new CommResMeth::Scene(&wnd);
//	CommResMeth::Scene *s1 = new CommResMeth::Scene(nullptr, sf::IntRect(30, 30, 100, 100));
	CommResMeth::Scene *s2 = new CommResMeth::Scene(s1, sf::IntRect(30, 30, 10, 10));

	s1->setPosition(30, 30);
	s2->move(0, 30);

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
		if (time > 0.1) {
			s1->move(sf::Vector2i(0, 1));
			s2->move(-1, 0);
			time = 0.0f;
		}
		time += ft.Mark();

		rect1.setPosition(s1->left, s1->top);
		rect1.setSize(sf::Vector2f(s1->width, s1->height));
		rect1.setFillColor(sf::Color::Blue);

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
#endif

#ifdef _TEST_2

class MainScene : public CommResMeth::Scene {
public:
	MainScene(Scene* const parent, sf::IntRect rect) : Scene(parent, rect) 
	{
		ft.Mark();
		s2 = new CommResMeth::Scene(this, sf::IntRect(30, 30, 10, 10));
	}

	int Exec() override
	{
		while (wnd->isOpen()) {
			sf::Event e;
			while (wnd->pollEvent(e)) {
				switch (e.type) {
				case sf::Event::Closed:
					wnd->close();
					break;
				default:
					break;
				}
			}
			if (time > 0.1) {
				move(sf::Vector2i(0, 1));
				s2->move(sf::Vector2i(-1, 0));
				time = 0.0f;
			}
			time += ft.Mark();

			rect1.setPosition(left, top);
			rect1.setSize(sf::Vector2f(width, height));
			rect1.setFillColor(sf::Color::Blue);

			rect2.setPosition(s2->left, s2->top);
			rect2.setSize(sf::Vector2f(s2->width, s2->height));
			rect2.setFillColor(sf::Color::Red);

			wnd->clear(sf::Color::Black);
			wnd->draw(rect1);
			wnd->draw(rect2);
			wnd->display();
		}

		return 0;
	}
private:
	CommResMeth::FrameTimer ft;
	float time;

	sf::RectangleShape rect1;
	sf::RectangleShape rect2;

	Scene *s2;
};

int main() {
	MainScene *s1 = new MainScene(nullptr, sf::IntRect(30, 30, 200, 200));
	return s1->exec();
}

#endif

#ifdef _TEST_3


class MainScene : public CommResMeth::Scene {
public:
	MainScene(Scene* const parent, sf::IntRect rect) : Scene(parent, rect)
	{
		ft.Mark();
	}

	int Exec() override
	{
		auto *s1 = new CommResMeth::Scene(this, sf::IntRect(30, 30, 10, 10));
		auto *s2 = new CommResMeth::Scene(this, sf::IntRect(30, 30, 10, 10));
		while (wnd->isOpen()) {
			sf::Event e;
			while (wnd->pollEvent(e)) {
				switch (e.type) {
				case sf::Event::Closed:
					wnd->close();
					break;
				default:
					break;
				}
			}
			if (time > 0.1) {
				move(sf::Vector2i(0, 1));
				s2->move(sf::Vector2i(-1, 0));
				time = 0.0f;
			}
			time += ft.Mark();

			rect1.setPosition(left, top);
			rect1.setSize(sf::Vector2f(width, height));
			rect1.setFillColor(sf::Color::Blue);

			rect2.setPosition(s2->left, s2->top);
			rect2.setSize(sf::Vector2f(s2->width, s2->height));
			rect2.setFillColor(sf::Color::Red);

			wnd->clear(sf::Color::Black);
			wnd->draw(rect1);
			wnd->draw(rect2);
			wnd->display();
		}
		delete s2;

		return 0;
	}
private:
	CommResMeth::FrameTimer ft;
	float time;

	sf::RectangleShape rect1;
	sf::RectangleShape rect2;
};

int main() {
	MainScene *s1 = new MainScene(nullptr, sf::IntRect(30, 30, 200, 200));
	return s1->exec();
}


#endif