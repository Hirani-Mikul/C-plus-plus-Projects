#include "MyVector.h"
#include <math.h>

MyVector::MyVector() {}
MyVector::MyVector(int x, int y) {
	this->x = x;
	this->y = y;
}
MyVector MyVector::add(MyVector v) {
	MyVector temp(this->x, this->y);

	temp.x += v.x;
	temp.y += v.y;
	
	return temp;
}

MyVector MyVector::mult(MyVector v) {
	MyVector temp(this->x, this->y);

	temp.x *= v.x;
	temp.y *= v.y;

	return temp;
}
MyVector MyVector::mult(int n) {
	MyVector temp(this->x, this->y);

	temp.x *= n;
	temp.y *= n;

	return temp;
}
MyVector MyVector::sub(MyVector v) {
	MyVector temp(this->x, this->y);

	temp.x -= v.x;
	temp.y -= v.y;

	return temp;
}
MyVector MyVector::div(MyVector v) {
	MyVector temp(this->x, this->y);
	
	if (v.x != 0 && v.y != 0) {
		temp.x /= v.x;
		temp.y /= v.y;
	}
	else {
		temp.x /= 1;
		temp.y /= 1;
	}
	
	return temp;
}
MyVector MyVector::div(int n) {
	MyVector temp(this->x, this->y);

	if (n != 0) {
		temp.x /= n;
		temp.y /= n;
	}
	else {
		temp.x /= 1;
		temp.y /= 1;
	}

	return temp;
}

int MyVector::dot(MyVector v) {
	return (this->x *= v.x) + (this->y *= v.y);
}
int MyVector::magSq() {
	const int x = this->x;
	const int y = this->y;

	return (x * x) + (y * y);
}
int MyVector::length() {
	return int(sqrt(this->dot(*this)));
}

MyVector MyVector::normalize() {
	return this->div(this->length());
}
MyVector MyVector::set(int x, int y) {
	MyVector temp(this->x, this->y);

	temp.x = x;
	temp.y = y;

	return temp;
}
MyVector MyVector::limit(int max) {
	const int mSq = this->magSq();
	MyVector temp(this->x, this->y);

	if (mSq > (max * max))
		temp.div(int(sqrt(mSq))).mult(max);

	return temp;
}

/*
	GETTING RANDOM NUMBER

	int random = rand() % 10; --- 0 : 9 ----
	int random = 1 + (rand() % 9) --- 1:9 ---
*/