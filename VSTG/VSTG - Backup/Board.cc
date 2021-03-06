#include "Board.hpp"
#include "ObjEnemy.hpp"
#include <stdlib.h>
#include <assert.h>

Board::Tile::Tile(int width_in, int height_in) : isColiChecked(false), objCount(0)
{
	width = width_in;
	height = height_in;
	isColiChecked = true;
}

std::set<std::shared_ptr<ObjCharacter>>& Board::Tile::GetLayer()
{
	return layerObject;
}

void Board::Tile::RemoveObject(std::shared_ptr<ObjCharacter> pObject)
{
	layerObject.erase(pObject);
}

void Board::Tile::AddObject(std::shared_ptr<ObjCharacter> pObject)
{
	layerObject.insert(pObject);
}

void Board::Tile::clear()
{
	layerObject.clear();
}


Board::Board(const int boardWidth_in, const int boardHeight_in, const int tileWidth_in, const int tileHeight_in)
{
	boardWidth = boardWidth_in;
	boardHeight = boardHeight_in;
	tileWidth = tileWidth_in;
	tileHeight = tileHeight_in;
	nCol = boardWidth / tileWidth + 1;
	nRow = boardHeight / tileHeight + 1;

	// Include additional tile for out of scope
	for (int i = 0; i <= nCol*nRow; i++) {
		tiles.push_back(std::make_shared<Tile>(Tile(tileWidth, tileHeight)));
	}
}


Essential::setVecInt& Board::GetPotentialPos(const int id_x, const int id_y)
{
	sHLPos.clear();
	for (int y = std::max(0, id_y - 1); y <= std::min(nRow - 1, id_y + 1); y++) {
		for (int x = std::max(0, id_x - 1); x <= std::min(nCol - 1, id_x + 1); x++) {
			sHLPos.insert(sf::Vector2i(x, y));
		}
	}
	return sHLPos;
}

std::set<std::shared_ptr<Board::Tile>>& Board::GetPotentialTile(const int id_x, const int id_y) 
{
	sTile.clear();
	for (int y = std::max(0, id_y - 1); y <= std::min(nRow-1, id_y + 1); y++) {
		for (int x = std::max(0, id_x - 1); x <= std::min(nCol-1, id_x + 1); x++) {
			auto& tile = tiles[y*nCol + x];
#ifdef _DEBUG
			for (auto & pObj : tile->GetLayer()) {
				sf::Vector2f pos = pObj->getPosition();
				if (pos.x >= 0 && pos.x < Essential::ScreenWidth && pos.y >= 0 && pos.y < Essential::ScreenHeight) {
					assert(pos.x >= x*tileWidth && pos.x < (x + 1) *tileWidth);
					assert(pos.y >= y*tileHeight && pos.y < (y + 1) *tileHeight);
				}
				else {
					assert(y*nCol + x == nCol * nRow);
				}
			}
#endif
			if (!tile->isColiChecked && tile->layerObject.size() > 0) {
				sTile.insert(tiles[y*nCol + x]);
				sHLPos.insert(sf::Vector2i(x, y));
			}
		}
	}
	return sTile;
}

void Board::RemoveObject(const std::shared_ptr<ObjCharacter> pObject)
{
	const sf::Vector2i& brdPos = pObject->GetBrdPos();
	RemoveObject(brdPos, pObject);
}

void Board::RemoveObject(const sf::Vector2i& brdPos, const std::shared_ptr<ObjCharacter> pObject)
{
	if (brdPos.x < 0 || brdPos.x >= nCol || brdPos.y < 0 || brdPos.y >= nRow) {
		tiles[nCol * nRow]->RemoveObject(pObject);
	}
	else {
		tiles[brdPos.y*nCol + brdPos.x]->RemoveObject(pObject);
	}
}

void Board::AddObject(const std::shared_ptr<ObjCharacter> pObject)
{
	const sf::Vector2i& pos = pObject->GetBrdPos();
	AddObject(pos, pObject);
}

void Board::AddObject(const sf::Vector2i& brdPos, const std::shared_ptr<ObjCharacter> pObject)
{
	if (brdPos.x < 0 || brdPos.x >= nCol || brdPos.y < 0 || brdPos.y >= nRow) {
		tiles[nCol * nRow]->AddObject(pObject);
	}
	else {
		tiles[brdPos.y*nCol + brdPos.x]->AddObject(pObject);
	}
}

void Board::View(sf::RenderTarget & gfx)
{
	for (int i = 0; i < nCol*nRow; i++) {
		const int x = i % nCol;
		const int y = i / nCol;

		sf::Vertex lines[] = {
			sf::Vertex(sf::Vector2f(float((x + 1)*tileWidth), float(y*tileHeight))),
			sf::Vertex(sf::Vector2f(float((x + 1)*tileWidth), float((y + 1)*tileHeight))),
			sf::Vertex(sf::Vector2f(float((x)*tileWidth), float((y + 1)*tileHeight)))
		};
		gfx.draw(lines, 3, sf::LineStrip);
	}
}

void Board::Highlight(sf::RenderTarget & gfx)
{
	for (auto it = sHLPos.begin(); it != sHLPos.end(); it++) {
		HighlightTile(gfx, *it);
	}
	sHLPos.clear();
}

void Board::HighlightTile(sf::RenderTarget & gfx, sf::Vector2i pos)
{
	static sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(float(pos.x * tileWidth), float(pos.y * tileHeight)));
	rect.setSize(sf::Vector2f(float(tileWidth), float(tileHeight)));
	rect.setFillColor(sf::Color::Red);
	gfx.draw(rect);
}

std::vector<size_t> Board::GetCount()
{
	std::vector<size_t> counts;
	counts.resize(nCol*nRow + 1);
	for (int i = 0; i <= nCol*nRow; i++) {
		counts[i] = tiles[i]->layerObject.size();
	}
	return counts;
}

void Board::clear()
{
	for (int i = 0; i <= nCol*nRow; i++) {
		tiles[i]->clear();
	}
}

void Board::ProcessCollision()
{
	for (int i = 0; i < nRow*nCol; i++) {
		assert(tiles[i]->isColiChecked == true);
		tiles[i]->isColiChecked = false;
	}
	for (int i = 0; i < nRow*nCol;i++) {
		auto& tile = tiles[i];
		if (!tile->isColiChecked) {
			if (tile->layerObject.size() == 0) {
				tile->isColiChecked = true;
				continue;
			}
			assert(tile->layerObject.size() > 0);
			auto& potentialTiles = GetPotentialTile(i % nCol, i / nCol);
			for (auto& potentialTile : potentialTiles) {
				auto& layer1 = tile->layerObject;
				auto& layer2 = potentialTile->layerObject;
				for (auto it1 = layer1.begin(); it1 != layer1.end(); it1++) {
					for (auto it2 = layer2.begin(); it2 != layer2.end(); it2++) {
						if ((*it1) != (*it2) && (*it1)->GetInteractType() && (*it2)->GetType()) {
							//HighlightTile(Essential::wnd, sf::Vector2i(i / nCol, i % nCol));
							sf::Vector2<float> diffPos = (*it1)->getPosition() - (*it2)->getPosition();
							float len = (*it1)->GetColliderSize() + (*it2)->GetColliderSize();
							if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
								(*it1)->OnCollisionEnter(*it2);
						}
					}
				}
			}
			tile->isColiChecked = true;
		}
	}
}

void Board::ProcColiLayer(std::set<std::shared_ptr<ObjCharacter>> layer1, std::set<std::shared_ptr<ObjCharacter>> layer2)
{
	if (layer1 != layer2) {
		for (auto& pObj1 : layer1) {
			for (auto& pObj2 : layer2) {
				pObj1->OnCollisionEnter(pObj2);
			}
		}
	}
	else {
		for (auto it1 = layer1.begin(); it1 != layer1.end(); it1++) {
			for (auto it2 = it1; it2 != --layer2.end();) {
				it2++;
				(*it2)->OnCollisionEnter(*it1);
			}
		}
	}
}

sf::Vector2i Board::UpdateObjectPos(std::shared_ptr<ObjCharacter> pObj)
{
	const auto& position = pObj->getPosition();
	const auto& brdPos = pObj->GetBrdPos();
	sf::Vector2i newBrdPos;
	if (position.x >= 0 && position.x < Essential::ScreenWidth && position.y >= 0 && position.y < Essential::ScreenHeight) {
		newBrdPos = sf::Vector2i(int(position.x / tileWidth), int(position.y / tileHeight));
	}
	else {
		newBrdPos = sf::Vector2i(0, nRow+1);
	}
	if (brdPos.x != newBrdPos.x || brdPos.y != newBrdPos.y) {
		RemoveObject(brdPos, pObj);
		AddObject(newBrdPos, pObj);
		pObj->SetBrdPos(newBrdPos);
	}
	return newBrdPos;
}



