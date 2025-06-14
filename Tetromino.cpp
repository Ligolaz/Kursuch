/*------------------------------------------------------------------<Header>-
Name: Tetromino.cpp
Title: Реалізація класу Tetromino
Group: ТВ-43
Student: Галюк Д. В.
Written: 2025-05-16
Revised: 2025-05-18
Description: Реалізація конструктора, генерації обертів та допоміжних функцій.
--------------------------------------------------------------------</Header>-*/

#include "Tetromino.h" //Хедер для тетроміно
#include <algorithm> //Для sort(), min()
using namespace std;

/*--------------------------------------------------------------------------
Description: Конструктор, який ініціалізує тетроміно заданого типу, визначає
базову форму фігури та генерує всі її обертання.
--------------------------------------------------------------------------*/
Tetromino::Tetromino(Type type) : type(type) { //Конструктор, який створює фігуру заданого типу тетраміно
	vector<Coord> base;
	switch (type) {
		case L: base = { {0,0}, {1,0}, {2,0}, {2,1} }; break;
		case I: base = { {0,0}, {1,0}, {2,0}, {3,0} }; break;
		case T: base = { {0,0}, {0,1}, {0,2}, {1,1} }; break;
		case S: base = { {0,1}, {0,2}, {1,0}, {1,1} }; break;
	}
	generateRotations(base);
}

/*-------------------------------------------------------------------------
Function: getType.
Description: Повертає тип тетроміно.
-------------------------------------------------------------------------*/
Tetromino::Type Tetromino::getType() const {
	return type;
}

/*-----------------------------------------------------------------------------
Function: getRotations
Description: Повертає всі можливі варіанти розміщення фігури при обертанні.
-----------------------------------------------------------------------------*/
const vector<vector<Coord>>& Tetromino::getRotations() const {
	return rotations;
}

/*-----------------------------------------------------------------------------
Function: getFigure.
Description: Повертає символ, що позначає тип тетроміно (L, I, T, S), через
який потім отримаємо зображення фігури на полі.
-----------------------------------------------------------------------------*/
char Tetromino::getFigure() const {
	switch (type) {
		case L: return 'L';
		case I: return 'I';
		case T: return 'T';
		case S: return 'S';
	}
	return '?';
}

/*-----------------------------------------------------------------------------
Function: generateRotations
Description: Генерує всі унікальні обертання фігури на основі базового
положення, для кожного повороту нормалізує координати та додає їх, якщо
варіант унікальний.
Parameters: base — базове положення фігури (вектор координат).
-----------------------------------------------------------------------------*/
void Tetromino::generateRotations(const vector<Coord>& base) { //Генерація варіантів обертів фігури з базового положення
	vector<Coord> temp = base;
	for (int r = 0; r < 4; ++r) {
		vector<Coord> norm = temp;
		int minX = 100, minY = 100;
		for (const Coord& c : norm) {
			if (c.x < minX) minX = c.x;
			if (c.y < minY) minY = c.y;
		}
		for (Coord& c : norm) {
			c.x -= minX;
			c.y -= minY;
		}
		sort(norm.begin(), norm.end(), [](const Coord& a, const Coord& b) {
			return a.x != b.x ? a.x < b.x : a.y < b.y;
		});
		if (!isDuplicate(rotations, norm)) {
			rotations.push_back(norm);
		}
		for (Coord& c : temp) {
			int tmp = c.x;
			c.x = c.y;
			c.y = -tmp;
		}
	}
}

/*-----------------------------------------------------------------------------
Function: isDuplicate.
Description: Перевіряє, чи існує в списку вже такий варіант розміщення,
повертає false — якщо унікальний, інакше такий вже є.
Parameters: list — список існуючих варіантів (вектор векторів координат),
shape — варіант для перевірки.
-----------------------------------------------------------------------------*/
bool Tetromino::isDuplicate(const vector<vector<Coord>>& list, const vector<Coord>& shape) { //Перевірка унікальності на положення фігури
	for (const auto& variant : list) {
		if (variant.size() != shape.size()) continue;
		bool same = true;
		for (size_t i = 0; i < shape.size(); ++i) {
			if (!(variant[i] == shape[i])) {
				same = false;
				break;
			}
		}
		if (same) return true;
	}
	return false;
}