#pragma once

#include "Moveable.h"
#include "AssetManager.h"
#include "Methods.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include <list>

#pragma comment(lib, "CommonResourcesMethods")

class Renderer;

class Canvas : public CommResMeth::Scene { // Consider to make canvas an object to draw when collider ?
public:
	Canvas(Scene * const parent, sf::IntRect windowRect, sf::IntRect worldRect);
	~Canvas();
	void setBackground(std::shared_ptr<sf::Texture> pTexture, sf::IntRect rect);
	void setBackground(std::shared_ptr<sf::Texture> pTexture);

	sf::IntRect worldRect;
	std::shared_ptr<sf::Texture> pTex;
	sf::Sprite sprite;
};

class Renderer : public virtual Moveable, public std::enable_shared_from_this<Renderer>
{
public:
	static std::set<std::shared_ptr<Renderer>> setDrawObjects;
	static std::list<Canvas*> listCanvas;
	static void draw(sf::RenderTarget &gfx);
public:
	Renderer(std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin, const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f));
	Renderer(std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f));
	Renderer(const sf::IntRect & rect, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin,
		const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f));
	Renderer(const sf::IntRect & rect, std::shared_ptr<sf::Texture> pTex,
		const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f));
	~Renderer();
private:
	std::shared_ptr<sf::Texture> pTex;
	sf::Sprite sprite;
};

