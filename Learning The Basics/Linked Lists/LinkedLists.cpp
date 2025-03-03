// LinkedLists.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// UNLIKE ARRAY WHICH STORES ITS NEXT ELEMENT AFTER PREVIOUS ELEMENT IN THE MEMORY
// LINKED LISTS STORES ITS ELEMENT RANDOMLY IN THE MEMORY
// ONLY WAY TO ACCESS IT, IS TO STORE THE POINTER TO THE NEXT ELEMENT IN THE PREVIOUS ELEMENT


#include <iostream>
using namespace std;

class Node {
public:
	string Author;
	string Title;
	int pageNum;
	Node* Next;

};

void updateBook(Node* n, string author, string title, int page, Node *next) {
	n->Author = author;
	n->Title = title;
	n->pageNum = page;
	n->Next = next;
}

void printBooks(Node* n) {
	while (n != NULL) {
		cout << "Title: " << n->Title << endl;
		cout << "Total Page: " << n->pageNum << endl;
		cout << "Author: " << n->Author << endl << endl << endl;
		n = n->Next;
	}
}

void insertAtTheFront(Node** head, string author, string title, int page) {
	//1. PREPARE NEW NODE
	Node* newNode = new Node();
	//2. UPDATE AND PUT IT INFRONT OF THE CURRENT HEAD
	updateBook(newNode, author, title, page, *head);
	//3. MOVE HEAD OF THE LIST TO POINT TO THE NEWNODE
	*head = newNode;
}
void insertAtTheEnd(Node** head, string author, string title, int page) {
	//1. PREPARE NEW NODE
	Node* newNode = new Node();
	updateBook(newNode, author, title, page, NULL);

	//2. IF THE LINKED LIST IS EMPTY, NEWNODE WILL BE A HEAD NODE

	if (*head == NULL) {
		*head = newNode;
		return;
	}

	//3. ELSE FIND THE LAST NODE

	Node* last = *head;
	while(last->Next != NULL) {
		last = last->Next;
	}

	//4. INSERT THE NEW NODE AFTER THE LAST NODE (AT THE END)

	last->Next = newNode;
}

void insertAfter(Node* prev, string author, string title, int page) {
	//1. CHECK IF THE PREVIOUS NODE IN NULL
	if (prev == NULL) {
		cout << "Previous Node cannot be NULL";
		return;
	}
	//2. PREPARE A NEW NODE

	Node* newNode = new Node();

	// ALSO UPDATING THE NEXT NODE TO BE THE PREVIOUS NEXT NODE
	updateBook(newNode, author, title, page, prev->Next);

	//3. INSERT NEW NODE AFTER PREVIOUS ( CAREFULLY )
	prev->Next = newNode;
}

int main()
{
	Node* book1 = new Node(); // HEAD
	Node* book2 = new Node();
	Node* book3 = new Node();
	Node* book4 = new Node();

	updateBook(book1, "Harshad Vekaria", "Success steps", 587, book2);
	updateBook(book2, "Mikul Hirani", "Wimpy Kidz", 326, book3);
	updateBook(book3, "Nirav Rabadia", "What is IMPOSSIBLE? ", 842, book4);
	updateBook(book4, "Divyesh Dabasia", "How did this happen??", 621, NULL);

	insertAtTheFront(&book1, "Bhavik Hirani", "Who are you?", 432);
	insertAtTheEnd(&book1, "Mann Patel", "Success And Failure", 222);

	insertAfter(book3, "Yash Vekaria", "Business Success", 892);

	printBooks(book1);


	system("pause>0");
}

