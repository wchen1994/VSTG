#pragma once

#include "Scene.h"
#include "Collider.h"
#include "Methods.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <deque>
#include <set>
#include <vector>

#pragma comment(lib, "CommonResourcesMethods")

class Board;

class BoardObj : public virtual Collider, public std::enable_shared_from_this<BoardObj>{
public:
	BoardObj(Board * const brd, ColliderType type, const ColliderProperities & propertites,
		FLAG_TYPE selfFlag = COLLI_FLAG_EVERYTHING, FLAG_TYPE interactFlag = COLLI_FLAG_EVERYTHING,
		const sf::Vector2f & pos = sf::Vector2f(), const CommResMeth::Angle & rot = 0.f);
	~BoardObj();
	void updateBoardPos();
	std::deque<sf::Vector2i>& getQBoardPos() { return queueBrdPos; }
	virtual void OnUpdateBrdPos();
private:
	std::deque<sf::Vector2i> queueBrdPos;
	Board *brd;
};

class Board : public CommResMeth::Scene {
public:
	struct Tile {
		Tile();
		~Tile() { Clear(); }
		const std::set<BoardObj*>& GetLayer();
//		std::set<std::shared_ptr<BoardObj>>& GetLayer();
		void RemoveObject(BoardObj* pObject);
//		void RemoveObject(std::shared_ptr<BoardObj> pObject);
		void AddObject(BoardObj* pObject);
//		void AddObject(std::shared_ptr<BoardObj> pObject);
		void Clear();

		bool isColiChecked;
		int objCount;
		std::set<BoardObj*> layerObject;
//		std::set<std::shared_ptr<BoardObj>> layerObject;
	};
	const int outsiderIndex;

public:
	Board(Scene* const parent, const sf::IntRect & rect, const int tileWidth, const int tileHeight);
	Board(Scene* const parent, const sf::IntRect & rect, const sf::Vector2i & tileSize): 
		Board(parent, rect, tileSize.x, tileSize.y){}
	~Board() { clear(); }

	/*
	Return the set of index pairs in the square shape cover the potential area
	*/
	const CommResMeth::setVecInt getPotentialPos(const int id_x, const int id_y) const;
	const CommResMeth::setVecInt getPotentialPos(const float pos_x, const float pos_y) const {
		return getPotentialPos(int(pos_x / tileSize.x), int(pos_y / tileSize.y));
	}
	const CommResMeth::setVecInt getPotentialPos(const BoardObj* pObject) const {
//	const CommResMeth::setVecInt getPotentialPos(const std::shared_ptr<BoardObj> pObject) const {
		const sf::Vector2f & pos = pObject->getPosition();
		return getPotentialPos(pos.x, pos.y);
	}

	/*
	Return the tiles that with element in it and in the potnetial area
	*/
	const std::set<std::shared_ptr<Tile>> getPotentialTile(const int id_x, const int id_y) const;
	const std::set<std::shared_ptr<Tile>> getPotentialTile(const float pos_x, const float pos_y) const {
		return getPotentialTile(int(pos_x / tileSize.x), int(pos_y / tileSize.y));
	}
	const std::set<std::shared_ptr<Tile>> getPotentialTile(const BoardObj* pObject) const {
//	const std::set<std::shared_ptr<Tile>> getPotentialTile(const std::shared_ptr<BoardObj> pObject) const {
		const sf::Vector2f & pos = pObject->getPosition();
		return getPotentialTile(pos.x, pos.y);
	}
	
	void removeObject(BoardObj* pObject);
//	void removeObject(const std::shared_ptr<BoardObj> pObject);
	void removeObject(const sf::Vector2i& brdPos, BoardObj* pObject);
//	void removeObject(const sf::Vector2i& brdPos, const std::shared_ptr<BoardObj> pObject);
	void addObject(BoardObj* pObject);
//	void addObject(const std::shared_ptr<BoardObj> pObject);
	void addObject(const sf::Vector2i& brdPos, BoardObj* pObject);
//	void addObject(const sf::Vector2i& brdPos, const std::shared_ptr<BoardObj> pObject);

	void clear();
	void processCollision();
	void updateObjsBrdPos();

public: // Getter & Setter
	const sf::Vector2i & getTileSize() const { return tileSize; }
	const sf::Vector2i & getBoardSize() const { return boardSize; }
	const sf::Vector2i & getGridSize() const { return grid; }
	const std::vector<size_t> getCountVector() const;
	size_t getCountNumb();

private:
	sf::Vector2i tileSize;
	sf::Vector2i boardSize;
	sf::Vector2i grid;
	std::vector<std::shared_ptr<Tile>> tiles;
	std::vector<std::shared_ptr<Tile>> next_tiles;
//	CommResMeth::setVecInt sHLPos;
//	std::set<std::shared_ptr<Board::Tile>> sTile;

public: // Draw for debug
	void viewGrid(sf::RenderTarget& gfx);
};