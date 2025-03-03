#pragma once
class MyVector
{
public:
	int x;
	int y;
	MyVector();
	MyVector(int, int);
	MyVector add(MyVector);
	MyVector sub(MyVector);
	MyVector mult(MyVector);
	MyVector div(MyVector);

	MyVector mult(int);
	MyVector div(int);
	int dot(MyVector);
	int magSq();
	int length();

	MyVector normalize();
	MyVector set(int, int);
	MyVector limit(int);

};

