// Queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>

void addStudents(std::queue<std::string> *studs, std::string name) {
    std::queue<std::string>* ptr = studs;

    ptr->push(name);
}

void printStudentsQueue(std::queue<std::string> studs) {

    std::cout << "First element is: " << studs.front() << std::endl;
    std::cout << "Last element is: " << studs.back() << std::endl;

    std::cout << std::endl << std::endl;

    while (!studs.empty())
    {
        std::cout << "Name: " << studs.front() << std::endl;
        studs.pop();
    }

}

int main()
{
    std::queue<std::string> Students;

    addStudents(&Students, "Mikul Hirani");
    addStudents(&Students, "Bhavik Hirani");
    addStudents(&Students, "Nirav Rabadia");

    if (Students.empty()) {
        std::cout << "Queue is empty." << std::endl;
    }
    else {
        printStudentsQueue(Students);
    }

    system("pause>0");
}
