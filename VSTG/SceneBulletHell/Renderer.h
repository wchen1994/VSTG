#pragma once

#include "Moveable.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "Methods.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include <list>

#pragma comment(lib, "CommonResourcesMethods")

class Renderer : public virtual Moveable
{
public:
	static std::set<Renderer*> setDrawObjects;
	static void draw(sf::RenderTarget &gfx);
	static void clearObjects() { setDrawObjects.clear(); }
public:
	Renderer(std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin, const sf::Vector2f & scale, const CommResMeth::Angle angle);
	Renderer(const sf::IntRect & rect, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin,
		const sf::Vector2f & scale, const CommResMeth::Angle angle);
	~Renderer();
protected:
	std::shared_ptr<sf::Texture> pTex;
	sf::Sprite sprite;
};

