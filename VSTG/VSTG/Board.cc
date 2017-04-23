#include "Board.hpp"

Board::Board(int wndWidth, int wndHeight, int gridsize){
	this->gridsize = gridsize;
	width = (wndWidth + gridsize - 1) / gridsize;
	height = (wndHeight + gridsize - 1) / gridsize;

	grid.resize(height);
	for (int i=0; i<height; i++){
		grid[i].resize(width);
	}
}

void Board::insert(int row, int col, GameObject *pObject){
	grid[row][col].insert(pObject);
}

void Board::remove(int row, int col, GameObject *pObject){
	grid[row][col].erase(pObject);
}

void Board::processCollision(){
	std::set<GameObject*> setObjs;
	std::set<GameObject*>::iterator itPrimary;
	std::set<GameObject*>::iterator itSecondary;

	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			setObjs = grid[row][col];
			for (itPrimary = setObjs.begin(); 
			 	 itPrimary != setObjs.end(); 
			 	 itPrimary++){
				for (itSecondary = itPrimary; 
					 itSecondary != setObjs.end(); 
					 itSecondary++){
					(*itPrimary)->OnCollisionEnter(*itSecondary);
				}
			}
		}
	}
}

void Board::clear(){
	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			grid[row][col].clear();
		}
	}
}
