#include "Renderer.h"

// Static start
std::set<std::shared_ptr<Renderer>> Renderer::setDrawObjects;
std::list<Canvas*> Renderer::listCanvas;
// Static end

void Renderer::draw(sf::RenderTarget & gfx)
{
	// Draw Canvas Background first
	for (auto pCanvas : listCanvas) {
		if (pCanvas->pTex)
			gfx.draw(pCanvas->sprite);
	}

	// Draw objects
	for (auto pRender : setDrawObjects) {
		for (auto pCanvas : listCanvas) {
			auto& worldRect = pCanvas->worldRect; // Maybe add a register signiture
			if (worldRect.contains(sf::Vector2i((int)pRender->position.x, (int)pRender->position.y))) {
				const sf::Vector2f canvasPos = pRender->position - sf::Vector2f((float)worldRect.left, (float)worldRect.top - worldRect.height);
				pRender->sprite.setPosition(pCanvas->BottomLeftCoord2Window(canvasPos));
				gfx.draw(pRender->sprite);
			}
		}
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

Canvas::Canvas(Scene * const parent, const sf::IntRect & windowRect, const sf::FloatRect & worldRect) :
	Scene(parent, windowRect), worldRect(worldRect), pTex(nullptr), view(worldRect)
{
	Renderer::listCanvas.push_back(this);
}

Canvas::~Canvas()
{
	for (auto itCanvas = Renderer::listCanvas.begin(); itCanvas != Renderer::listCanvas.end();) {
		if (*itCanvas == this) {
			itCanvas = Renderer::listCanvas.erase(itCanvas);
			break;
		}
		else {
			++itCanvas;
		}
	}
}

void Canvas::setBackground(std::shared_ptr<sf::Texture> pTexture, sf::IntRect rect)
{
	pTex = pTexture;
	sprite.setPosition((float)left, (float)top);
	sprite.setTexture(*pTexture);
	sprite.setTextureRect(rect);
	sf::Vector2f scale = { width / (float)rect.width, height / (float)rect.height };
	sprite.setScale(scale);
}

void Canvas::setBackground(std::shared_ptr<sf::Texture> pTexture)
{
	const sf::IntRect rect = { 0,0,(int)pTexture->getSize().x,(int)pTexture->getSize().y };
	setBackground(pTexture, rect);
}
