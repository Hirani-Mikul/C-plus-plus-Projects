// Structure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Car
{
    std::string brand;
    std::string color;
    int price;
    int seats;
};

struct Person
{
    std::string name;
    std::string gender;
    int age;
    Car car;
};

void printCarInfo(Car car) {
    std::cout << "Brand: " << car.brand << std::endl;
    std::cout << "Color: " << car.color << std::endl;
    std::cout << "Seats: " << car.seats << std::endl;
    std::cout << "Price: $" << car.price << std::endl;
}
void printPersonInfo(Person person) {
    std::cout << "Name: " << person.name << std::endl;
    std::cout << "Gender: " << person.gender << std::endl;
    std::cout << "Age: " << person.age << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Car Info: " << std::endl;
    printCarInfo(person.car);
}

int main()
{
    Car car1;
    car1.brand = "Tesla";
    car1.color = "Black";
    car1.seats = 4;
    car1.price = 200900;

    Person person;
    person.name = "Mikul Hirani";
    person.gender = "Male";
    person.age = 20;
    person.car = car1;

    //printCarInfo(car1);
    printPersonInfo(person);

    system("pause>0");
}
