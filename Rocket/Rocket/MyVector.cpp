#include "MyVector.h"
#include <math.h>
MyVector::MyVector() {}

MyVector::MyVector(int x, int y) {
	this->x = x;
	this->y = y;
}
MyVector MyVector::add(MyVector v) {
	this->x += v.x;
	this->y += v.y;

	return *this;
}
MyVector MyVector::subtract(MyVector v) {
	this->x -= v.x;
	this->y -= v.y;

	return *this;
}
MyVector MyVector::multiply(MyVector v) {
	this->x *= v.x;
	this->y *= v.y;

	return *this;
}
MyVector MyVector::multiply(int n) {
	this->x *= n;
	this->y *= n;

	return *this;
}
MyVector MyVector::divide(MyVector v) {
	if (this->x != 0 && this->y != 0) {
		this->x /= v.x;
		this->y /= v.y;
	}
	else {
		this->x /= 1;
		this->y /= 1;
	}

	return *this;
}
MyVector MyVector::divide(int n) {
	if (n != 0) {
		this->x /= n;
		this->y /= n;
	}
	else {
		this->x /= 1;
		this->y /= 1;
	}

	return *this;
}
int MyVector::dot(MyVector v) {
	return (this->x *= v.x) + (this->y *= v.y);
}
int MyVector::magSq() {
	const int x = this->x;
	const int y = this->y;
	
	return (x * x) + (y * y);
};
int MyVector::length() {
	return int(sqrt(this->dot(*this)));
}
MyVector MyVector::normalize() {

	return this->divide(this->length());
}
MyVector MyVector::set(int x, int y) {
	this->x = x;
	this->y = y;

	return *this;
}
MyVector MyVector::limit(int max) {
	const int mSq = this->magSq();

	if (mSq > (max * max)) {
		this->divide(int(sqrt(mSq))).multiply(max);
	}

	return *this;
};

