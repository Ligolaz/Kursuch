/*----------------------------------------------------------------<Header>-
Name: PuzzleField.h
Title: Хедер Puzzle Field.
Group: ТВ-43
Student: Галюк Д. В.
Written: 2025-05-17
Revised: 2025-05-18
Description: Заголовочний файл класу PuzzleField.
------------------------------------------------------------------</Header>-*/

#ifndef PUZZLEFIELD_H
#define PUZZLEFIELD_H

#include <vector> //Для vector
#include "Tetromino.h" //Для використання фігур тетроміно та Coord
using namespace std;

class PuzzleField {
public:
	PuzzleField(int rows, int cols); //Конструктор поля з заданою кількістю рядків і стовпців
	void setRegionMap(const vector<vector<int>>& regionMap); //Встановлення мапи
	bool canPlaceTetromino(int x, int y, const vector<Coord>& shape); //Перевірка: чи можна розмістити фігуру
	void placeTetromino(int x, int y, const vector<Coord>& shape, char symbol); //Розміщення фігури на полі
	void removeTetromino(int x, int y, const vector<Coord>& shape); //Видалення фігури з поля
	bool checkNoSquares() const; //Перевірка відсутності квадратів
	bool noSameTetramino(int baseX, int baseY, const vector<Coord>& shape, char symbol) const; //Перевірка на те, щоб однакові фігури не торкалися сторонами один одного
	bool checkConnected() const; //Перевірка зв’язності незаповнених клітин
	void print() const; //Вивід поля
	int getRegionCount() const; //Повертає кількість регіонів
	const vector<vector<int>>& getRegionMap() const; //Повертає мапу
	vector<Coord> getRegionCells(int regionId) const; //Повертає координати клітин регіону
private:
	int rows, cols; //Розмірність поля
	vector<vector<char>> field; //Поле з символами
	vector<vector<int>> regions; //Мапа регіонів
	bool inside(int x, int y) const; //Перевірка: чи координата в межах поля
};

#endif