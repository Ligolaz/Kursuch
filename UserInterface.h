#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "PuzzleField.h"

class UserInterface {
public:
	static int showMenu();
	static PuzzleField getUserField();
	static PuzzleField getProgramField();
};

#endif