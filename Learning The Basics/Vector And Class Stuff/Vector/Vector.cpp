#include "Person.h"
#include <vector>
void doSomething(Animal* someone, int size) {
	for (int i = 0; i < size; i++) {
		someone->printInfo();
	}
}	

void doSomething(std::vector<Animal*> someone) {
	for (auto& a : someone)
	{
		a->printInfo();
		std::cout << std::endl;
	}
}

int main()
{

	std::vector<Animal*> Animals;
	std::vector<Person*> people;

	Animals.push_back(new Person("Mikul Hirani", 20, 'M'));
	Animals[0]->fillInfo("Indian", "no", "Software Developer", "Cricket", 0);
	Animals.push_back(new Dog("Tommy", "John Wick", 8, 'M'));
	Animals.push_back(new Dog("Doggy", "Ahmed Chaudhry", 8, 'M'));
	Animals.push_back(new Dog("Sweety", "Miss Angle", 8, 'F'));
	Animals.push_back(new Dog("Cutty", "Saldina", 8, 'F'));
	
	Animals[4]->kill();

	people.push_back(new Person("Mikul Hirani", 20, 'M'));
	people.push_back(new Person("Bhavik Hirani", 20, 'M'));
	people.push_back(new Person("Divyesh Dabasia", 20, 'M'));
	people.push_back(new Person("Nirav Vekaria", 20, 'M'));

	/*people[1]->kill();

	people.erase(
		std::remove_if(
			people.begin(), people.end(), [](const Person* p) { return p->isDead; }
		), people.end()
	);

	for (auto& p : people)
	{
		p->printInfo();
		std::cout << std::endl;
	}*/


	Animals.erase(
		std::remove_if(
			Animals.begin(), Animals.end(), [](const Animal* a) {return a->isDead; }
		),
			Animals.end()
	);


	doSomething(Animals);

	for (auto& v : Animals)
		delete v;

	Animals.clear();

	/*Animal a("Dinosaur", 302, 'M');
	Dog d("Tommy", "John Wick", 8, 'F');
	Person p("Mikul Hirani", 20, 'M');

	Animal** All = new Animal * [2];

	All[0] = new Person("Mikul Hirani", 20, 'M');
	All[1] = new Dog("Tommy", "John Wick", 8, 'F');
	All[0]->fillInfo("Indian", "no", "Software Developer", "Cricket", 0);


	doSomething(All);

	for (int i = 0; i < 2; i++)
		delete All[i];

	delete[] All;*/


	//Animal* aa = new Person("Mikul Hirani", 20, 'M');

	//doSomething(*aa);
}
