#include <iostream>
#include "UserInterface.h" //Меню для користувача
#include "Solver.h" //Вирішення задачі
using namespace std;

int main() {
	int choice; //Змінна для вибору користувача у меню

	do {
		choice = UserInterface::showMenu(); //Виклик меню користувача
		PuzzleField field(7, 7); //Маємо поле 7на7 для заповнення
		if (choice == 1) {
			field = UserInterface::getUserField(); //Користувацький ввід
		} else if (choice == 2) {
			int testChoice;
			cout << "Choose what test to run (1 to 4): ";
			while (!readIntSimple(testChoice) || testChoice < 1 || testChoice > 4) {
				cout << "Only 1 to 4 is available, choose between them: ";
			}
			field = UserInterface::getProgramField(testChoice); //Програмний
		} else if (choice == 3) {
			cout << "Exiting program...\n";
			break;
		}
		Solver solver(field); //Створюємо об'єкт Solver з отриманим полем
		if (solver.solve()) {
			cout << "Tetromino results:\n";
			field.print(); //Вивід результату
		} else {
			cout << "Results don't satisfy expectations.\n";
		}
	} while (choice != 3); //Цикл повторюєтся поки не буде '3' як choice
	return 0;
}