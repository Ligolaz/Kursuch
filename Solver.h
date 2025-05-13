#ifndef SOLVER_H
#define SOLVER_H
#include "PuzzleField.h" //Для роботи з полем
#include "Tetromino.h" //Для тетроміно та їх ротацій
#include <vector> //Для контейнера vector

class Solver { //Solver відповідає за пошук розв’язку шляхом розміщення тетроміно на полі
public:
	Solver(PuzzleField& field); //Конструктор який приймає посилання на поле
	bool solve(); //Метод, що запускає алгоритм розв’язання
private:
	PuzzleField& field; //Посилання на поле, яке заповнюєтся тетроміном
	std::vector<Tetromino> tetrominoes; //Список тетроміно, які можливі для використання
	bool backtrack(int regionId); //Функція бектрекінгу для розміщення фігур по регіонах
};

#endif