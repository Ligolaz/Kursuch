#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector> //Для vector
using namespace std;

class Tetromino {
public:
    enum Type { L, I, T, S }; //Перелік доступних типів тетроміно
    Tetromino(Type type); //Конструктор, який створює фігуру заданого типу тетраміно
    Type getType() const; //Отримати тип фігури
    const vector<vector<Coord>>& getRotations() const; //Отримати всі можливі варіанти фігури (її положення при обертанні)
    char getFigure() const; //Отримати символ (L, I...), через який потім отримаємо зображення фігури на полі
private:
    Type type; //Тип фігури
    vector<vector<Coord>> rotations; //Всі можливі варіанти розміщення фігури, де кожне розміщення є списоком координат клітин
    void generateRotations(const vector<Coord>& base);	//Генерація варіантів обертів фігури з базового положення
	bool isDuplicate(const vector<vector<Coord>>& list, const vector<Coord>& shape); //Перевірка унікальності на положення фігури
};

#endif