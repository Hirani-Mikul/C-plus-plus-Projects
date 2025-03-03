#include <conio.h>
#include "Ship.h"


Ship::Ship(int x, int y, int w, int h) {
	//this->pos = new MyVector(x, y);
	//this->vel = new MyVector(0.0f, 0.0f);
	//this->acc = new MyVector(1.0f, 0.0f);
	//this->pos = MyVector(x, y);
	//this->vel = MyVector(0.0f, 0.0f);
	//this->acc = MyVector(1.0f, 0.0f);
	this->pos.set(x, y);
	this->vel.set(0, 0);
	this->acc.set(1, 0);
	this->cWidth = w;
	this->cHeight = h;
}
void Ship::update() {
	this->move();
	//this->vel->add(this->acc);
	//this->acc->multiply(0.0f);
	//this->pos->add(*this->vel);
	//this->vel->limit(5.0f);
	this->vel.add(this->acc);
	this->vel.limit(5);
	this->pos.add(this->vel);
	this->acc.multiply(0);
}
void Ship::applyForce(int x, int y) {
	MyVector* force = new MyVector(x, y);
	this->acc.add(*force);
}
void Ship::move() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'w': //65: // up
			this->prevDir = "/\\";
			this->currentDir = this->UP;
			//this->vel.set(0, -1);
			this->acc.set(0, -1);
			break;
		case 's': //66: // down
			this->currentDir = this->DOWN;
			this->prevDir = "\\/";
			this->acc.set(0, 1);
			//this->vel.set(0, 1);
			break;
		case 'd'://67: // right
			this->currentDir = this->RIGHT;
			this->prevDir = "->";
			this->acc.set(1, 0);
			//this->vel.set(1, 0);
			break;
		case 'a'://68: // left
			this->currentDir = this->LEFT;
			this->prevDir = "<-";
			this->acc.set(-1, 0);
			//this->vel.set(-1, 0);
			break;
		case 'x':
			this->currentDir = this->STOP;
			this->vel.set(0, 0);
			break;
		case 'f':
			if (this->currentDir == this->UP) {
				this->applyForce(-2, 0);
			}
			else if (this->currentDir == this->DOWN) {
				this->applyForce(2, 0);
			}
			else if (this->currentDir == this->RIGHT) {
				this->applyForce(0, 2);
			}
			else if (this->currentDir == this->LEFT) {
				this->applyForce(0, -2);
			}
			else if (this->currentDir == this->STOP) {
				this->applyForce(0, 0);
			}
			break;
		default:
			break;
		}
	}
}
void Ship::checkEdges() {
	if (this->pos.x > this->cWidth) {
		this->pos.x = 0;
	}
	else if (this->pos.x < 0) {
		this->pos.x = this->cWidth;
	}
	if (this->pos.y > this->cHeight) {
		this->pos.y = 0;
	}
	else if (this->pos.y < 0) {
		this->pos.y = this->cHeight;
	}
}
void Ship::display() {
	if (this->currentDir == this->RIGHT) {
		cout << "->";
	} 
	else if (this->currentDir == this->LEFT) {
		cout << "<-";
	}
	else if (this->currentDir == this->UP) {
		cout << "/\\";
	}
	else if (this->currentDir == this->DOWN) {
		cout << "\\/";
	}
	else if (this->currentDir == this->STOP) {
		cout << this->prevDir;
	}

}