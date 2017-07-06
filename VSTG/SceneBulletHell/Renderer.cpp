#include "Renderer.h"

// Static start
std::set<std::shared_ptr<Renderer>> Renderer::setDrawObjects;
// Static end

void Renderer::draw(sf::RenderTarget & gfx)
{
	for (auto pRender : setDrawObjects) {
		pRender->sprite.setPosition(pRender->position);
		gfx.draw(pRender->sprite);
	}
}

Renderer::Renderer(std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin, const sf::Vector2f & scale)
{
	if (pTex == nullptr)
		pTex = CommResMeth::AssetManager::GetTexture("Resources/Textures/default.png");
	this->pTex = pTex;
	sprite.setTexture(*pTex);
	sprite.setOrigin(origin);
	sprite.setScale(scale);

	setDrawObjects.insert(shared_from_this());
}

Renderer::Renderer(std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale) :
	Renderer(pTex, { pTex->getSize().x / 2.f, pTex->getSize().y / 2.f }, scale)
{
}

Renderer::Renderer(const sf::IntRect & rect, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & origin, const sf::Vector2f & scale) :
	Renderer(pTex, origin, scale)
{
	sprite.setTextureRect(rect);
}

Renderer::Renderer(const sf::IntRect & rect, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale) :
	Renderer(rect, pTex, {rect.width/2.f, rect.height/2.f}, scale)
{
}

Renderer::~Renderer()
{
	setDrawObjects.erase(shared_from_this());
}
