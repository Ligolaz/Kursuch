#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "PuzzleField.h" // Для створення поля та його заповнення

class UserInterface { //UserInterface відповідає за взаємодію з користувачем
public:
	static int showMenu(); //Виводить меню та повертає вибір користувача
	static PuzzleField getUserField(); //Створення поля, заповненого користувачем
	static PuzzleField getProgramField(int fieldNum); //Створення поля програмно
};

#endif