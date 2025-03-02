#include <iostream>
#include "All.h"

std::vector<Cell> Grid;

class Maze : public olc::PixelGameEngine {
private:
	const int size = 15;
	int rows;
	int cols;
	std::vector<Cell*> stack;
	Cell* current = new Cell();


public:
	Maze() {
		sAppName = "Maze Generator";
	}
	void createGrid() {
		for (int j = 0; j < rows; j++)
			for (int i = 0; i < cols; i++)
				Grid.push_back(Cell(i, j, size));

	}


	bool OnUserCreate() override{

		rows = ScreenWidth() / size;
		cols = ScreenHeight() / size;

		createGrid();
		current = &Grid[0];

		return true;
	}

	void displayGrid() {
		for (auto& c : Grid)
			c.display(*this);
		//c->display(*this);

	}

	void removeWalls(Cell& a, Cell& b) {
		int x = a.x - b.x;

		if (x == 1) {
			a.walls[3] = false;
			b.walls[1] = false;
		}
		else if (x == -1) {
			a.walls[1] = false;
			b.walls[3] = false;
		}

		int y = a.y - b.y;
		if (y == 1) {
			a.walls[0] = false;
			b.walls[2] = false;
		}
		else if (y == -1) {
			a.walls[2] = false;
			b.walls[0] = false;
		}
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::VERY_DARK_GREY);

		displayGrid();
		current->visited = true;
		current->highlight(*this);
		//Cell* next = &current->checkNeighbors();
		Cell* next = current->checkNeighbors();

		
		if (next) {
			next->visited = true;
			stack.push_back(current);
			//std::cout << "Size: " << stack.size() << std::endl;
			removeWalls(*current, *next);
			current = next;
		}
		else if (stack.size() > 0) {
			current = stack.back();
			stack.pop_back();
			//std::cout << "Size: " << stack.size() << std::endl;
			//std::cout << "XY: " << current->x << ", " << current->y << std::endl;
			current->revisited++;
		}

		return true;
	}
	void clearStack() {
		Grid.erase(
			std::remove_if(Grid.begin(), Grid.end(), [](const Cell& c) { return true; }),
			Grid.end()
		);
	}
	void removeGrid() {
		std::cout << "Start: " << Grid.size() << std::endl;
		Grid.erase(
			std::remove_if(Grid.begin(), Grid.end(), [](const Cell& c) { return true; }),
			Grid.end()
		);
		std::cout << "End: " << Grid.size() << std::endl;
		std::cout << "StackEnd: " << stack.size() << std::endl;

	}

	~Maze() {
		removeGrid();
	}
};

int main() {

	Maze maze;
	if (maze.Construct(300, 300, 2, 2))
		maze.Start();
	
}