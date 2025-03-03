#include <iostream>

using namespace std;


namespace recursive {
	int recursive_sum(int a, int b) {
		if (a == b) return a;

		return a + recursive_sum(a + 1, b);
	}

	int recur() {

		int a = 2, b = 10;

		int sum = recursive_sum(a, b);

		cout << "Sum: " << sum << endl;

		system("pause>0");
		return 0;
	}
}


void selectAccout() {
	cout << "1. Login: " << endl;
	cout << "2. Exit" << endl;
}

void showMenu() {
	cout << "********** MENU **********" << endl;
	cout << "1. Check Balance" << endl;
	cout << "2. Withdraw Cash" << endl;
	cout << "3. Deposit Cash" << endl;
	cout << "4. Transfer Cash" << endl;
	cout << "5. Exit" << endl;

}

int main()
{
	recursive::recur();
	int userID;
	bool isLogged = false;
	int mainMenuOption;
	int accountMenuOption;
	double user_1_Amount = 1000;
	double user_2_Amount = 2000;
	double amount = 0;
	
	selectAccout();
	cout << "Option: "; cin >> accountMenuOption;
	
	if (accountMenuOption == 1) {
			cout << "Enter Login ID: "; cin >> userID;
			amount = userID == 1 ? user_1_Amount : userID == 2 ? user_2_Amount : 0.0;
		do
		{
			showMenu();
			cout << "Option: "; cin >> mainMenuOption;
			system("cls");

			switch (mainMenuOption)
			{
			case 1:
				if (userID == 1) {
				cout << "Your balance is " << user_1_Amount << "$" << endl; break;

				}
				else if (userID == 2) {
					cout << "Your balance is " << user_2_Amount << "$" << endl; break;

				}
			case 2: 
				double withDrawAmount;
				cout << "Enter amount: "; cin >> withDrawAmount;
				if (withDrawAmount <= amount) {
					amount -= withDrawAmount;
					cout << "Your New Balance is " << amount << "$" << endl;
				}
				else cout << "Not enough money!" << endl;
				break;
			case 3: 
				double depositAmount;
				cout << "Enter amount: "; cin >> depositAmount;
				amount += depositAmount;
				cout << "Your New Balance is " << amount << "$" << endl;
				break;
			case 4:
				double transferAmount;
				int transformID;
				cout << "Enter the recipient ID: "; cin >> transformID;
				cout << "Enter Transfer Amount: "; cin >> transferAmount;

				if (transformID == userID) {
					cout << "Invalid Transaction..." << endl;
				}
				else if (transformID == 1) {
					amount -= transferAmount;
					user_1_Amount += transferAmount;
				}
				else if (transformID == 2) {
					amount -= transferAmount;
					user_2_Amount += transferAmount;
				}
				else {
					cout << "Invalid Transaction.." << endl;
				}

				cout << "Your Balance is: " << amount << "$" << endl; break;
			}

			userID == 1 ? user_1_Amount = amount : user_2_Amount = amount;

		} while (mainMenuOption != 5);
	}

	cout << "Leaving...";
	system("pause>0");
	//return 0;
}

