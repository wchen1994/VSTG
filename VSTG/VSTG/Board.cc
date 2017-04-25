#include "Board.hpp"
#include <stdlib.h>

Board::Tile::Tile(float & width_in, float & height_in)
{
	width = width_in;
	height = height_in;
}

std::set<std::shared_ptr<GameObject>> Board::Tile::GetLayer() const
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


Board::Board(float & boardWidth_in, float & boardHeight_in, float & tileWidth_in, float & tileHeight_in)
{
	boardWidth = boardWidth_in;
	boardHeight = boardHeight_in;
	tileWidth = tileWidth_in;
	tileHeight = tileHeight_in;
	nCol = int(boardWidth / tileWidth + 1);
	nRow = int(boardHeight / tileHeight + 1);
	for (int i = 0; i < nCol*nRow; i++) {
		tiles.push_back(std::make_shared<Tile>(Tile(tileWidth, tileHeight)));
	}
}

void Board::UpdateBoard()
{
	for (int i = 0; i < nCol*nRow; i++) {
		std::set<std::shared_ptr<GameObject>> &layer = tiles[i]->GetLayer();
		for (auto it_pObject = layer.begin(); it_pObject != layer.end(); it_pObject++) {
			sf::Vector2f &pos = (*it_pObject)->getPosition();
			const int x_new = int(pos.x / tileWidth);
			const int y_new = int(pos.y / tileHeight);
			if (x_new != i % nCol && y_new != i / nCol) {
				tiles[i]->RemoveObject(*it_pObject);
				tiles[y_new * nCol + x_new]->AddObject(*it_pObject);
			}
		}
	}
}

std::set<std::shared_ptr<Board::Tile>> Board::GetPotentialTile(int id_x, int id_y) const
{
	std::set<std::shared_ptr<Board::Tile>> sTile;
	for (int y = std::max(0, id_y - 1); y <= std::min(nRow, id_y + 1); y++) {
		for (int x = std::max(0, id_x - 1); x <= std::min(nCol, id_x + 1); x++) {
			sTile.insert(tiles[y*nCol + x]);
		}
	}
	return sTile;
}

void Board::RemoveObject(std::shared_ptr<GameObject> pObject)
{
	const sf::Vector2f pos = pObject->getPosition();
	const int id_x = int(pos.x / tileWidth);
	const int id_y = int(pos.y / tileHeight);
	tiles[id_y * nCol + id_x]->RemoveObject(pObject);
}

void Board::AddObject(std::shared_ptr<GameObject> pObject)
{
	const sf::Vector2f pos = pObject->getPosition();
	const int id_x = int(pos.x / tileWidth);
	const int id_y = int(pos.y / tileHeight);
	tiles[id_y * nCol + id_x]->AddObject(pObject);
}
