#include <iostream>
#include "UserInterface.h" //Меню для користувача
#include "Solver.h" //Вирішення задачі
using namespace std;

int main() {
	int choice; //Змінна для вибору користувача у меню
	PuzzleField* field = nullptr;
	do {
		choice = UserInterface::showMenu(); //Виклик меню користувача
		if (choice == 1) {
			int testChoice;
			cout << "Choose what test to run (1 to 4): ";
			while (!UserInterface::readIntSimple(testChoice) || testChoice < 1 || testChoice > 4) {
				cout << "Only 1 to 4 is available, choose between them: ";
			}
			delete field;
			field = new PuzzleField(UserInterface::getProgramField(testChoice)); //Програмне заповнення поля
		} else if (choice == 2) {
			cout << "Exiting program...\n";
			break;
		}
		if (field) {
			Solver solver(*field); //Передаємо посилання на поле
			if (solver.solve()) {
				cout << "Tetromino results:\n\n";
				field->print(); //Вивід результату
				cout << "\n";
			} else {
				cout << "You've exited or something went wrong.\n";
			}
		} else {
		cout << "No field was created. Select option 1 first.\n";
		}
	} while (1); //Цикл повторюєтся поки не буде '2' як choice
	return 0;
}