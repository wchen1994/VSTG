#pragma once

#include "GameObject.hpp"
#include <set>
#include <vector>

class Board{
private:
	class Tile {
	public:
		Tile(float& width_in, float& height_in);
		std::set<std::shared_ptr<GameObject>> GetLayer() const;
		void RemoveObject(std::shared_ptr<GameObject> pObject);
		void AddObject(std::shared_ptr<GameObject> pObject);
	private:
		float width;
		float height;
		std::set<std::shared_ptr<GameObject>> layerObject;
	};

public:
	Board(float& boardWidth_in, float& boardHeight_in, float& tileWidth_in, float& tileHeight_in);
	void UpdateBoard();
	std::set<std::shared_ptr<Tile>> GetPotentialTile(int id_x, int id_y) const;
	std::set<std::shared_ptr<Tile>> GetPotentialTile(float& pos_x, float& pos_y) const {
		return GetPotentialTile(int(pos_x / tileWidth), int(pos_y / tileHeight));
	}
	std::set<std::shared_ptr<Tile>> GetPotentialTile(std::shared_ptr<GameObject>& pObject) const {
		const sf::Vector2f pos = pObject->getPosition();
		return GetPotentialTile(int(pos.x), int(pos.y));
	}
	void RemoveObject(std::shared_ptr<GameObject> pObject);
	void AddObject(std::shared_ptr<GameObject> pObject);

private:
	float tileWidth;
	float tileHeight;
	float boardWidth;
	float boardHeight;
	int nRow;
	int nCol;
	std::vector<std::shared_ptr<Tile>> tiles;
};