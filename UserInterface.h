#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "PuzzleField.h" // Для створення поля та його заповнення

class UserInterface { //UserInterface відповідає за взаємодію з користувачем
public:
	static bool readIntSimple(int& num); //Функція зчитування вибору
	static int showMenu(); //Виводить меню та повертає вибір користувача
	static PuzzleField getProgramField(int fieldNum); //Створення поля програмно
};

#endif