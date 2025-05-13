#include "Solver.h" //Хедер для "вирішальника"

Solver::Solver(PuzzleField& field) : field(field) { //Конструктор класу Solver, ініціалізує поле та список тетроміно
	tetrominoes = {
		Tetromino(Tetromino::L),
		Tetromino(Tetromino::I),
		Tetromino(Tetromino::T),
		Tetromino(Tetromino::S)
	};
}

bool Solver::solve() { //Метод, який запускає процес пошуку рішення
	return backtrack(1); //Початок з першого регіону
}

bool Solver::backtrack(int regionId) { //Рекурсивний метод для розв'язування задачі, використовуємо бектрекінг
	if (regionId > field.getRegionCount()) { //Якщо всі регіони заповнені, перевіряємо додаткові умови
		return field.checkConnected() && field.checkNoSquares(); //Додаткова умова - перевірка на з'єднання та відсутність квадратів
	}
	auto cells = field.getRegionCells(regionId); //Отримання клітини для поточного регіону
	for (const auto& tetromino : tetrominoes) { 
		for (const auto& shape : tetromino.getRotations()) { //Для кожного тетроміно пробуємо всі можливі положення
			for (const auto& [x, y] : cells) { //Для кожної клітини регіону пробуємо розташувати тетроміно
				//Вирахування базової позиції для тетроміно
				int baseX = x - shape[0].first;
				int baseY = y - shape[0].second;
				if (!field.canPlaceTetromino(baseX, baseY, shape)) continue; //Перевірка на можливість розташування тетроміно на поточній позиції
				field.placeTetromino(baseX, baseY, shape, tetromino.getCharRepresentation()); //Якщо можливо - ставимо тетроміно на поле
				if (backtrack(regionId + 1)) return true; //Рекурсивно вирішуємо задачу для наступного регіону
				field.removeTetromino(baseX, baseY, shape); //Якщо рішення не вдалося, видаляємо тетроміно і пробуємо інший метод розміщення фігури/інше положення(rotate)/іншу фігуру
			}
		}
	}
	return false; //Якщо ніяке розташування не вдалося - повертаємо false
}