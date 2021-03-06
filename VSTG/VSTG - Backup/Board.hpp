#pragma once

#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include "Essential.hpp"
#include "ObjCharacter.h"
#include <set>
#include <vector>

class Board{
public:
	struct Tile {
//	public:
		Tile(int width_in, int height_in);
		~Tile() { clear(); }
		std::set<std::shared_ptr<ObjCharacter>>& GetLayer();
		void RemoveObject(std::shared_ptr<ObjCharacter> pObject);
		void AddObject(std::shared_ptr<ObjCharacter> pObject);
		void clear();
//	private:
		int width;
		int height;
		bool isColiChecked;
		int objCount;
		std::set<std::shared_ptr<ObjCharacter>> layerObject;
	};

public:
	Board(const int boardWidth_in, const int boardHeight_in, const int tileWidth_in, const int tileHeight_in);
	~Board() { clear(); }

	Essential::setVecInt& GetPotentialPos(const int id_x, const int id_y);
	Essential::setVecInt& GetPotentialPos(const float pos_x, const float pos_y) {
		return GetPotentialPos(int(pos_x / tileWidth), int(pos_y / tileHeight));
	}
	Essential::setVecInt& GetPotentialPos(const std::shared_ptr<ObjCharacter> pObject) {
		const sf::Vector2f pos = pObject->getPosition();
		return GetPotentialPos(pos.x, pos.y);
	}

	std::set<std::shared_ptr<Tile>>& GetPotentialTile(const int id_x, const int id_y);
	std::set<std::shared_ptr<Tile>>& GetPotentialTile(const float pos_x, const float pos_y) {
		return GetPotentialTile(int(pos_x / tileWidth), int(pos_y / tileHeight));
	}
	std::set<std::shared_ptr<Tile>>& GetPotentialTile(const std::shared_ptr<ObjCharacter> pObject) {
		const sf::Vector2f pos = pObject->getPosition();
		return GetPotentialTile(pos.x, pos.y);
	}
	
	void RemoveObject(const std::shared_ptr<ObjCharacter> pObject);
	void RemoveObject(const sf::Vector2i& brdPos, const std::shared_ptr<ObjCharacter> pObject);
	void AddObject(const std::shared_ptr<ObjCharacter> pObject);
	void AddObject(const sf::Vector2i& brdPos, const std::shared_ptr<ObjCharacter> pObject);
	void View(sf::RenderTarget& gfx);
	void Highlight(sf::RenderTarget &gfx);
	void HighlightTile(sf::RenderTarget &gfx, sf::Vector2i pos);
	std::vector<size_t> GetCount();
	void clear();
	void ProcessCollision();
	void ProcColiLayer(std::set<std::shared_ptr<ObjCharacter>> layer1, std::set<std::shared_ptr<ObjCharacter>> layer2);

	sf::Vector2i UpdateObjectPos(std::shared_ptr<ObjCharacter> pObj);
private:
	int tileWidth;
	int tileHeight;
	int boardWidth;
	int boardHeight;
	int nRow;
	int nCol;
	std::vector<std::shared_ptr<Tile>> tiles;
	Essential::setVecInt sHLPos;
	std::set<std::shared_ptr<Board::Tile>> sTile;
};