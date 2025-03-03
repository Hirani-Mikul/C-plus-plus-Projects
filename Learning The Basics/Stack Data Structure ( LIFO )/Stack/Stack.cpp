// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>

void addStudents(std::stack<std::string> *studs, std::string name) {
    std::stack<std::string>* ptr = studs;
    ptr->push(name);
    //studs.push(name);
}
void removeStudents(std::stack<std::string> studs) {
    studs.pop();
}

void printName(std::stack<std::string> studs) {
    while(!studs.empty()) {
        std::cout << studs.top() << std::endl;
        studs.pop();
    }
}

int main()
{
    // EMPTY(), SIZE(), PUSH(), POP(), TOP()

    std::stack <std::string> Students;

    addStudents(&Students, "Mikul Hirani");
    addStudents(&Students, "Bhavik Hirani");
    addStudents(&Students, "Harshad Vekaria");

    if (Students.empty()) {
        std::cout << "Stack is empty." << std::endl;
    }
    else {
        printName(Students);
    }

    system("pause>0");
}
