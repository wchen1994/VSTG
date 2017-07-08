#include "Board.h"
#include <stdlib.h>
#include <assert.h>


BoardObj::BoardObj(Board * const brd, ColliderType type, const ColliderProperities & propertites, 
	FLAG_TYPE selfFlag, FLAG_TYPE interactFlag, const sf::Vector2f & pos, const CommResMeth::Angle & rot)
	:
	Moveable(pos, rot), Collider(type, propertites, selfFlag, interactFlag),
	brd(brd),
	enable_shared_from_this<BoardObj>()
{
	updateBoardPos();
	brd->addObject(shared_from_this());
}

void BoardObj::updateBoardPos()
{
	brd->removeObject(shared_from_this());
	OnUpdateBrdPos();
	brd->addObject(shared_from_this()); // outsider will automatically add to outsiders' tile
}

void BoardObj::OnUpdateBrdPos()
{
	assert(queueBrdPos.size() == 0);
	queueBrdPos.push_back(sf::Vector2i((int)position.x / brd->getTileSize().x, (int)position.y / brd->getTileSize().y));
}

Board::Tile::Tile() : isColiChecked(false), objCount(0)
{
	isColiChecked = true;
}

std::set<std::shared_ptr<BoardObj>>& Board::Tile::GetLayer()
{
	return layerObject;
}

void Board::Tile::RemoveObject(std::shared_ptr<BoardObj> pObject)
{
	layerObject.erase(pObject);
}

void Board::Tile::AddObject(std::shared_ptr<BoardObj> pObject)
{
	layerObject.insert(pObject);
}

void Board::Tile::Clear()
{
	layerObject.clear();
}


Board::Board(Scene* const parent, const int tileWidth, const int tileHeight) :
	Scene(parent),
	boardSize({ width, height }), tileSize(tileWidth, tileHeight),
	grid({ (width + 1) / tileWidth, (height + 1) / tileHeight }),
	outsiderIndex(grid.x * grid.y)
{
	// Include additional tile for out of scope
	for (int i = 0; i <= outsiderIndex; i++) {
		tiles.push_back(std::make_shared<Tile>());
		next_tiles.push_back(std::make_shared<Tile>());
	}
}

const CommResMeth::setVecInt Board::getPotentialPos(const int id_x, const int id_y) const
{
	CommResMeth::setVecInt setVec;
	for (int y = std::max(0, id_y - 1); y <= std::min(grid.y - 1, id_y + 1); y++) {
		for (int x = std::max(0, id_x - 1); x <= std::min(grid.x - 1, id_x + 1); x++) {
			setVec.insert(sf::Vector2i(x, y));
		}
	}
	return setVec;
}

const std::set<std::shared_ptr<Board::Tile>> Board::getPotentialTile(const int id_x, const int id_y) const
{
	std::set<std::shared_ptr<Board::Tile>> setTiles;
	for (const auto & vecInt : getPotentialPos(id_x, id_y)) {
		const auto & tile = tiles[vecInt.y * grid.x + vecInt.x];
#ifdef _DEBUG
		for (auto & pObj : tile->GetLayer()) {
			const sf::Vector2f & pos = pObj->getPosition();
			assert(pos.x >= vecInt.x * tileSize.x && pos.x < (vecInt.x + 1) * tileSize.x);
			assert(pos.y >= vecInt.y * tileSize.y && pos.y < (vecInt.y + 1) * tileSize.y);
		}
#endif
		if (!tile->isColiChecked && tile->layerObject.size() > 0) {
			setTiles.insert(tiles[vecInt.y * grid.x + vecInt.x]);
			//sHLPos.insert(sf::Vector2i(x, y)); // set for draw for debug
		}
	}

	return setTiles;
}

void Board::removeObject(const std::shared_ptr<BoardObj> pObject)
{
	std::deque<sf::Vector2i>& qBrdPos = pObject->getQBoardPos();
	while (qBrdPos.size() != 0) {
		auto vecBrdPos = qBrdPos.front();
		removeObject(vecBrdPos, pObject);
		qBrdPos.pop_front();
	}
}

void Board::removeObject(const sf::Vector2i& brdPos, const std::shared_ptr<BoardObj> pObject)
{
	if (brdPos.x < 0 || brdPos.x >= grid.x || brdPos.y < 0 || brdPos.y >= grid.y) {
		tiles[outsiderIndex]->RemoveObject(pObject);
	}
	else {
		tiles[brdPos.y*grid.x + brdPos.x]->RemoveObject(pObject);
	}
}

void Board::addObject(const std::shared_ptr<BoardObj> pObject)
{
	// Do not clear the queue
	std::deque<sf::Vector2i>& qBrdPos = pObject->getQBoardPos();
	for (auto vecBrdPos : qBrdPos) {
		addObject(vecBrdPos, pObject);
	}
}

void Board::addObject(const sf::Vector2i& brdPos, const std::shared_ptr<BoardObj> pObject)
{
	if (brdPos.x < 0 || brdPos.x >= grid.x || brdPos.y < 0 || brdPos.y >= grid.y) {
		next_tiles[outsiderIndex]->AddObject(pObject);
	}
	else {
		next_tiles[brdPos.y*grid.x + brdPos.x]->AddObject(pObject);
	}
}


void Board::clear()
{
	for (int i = 0; i <= outsiderIndex; i++) {
		tiles[i]->Clear();
	}
}

void Board::processCollision()
{
	for (int i = 0; i < outsiderIndex; i++) {
		assert(tiles[i]->isColiChecked == true);
		tiles[i]->isColiChecked = false;
	}
	for (int i = 0; i < outsiderIndex; i++) {
		auto& tile = tiles[i];
		if (!tile->isColiChecked) {

			// Skip if tile is empty
			if (tile->layerObject.size() == 0) {
				tile->isColiChecked = true;
				continue;
			}

			assert(tile->layerObject.size() > 0);
			const auto& potentialTiles = getPotentialTile(i % grid.x, i / grid.x);
			for (auto& potentialTile : potentialTiles) {
				auto& layer1 = tile->layerObject;
				auto& layer2 = potentialTile->layerObject;
				for (auto it1 = layer1.begin(); it1 != layer1.end(); it1++) {
					for (auto it2 = layer2.begin(); it2 != layer2.end(); it2++) {
						if ((*it1) != (*it2) && (*it1)->interactFlag && (*it2)->colliderFlag) {
							(*it1)->processCollision((*it2).get());
						}
					}
				}
			}
			tile->isColiChecked = true;
		}
	}
}

void Board::updateObjsBrdPos()
{
	for (auto tile : tiles) {
		for (auto pObj : tile->GetLayer()){
			pObj->updateBoardPos();
		}
	}
	tiles.swap(next_tiles); // Reference to cppreference.com System was in maintance
}

const std::vector<size_t> Board::getCountVector() const
{
	std::vector<size_t> counts;
	counts.resize(outsiderIndex + 1);
	for (int i = 0; i <= outsiderIndex; i++) {
		counts[i] = tiles[i]->layerObject.size();
	}
	return counts;
}

size_t Board::getCountNumb()
{
	size_t sum = 0;
	const auto & vectCount = getCountVector();
	for (size_t count : vectCount) {
		sum += count;
	}
	return sum;
}

void Board::viewGrid(sf::RenderTarget & gfx)
{
	for (int i = 0; i < outsiderIndex; i++) {
		const int x = i % grid.x;
		const int y = i / grid.x;

		//Transform to draw space
		const int startx = left + x * tileSize.x;
		const int starty = top + height - y * tileSize.y;

		sf::Vertex linesTileUpRight[] = {
			sf::Vertex(sf::Vector2f(float(startx), float(starty - tileSize.y))),
			sf::Vertex(sf::Vector2f(float(startx + tileSize.x), float(starty - tileSize.y))),
			sf::Vertex(sf::Vector2f(float(startx + tileSize.x), float(starty)))
		};
		gfx.draw(linesTileUpRight, 3, sf::LineStrip);
	}
	sf::Vertex linesBoardDownLeft[] = {
		sf::Vertex(sf::Vector2f(float(left), float(top))),
		sf::Vertex(sf::Vector2f(float(left), float(top + height))),
		sf::Vertex(sf::Vector2f(float(left + width), float(top + height))),
	};
	gfx.draw(linesBoardDownLeft, 3, sf::LineStrip);
}



