/*----------------------------------------------------------------<Header>-
Name: Solver.cpp
Title: Імплементація Solver-у.
Group: ТВ-43
Student: Галюк Д. В.
Written: 2025-05-17
Revised: 2025-05-18
Description: Алгоритм вирішення задачі(головоломки) з тетроміно.
------------------------------------------------------------------</Header>-*/

#include "Solver.h" //Хедер для "вирішальника"

/*------------------------------------------------------------------------------
Description: Конструктор Solver, ініціалізує поле.
Parameters: field — посилання на ігрове поле.
----------------------------------------------------------------------------- */
Solver::Solver(PuzzleField& field) : field(field) { //Конструктор класу Solver, ініціалізує поле та список тетроміно
	tetrominoes = {
		Tetromino(Tetromino::L),
		Tetromino(Tetromino::I),
		Tetromino(Tetromino::T),
		Tetromino(Tetromino::S)
	};
}

/*-----------------------------------------------------------------------------
Function: solve.
Description: Запускає процес вирішення головоломки, повертає true, якщо
розв'язок знайдено.
-----------------------------------------------------------------------------*/
bool Solver::solve() { //Метод, який запускає процес пошуку рішення
	return backtrack(1);
}

/*-----------------------------------------------------------------------------
Function: backtrack.
Description  : Рекурсивна функція пошуку рішень методом повернення, повертає
чи вдалося знайти рішення.
Parameters   : index — індекс поточного елемента.
-----------------------------------------------------------------------------*/
bool Solver::backtrack(int regionId) { //Рекурсивний метод для розв'язування задачі, використовуємо бектрекінг
	if (regionId > field.getRegionCount()) { //Якщо всі регіони заповнені, перевіряємо додаткові умови
		return field.checkConnected() && field.checkNoSquares();
	}
	auto cells = field.getRegionCells(regionId);
	for (const auto& tetromino : tetrominoes) { 
		for (const auto& shape : tetromino.getRotations()) {
			for (const Coord& cell : cells) {
				//Вирахування базової позиції для тетроміно
				int baseX = cell.x - shape[0].x;
				int baseY = cell.y - shape[0].y;
				if (!field.canPlaceTetromino(baseX, baseY, shape)) continue; //Перевірка на можливість розташування тетроміно на поточній позиції
				field.placeTetromino(baseX, baseY, shape, tetromino.getFigure());
				if (field.noSameTetramino(baseX, baseY, shape, tetromino.getFigure()) && field.checkNoSquares()) { //Рекурсивно вирішуємо задачу для регіону
					if (backtrack(regionId + 1)) return true; //Якщо рішення не вдалося, видаляємо тетроміно і пробуємо інший метод розміщення фігури/інше положення(rotate)/іншу фігуру
				}
				field.removeTetromino(baseX, baseY, shape);
			}
		}
	}
	return false; //Якщо ніяке розташування не вдалося - повертаємо false
}