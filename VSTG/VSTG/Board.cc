#include "Board.hpp"
#include <stdlib.h>
#include <assert.h>

Board::Tile::Tile(int width_in, int height_in)
{
	width = width_in;
	height = height_in;
}

std::set<std::shared_ptr<GameObject>>& Board::Tile::GetLayer()
{
	return layerObject;
}

void Board::Tile::RemoveObject(std::shared_ptr<GameObject> pObject)
{
	layerObject.erase(pObject);
}

void Board::Tile::AddObject(std::shared_ptr<GameObject> pObject)
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
			sTile.insert(tiles[y*nCol + x]);
		}
	}
	return sTile;
}

void Board::RemoveObject(const std::shared_ptr<GameObject> pObject)
{
	sf::Vector2i& brdPos = pObject->GetBrdPos();
	RemoveObject(brdPos, pObject);
}

void Board::RemoveObject(const sf::Vector2i& brdPos, const std::shared_ptr<GameObject> pObject)
{
	if (brdPos.x < 0 || brdPos.x >= nCol || brdPos.y < 0 || brdPos.y >= nRow) {
		tiles[nCol * nRow]->RemoveObject(pObject);
	}
	else {
		tiles[brdPos.y*nCol + brdPos.x]->RemoveObject(pObject);
	}
}

void Board::AddObject(const std::shared_ptr<GameObject> pObject)
{
	sf::Vector2i& pos = pObject->GetBrdPos();
	AddObject(pos, pObject);
}

void Board::AddObject(const sf::Vector2i& brdPos, const std::shared_ptr<GameObject> pObject)
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

void Board::HighlightTile(sf::RenderTarget & gfx, sf::Vector2i pos)
{
	sf::RectangleShape rect;
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
		counts[i] = tiles[i]->GetLayer().size();
	}
	return counts;
}

void Board::clear()
{
	for (int i = 0; i <= nCol*nRow; i++) {
		tiles[i]->clear();
	}
}


