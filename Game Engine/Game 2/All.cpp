#include "All.h"

extern std::vector<Cell> Grid;

Cell::Cell() {}
Cell::Cell(int x, int y, int w) {
	this->x = x;
	this->y = y;
	this->size = w;
	this->visited = false;
	this->revisited = 0;
}
//void Cell::display(olc::PixelGameEngine* pge) {
	void Cell::display(olc::PixelGameEngine& pge) {
	int newX = this->x * this->size;
	int newY = this->y * this->size;

	// Top Wall
	if (walls[0])
		pge.DrawLine(olc::vi2d{ newX, newY }, olc::vi2d{ newX + size, newY }, olc::WHITE);

	// Right Wall
	if (walls[1])
		pge.DrawLine(olc::vi2d{ newX + size, newY }, olc::vi2d{ newX + size, newY }, olc::WHITE);

	// Bottom Wall
	if (walls[2])
		pge.DrawLine(olc::vi2d{ newX, newY + size}, olc::vi2d{ newX + size, newY + size }, olc::WHITE);

	// Left Wall
	if (walls[3])
		pge.DrawLine(olc::vi2d{ newX, newY }, olc::vi2d{ newX, newY + size}, olc::WHITE);

	/*if (this->visited) {
		pge.FillRect(olc::vi2d{ x * size, y * size }, olc::vi2d{ size - 1, size - 1}, olc::RED);
	}*/

	/*if (this->revisited > 0) {
		pge.FillRect(olc::vi2d{ x * size, y * size }, olc::vi2d{ size, size }, olc::GREEN);
	}*/

}
void Cell::highlight(olc::PixelGameEngine& pge) {
	int x = this->x * this->size;
	int y = this->y * this->size;

	pge.FillRect(olc::vi2d{ x, y }, olc::vi2d{size, size}, olc::BLUE);
	//pge.FillRect(olc::vi2d{ x, y }, size, size, olc::BLUE);

}
int Cell::index(int cx, int cy) {
	int rows = 20;
	int cols = 20;
	if (cx < 0 || cy < 0 || cx > rows - 1 || cy > cols - 1)
		return -1;

	return cx + cy * rows;
}
Cell* Cell::checkNeighbors() {
//Cell Cell::checkNeighbors(std::vector<Cell*>& Grid) {
//Cell Cell::checkNeighbors(std::vector<Cell>& Grid) {

	std::vector<Cell*> neighbors;

	int tIndex = index(x, y - 1);
	int rIndex = index(x + 1, y);
	int bIndex = index(x, y + 1);
	int lIndex = index(x - 1, y);

	//	int tIndex = index(3, 4);
	//int rIndex = index(6, 7);
	//int bIndex = index(5, 9);
	//int lIndex = index(11, 9);

	//std::cout << "Val: " << index(19, 19) << std::endl;
	/*Cell* top = &Grid[0];
	Cell* right = &Grid[0];
	Cell* bottom = &Grid[0];
	Cell* left = &Grid[0];*/

	Cell* top = nullptr;
	Cell* right = nullptr;
	Cell* bottom = nullptr;
	Cell* left = nullptr;


	if (tIndex != -1)
		//std::cout << tIndex << std::endl;
		top = &Grid[tIndex];
	if (rIndex != -1)
		right = &Grid[rIndex];
	if (bIndex != -1)
		bottom = &Grid[bIndex];
	if (lIndex != -1)
		left = &Grid[lIndex];

	if (top && !top->visited)
		neighbors.push_back(top);
	if (right && !right->visited)
		neighbors.push_back(right);
	if (bottom && !bottom->visited)
		neighbors.push_back(bottom);
	if (left && !left->visited)
		neighbors.push_back(left);

	if (neighbors.size() > 0) {

		int randIndex = floor( rand() % neighbors.size() );

		return neighbors[randIndex];
	}

}