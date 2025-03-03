// OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Car {
private: 
    string Brand;
    string Color;
    double Price;
    int Seats;
    string RegistrationNumber;

protected:
    string OwnerName;
    int years;

public:

    Car(string brand, string owner, string color) {
        Brand = brand;
        OwnerName = owner;
        Color = color;
        years = 0;
    }

    void getInfo() {

        cout << "Brand: " << Brand << endl;
        cout << "Owner: " << OwnerName << endl;
        cout << "Color: " << Color << endl;
        cout << "Price: $" <<Price << endl;
        cout << "Seats: " << Seats << endl;
        cout << "Registration Number: " << RegistrationNumber << endl;
    }

    void Register(string regNum) {
        RegistrationNumber = regNum;
    }

    void setAmount (int p) {
        Price = p;
    }

    void NumberOfSeats(int seats) {
        Seats = seats;
    }

    void getAge() {
        if (years < 4) {
            cout << OwnerName << "'s product is new!. (" << years << " years)."  << endl;
        } else 
            cout << OwnerName << "'s product is very old!. (" << years << " years)." << endl;

    }

};

class SIM :public Car {
public:
    SIM(string brand, string owner, string color):Car(brand, owner, color) {

    }

    void getLocation() {
        cout << OwnerName << "'s Location: " << "Bhuj Kuttchh, Gujarat, India" << endl;
    }

    void increaseYear() {
        years++;
    }
};

int main()
{
    // CREATE INSTANCE OF CAR
    Car car("Maruti", "Mikul Hirani", "Red");
    Car car2("Jaguar", "Bhavik Hirani", "Black");

    // CREATE INSTANCE OF SIM

    SIM sim1("Safaricom", "Divyesh Dabasia", "Purple");
    SIM sim2("Airtel", "Harshad Vekaria", "Blue");


    // UPDATE CAR INFO
    car.Register("KBK 973D");
    car.setAmount(2000);
    car.NumberOfSeats(6);

    car2.Register("KBK 973M");
    car2.setAmount(6000);
    car2.NumberOfSeats(2);


    // UPDATE SIM INFO

    sim1.Register("fdskj32432fdsdddd213");
    sim1.setAmount(150);
    sim1.NumberOfSeats(1);

    sim2.Register("dsafkals3241jsd055");
    sim2.setAmount(218);
    sim2.NumberOfSeats(2);

    sim1.increaseYear();
    sim2.increaseYear();
    sim2.increaseYear();
    sim2.increaseYear();
    sim2.increaseYear();
    sim2.increaseYear();

    
    // USING POLYMORPHISM AND POINTER

    Car* s1 = &sim1;
    Car* s2 = &sim2;



    // DISPLAY CAR INFO
    car.getInfo();
    cout << endl << endl;
    car2.getInfo();
    cout << endl << endl << endl << endl;

    

    // DISPLAY SIM INFO 
    sim1.getInfo();
    sim1.getLocation();

    // GETTING AGE USING POINTERS (POLYMORPHISM)

    s1->getAge();

    cout << endl << endl;
    sim2.getInfo();
    sim2.getLocation();

    // GETTING AGE USING POINTERS (POLYMORPHISM)
    s2->getAge();

    system("pause>0");
}

