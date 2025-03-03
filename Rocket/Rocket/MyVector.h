#pragma once
class MyVector
{
public:
	int x;
	int y;
	MyVector();
	MyVector(int, int);
	MyVector add(MyVector);
	MyVector subtract(MyVector);
	MyVector multiply(MyVector);
	MyVector multiply(int);
	MyVector divide(MyVector);
	MyVector divide(int);
	int dot(MyVector);
	int magSq();
	int length(); // also known as mag();
	MyVector normalize();

	MyVector set(int, int);
	MyVector limit(int);
};


