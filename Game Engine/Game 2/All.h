#pragma once
#include <vector>
#include "olcPixelGameEngine.h"



class Cell {
public:
	int x;
	int y;
	int size;
	bool walls[4] = {true, true, true, true};
	int revisited;
	//olc::PixelGameEngine* pge;

public:
	bool visited;

	Cell();
	Cell(int x, int y, int w);
	
	//void display(olc::PixelGameEngine* pge);
	void display(olc::PixelGameEngine& pge);
	//void highlight(olc::PixelGameEngine* pge);
	void highlight(olc::PixelGameEngine& pge);

	int index(int x, int y);
	//Cell checkNeighbors(std::vector<Cell*>& Grid);
	//Cell checkNeighbors(std::vector<Cell>& Grid);
	Cell* checkNeighbors();

};


//class Grid {
//
//private:
//	const int size = 20;
//	const int rows = 10;
//	const int cols = 10;
//	std::vector<Cell*> grid;
//
//public:
//	Grid();
//	void createGrid();
//
//};

