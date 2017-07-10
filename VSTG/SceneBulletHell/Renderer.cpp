#include "Renderer.h"

// Static start
std::set<Renderer*> Renderer::setDrawObjects;
// Static end

void Renderer::draw(sf::RenderTarget & gfx)
{
	for (auto pRenderer : setDrawObjects) {
		pRenderer->sprite.setPosition( CommResMeth::Scene::BottomLeftCoord2TopLeftCoord(pRenderer->position) );
		gfx.draw(pRenderer->sprite);
	}
}

Renderer::Renderer(std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin, const sf::Vector2f & scale, const CommResMeth::Angle angle) 
{
	if (pTex == nullptr)
		pTex = CommResMeth::AssetManager::GetTexture("Resources/Textures/default.png");
	this->pTex = pTex;
	sprite.setTexture(*pTex);
	sprite.setOrigin(origin);
	sprite.setScale(scale);
	sprite.setRotation(angle);

	setDrawObjects.insert(this);
}

Renderer::Renderer(const sf::IntRect & rect, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin, 
	const sf::Vector2f & scale, const CommResMeth::Angle angle) :
	Renderer(pTex, origin, scale, angle)
{
	sprite.setTextureRect(rect);
}

Renderer::~Renderer()
{
	setDrawObjects.erase(this);
}
