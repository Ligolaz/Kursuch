#include "UserInterface.h" //Хедер для інтерфейсу користувача
#include <iostream>
#include <limits> //Для обробки помилок введення інтеджера
#include <vector> //Для vector - структура даних
using namespace std;

bool readIntSimple(int& num) { //Функція зчитування цілого числа
	cin >> num;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		return false;
	}
	return true;
}

int UserInterface::showMenu() { //Виводить меню та зчитує вибір користувача
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

PuzzleField UserInterface::getUserField() { //Створення пол, користувач заповнює через консоль
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

PuzzleField UserInterface::getProgramField(int fieldNum) { //Створює програмне поле з фіксованими регіонами
	if (fieldNum == 1) {
		PuzzleField field(7, 7);
		field.setRegionMap({
			{1, 2, 2, 2, 2, 3, 3},
			{1, 1, 4, 2, 3, 3, 3},
			{5, 1, 4, 6, 7, 7, 7},
			{5, 1, 4, 6, 6, 7, 7},
			{5, 5, 4, 6, 7, 7, 8},
			{5, 4, 4, 4, 7, 8, 8},
			{5, 5, 5, 4, 8, 8, 8},
		});
	} else if (fieldNum == 2) {
		PuzzleField field(7, 7);
		field.setRegionMap({
			{1, 1, 2, 2, 2, 2, 2},
			{1, 1, 1, 1, 3, 3, 2},
			{1, 1, 1, 3, 3, 4, 4},
			{1, 3, 3, 3, 5, 4, 4},
			{6, 3, 7, 5, 5, 5, 4},
			{6, 7, 7, 7, 5, 4, 4},
			{6, 6, 6, 7, 7, 7, 4},
		});
	} else if (fieldNum == 3) {
		PuzzleField field(9, 9);
		field.setRegionMap({
			{1, 1, 2, 2, 3, 3, 3, 4, 4},
			{1, 2, 2, 2, 5, 3, 3, 4, 4},
			{1, 2, 2, 5, 5, 3, 3, 4, 4},
			{1, 1, 1, 6, 5, 5, 5, 4, 4},
			{1, 6, 6, 6, 7, 7, 5, 8, 4},
			{6, 6, 9,10,10, 7, 8, 8, 8},
			{9, 9, 9,10,11, 7, 7, 7, 8},
			{9,10,10,10,11,12,12,12,12},
			{9, 9,10,11,11,11,11,12,12},
		});
	} else if (fieldNum == 4) {
		PuzzleField field(10, 10);
		field.setRegionMap({
			{1, 1, 1, 1, 2, 2, 2, 2, 2, 3},
			{1, 1, 4, 2, 2, 5, 5, 5, 2, 3},
			{6, 1, 4, 2, 2, 2, 2, 5, 2, 3},
			{6, 6, 4, 2, 7, 7, 7, 5, 2, 3},
			{6, 6, 4, 2, 2, 2, 7, 5, 2, 3},
			{8, 6, 4, 6, 6, 6, 7, 5, 3, 3},
			{8, 6, 6, 6, 9, 6,10,10, 3,11},
			{8, 8, 9, 9, 9,12,10,10, 3,11},
			{8, 8, 9,13,13,12,12,10,10,11},
			{8, 8,13,13,13,12,12,11,11,11},
		});
	}
	return field;
}