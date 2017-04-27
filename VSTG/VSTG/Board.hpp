#pragma once

#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include <set>
#include <vector>

class Board{
public:
	class Tile {
	public:
		Tile(int& width_in, int& height_in);
		~Tile() { clear(); }
		std::set<std::shared_ptr<GameObject>> GetLayer() const;
		void RemoveObject(std::shared_ptr<GameObject> pObject);
		void AddObject(std::shared_ptr<GameObject> pObject);
		void clear();
	private:
		int width;
		int height;
		std::set<std::shared_ptr<GameObject>> layerObject;
	};

public:
	Board(const int& boardWidth_in, const int& boardHeight_in, const int& tileWidth_in, const int& tileHeight_in);
	~Board() { clear(); }

	std::vector<sf::Vector2i> GetPotentialPos(const int id_x, const int id_y) const;
	std::vector<sf::Vector2i> GetPotentialPos(const float& pos_x, const float& pos_y) const {
		return GetPotentialPos(int(pos_x / tileWidth), int(pos_y / tileHeight));
	}
	std::vector<sf::Vector2i> GetPotentialPos(const std::shared_ptr<GameObject>& pObject) const {
		const sf::Vector2f pos = pObject->getPosition();
		return GetPotentialPos(pos.x, pos.y);
	}

	std::set<std::shared_ptr<Tile>> GetPotentialTile(const int id_x, const int id_y) const;
	std::set<std::shared_ptr<Tile>> GetPotentialTile(const float& pos_x, const float& pos_y) const {
		return GetPotentialTile(int(pos_x / tileWidth), int(pos_y / tileHeight));
	}
	std::set<std::shared_ptr<Tile>> GetPotentialTile(const std::shared_ptr<GameObject>& pObject) const {
		const sf::Vector2f pos = pObject->getPosition();
		return GetPotentialTile(pos.x, pos.y);
	}
	
	void RemoveObject(const std::shared_ptr<GameObject> pObject);
	void RemoveObject(const sf::Vector2i& brdPos, const std::shared_ptr<GameObject> pObject);
	void AddObject(const std::shared_ptr<GameObject> pObject);
	void AddObject(const sf::Vector2i& brdPos, const std::shared_ptr<GameObject> pObject);
	void View(sf::RenderTarget& gfx);
	void HighlightTile(sf::RenderTarget &gfx, sf::Vector2i pos);
	std::vector<size_t> GetCount();
	void clear();
private:
	int tileWidth;
	int tileHeight;
	int boardWidth;
	int boardHeight;
	int nRow;
	int nCol;
	std::vector<std::shared_ptr<Tile>> tiles;
};