/*----------------------------------------------------------------<Header>-
Name: PuzzleField.cpp
Title: Імплементація Puzzle Field.
Group: ТВ-43
Student: Галюк Д. В.
Written: 2025-05-17
Revised: 2025-05-18
Description: Реалізація класу PuzzleField — поле для тетроміно, також роботи
з ігровим полем та перевірок правильності розміщення тетроміно.
------------------------------------------------------------------</Header>-*/

#include "PuzzleField.h" //Відповідний хедер
#include <iostream>
#include <queue> //Для queue у обході матриці в ширину

/*------------------------------------------------------------------------------
Description: Конструктор класуб cтворює поле заданого розміру.
Parameters: rows — кількість рядків, cols — кількість стовпців.
-----------------------------------------------------------------------------*/
PuzzleField::PuzzleField(int rows, int cols) : rows(rows), cols(cols) { //Конструктор поля з заданою кількістю рядків і стовпців
	field = vector<vector<char>>(rows, vector<char>(cols, '.'));
	regions = vector<vector<int>>(rows, vector<int>(cols, 0));
}

/*------------------------------------------------------------------------------
Function: setRegionMap.
Description: Встановлення мапи регіонів на полі.
-----------------------------------------------------------------------------*/
void PuzzleField::setRegionMap(const vector<vector<int>>& regionMap) { //Встановлення мапи
	regions = regionMap;
}

/*-----------------------------------------------------------------------------
Function: canPlaceTetromino.
Description: Перевірка, чи можна розмістити фігуру на полі.
-----------------------------------------------------------------------------*/
bool PuzzleField::canPlaceTetromino(int x, int y, const vector<Coord>& shape) { //Перевірка: чи можна розмістити фігуру
	for (const Coord& c : shape) {
		int nx = x + c.x;
		int ny = y + c.y;
		if (!inside(nx, ny) || field[nx][ny] != '.') return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
Function: placeTetromino.
Description: Розміщує фігуру на полі.
-----------------------------------------------------------------------------*/
void PuzzleField::placeTetromino(int x, int y, const vector<Coord>& shape, char symbol) { //Розміщення фігури на полі
	for (const Coord& c : shape) {
		field[x + c.x][y + c.y] = symbol;
	}
}

/*-----------------------------------------------------------------------------
Function: removeTetromino.
Description: Видаляє фігуру з поля, тобто замінює на '.'.
-----------------------------------------------------------------------------*/
void PuzzleField::removeTetromino(int x, int y, const vector<Coord>& shape) { //Видалення фігури з поля
	for (const Coord& c : shape) {
		field[x + c.x][y + c.y] = '.';
	}
}

/* ---------------------------------------------------------------------------
Function: checkNoSquares.
Description: Перевіряє, що в полі немає квадратів 2на2 у одному регіоні(хоча
за умовою треба було з усіх регіонів).
-----------------------------------------------------------------------------*/
bool PuzzleField::checkNoSquares() const { //Перевірка відсутності квадратів
	for (int i = 0; i < rows-1; ++i) {
		for (int j = 0; j < cols-1; ++j) {
			//Всі клітини мають бути зафарбовані
			if (field[i][j] != '.' &&
				field[i][j + 1] != '.' &&
				field[i + 1][j] != '.' &&
				field[i + 1][j + 1] != '.') {
				//Та всі мають належати одному регіону
				int reg = regions[i][j];
				if (regions[i][j+1] == reg &&
					regions[i+1][j] == reg &&
					regions[i+1][j+1] == reg) {
					return false; //Квадрат у межах одного регіону
				}
			}
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
Function: noSameTetramino.
Description: Перевіряє, щоб однакові фігури не торкались сторонами один одного.
-----------------------------------------------------------------------------*/
bool PuzzleField::noSameTetramino(int baseX, int baseY, const vector<Coord>& shape, char symbol) const {
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};
    for (const Coord& c : shape) {
        int x = baseX + c.x;
        int y = baseY + c.y;
        int myRegion = regions[x][y];
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (!inside(nx, ny)) continue;
            if (regions[nx][ny] == myRegion) continue; //Всередині того ж регіону ок.
            if (field[nx][ny] == symbol) return false; //Знайшли сусідній такий самий символ, але в іншому регіоні
        }
    }
    return true;
}

/*-----------------------------------------------------------------------------
Function: checkConnected.
Description: Перевірка зв’язності всіх заповнених клітин згідно умови.
-----------------------------------------------------------------------------*/
bool PuzzleField::checkConnected() const { //Перевірка зв’язності незаповнених клітин
	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	queue<Coord> q;
	int total = 0, seen = 0;
	//Підрахунок усіх заповнених клітин
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			if (field[i][j] != '.') ++total;
	//Пошук першої заповненої клітини
	bool started = false;
	for (int i = 0; i < rows && !started; ++i)
		for (int j = 0; j < cols && !started; ++j)
			if (field[i][j] != '.') {
				q.push(Coord(i, j));
				visited[i][j] = true;
				started = true;
			}
	//Обхід матриці в ширину для перевірки зв’язності
	const int dx[] = {-1, 0, 1, 0};
	const int dy[] = {0, 1, 0, -1};
	while (!q.empty()) {
		Coord pos = q.front(); q.pop();
		++seen;
		for (int d = 0; d < 4; ++d) {
			int nx = pos.x + dx[d], ny = pos.y + dy[d];
			if (inside(nx, ny) && !visited[nx][ny] && field[nx][ny] != '.') {
				visited[nx][ny] = true;
				q.push(Coord(nx, ny));
			}
		}
	}
	return total == seen;
}

/* ----------------------------------------------------------------------------
Function: print.
Description: Вивід поля у консоль.
-----------------------------------------------------------------------------*/
void PuzzleField::print() const {
	for (const auto& row : field) {
		for (char ch : row) cout << ch << ' ';
		cout << '\n';
	}
}

/*-----------------------------------------------------------------------------
Function: getRegionCount.
Description: Повертає кількість регіонів.
-----------------------------------------------------------------------------*/
int PuzzleField::getRegionCount() const {
	int maxId = 0;
	for (const auto& row : regions)
		for (int val : row)
			if (val > maxId) maxId = val;
	return maxId;
}

/* ----------------------------------------------------------------------------
Function: getRegionMap.
Description: Повертає мапу регіонів.
-----------------------------------------------------------------------------*/
const vector<vector<int>>& PuzzleField::getRegionMap() const {
	return regions;
}

/*-----------------------------------------------------------------------------
Function: getRegionCells.
Description: Повертає координати всіх клітини, що належать до заданого регіону.
-----------------------------------------------------------------------------*/
vector<Coord> PuzzleField::getRegionCells(int regionId) const {
	vector<Coord> result;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			if (regions[i][j] == regionId)
				result.push_back(Coord(i, j));
	return result;
}

/*-----------------------------------------------------------------------------
Function: inside.
Description: Перевірка, чи знаходиться координата в межах поля.
-----------------------------------------------------------------------------*/
bool PuzzleField::inside(int x, int y) const {
	return x >= 0 && x < rows && y >= 0 && y < cols;
}