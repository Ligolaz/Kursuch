#include <iostream>
#include "UserInterface.h"
#include "Solver.h"
using namespace std;

int main() {
	int choice = UserInterface::showMenu(); //Виклик меню користувача
	PuzzleField field(7, 7); //Маємо поле 7на7 для заповнення
	if (choice == 1) {
		field = UserInterface::getFieldFromUser(); //Користувацький ввід
	} else if (choice == 2) {
		field = UserInterface::getPresetField(); //Програмний
	} else {
		cout << "Exiting program...\n";
		return 0; //Вихід якщо '3'
	}

	Solver solver(field); //Створюємо об'єкт Solver з отриманим полем
	if (solver.solve()) {
		cout << "Tetromino results:\n";
		field.print(); //Вивід результату
	} else {
		cout << "Results don't satisfy expectations.\n";
	}
	return 0;
}
