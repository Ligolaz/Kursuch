#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

bool readIntSimple(int& num) {
	cin >> num;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		return false;
	}
	return true;
}

int UserInterface::showMenu() {
	int choice;
	while (true) {
		cout << "1. User input.\n";
		cout << "2. Program input.\n";
		cout << "3. Exit.\n";
		cout << "Enter your choice: ";
		if (readIntSimple(choice) && (choice >= 1 && choice <= 3)) return choice;
		cout << "You've got only option from 1 to 3.\n";
	}
}

PuzzleField UserInterface::getUserField() {
	PuzzleField field(7, 7);
	vector<vector<int>> userMap(7, vector<int>(7));
	cout << "Fill in 7x7 matrix:\n";
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 7; ++j) {
			while (!readIntSimple(userMap[i][j])) {
				cout << "Enter integer: ";
			}
		}
	field.setRegionMap(userMap);
	return field;
}

PuzzleField UserInterface::getProgramField() {
	PuzzleField field(7, 7);
	field.setRegionMap({
		{1,1,1,2,2,2,2},
		{1,1,1,2,3,3,2},
		{4,4,4,3,3,3,2},
		{4,5,4,3,6,6,6},
		{5,5,5,3,6,7,7},
		{5,8,8,8,6,7,7},
		{5,8,9,8,6,6,7},
	});
	return field;
}