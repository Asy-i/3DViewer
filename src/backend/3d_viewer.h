#ifndef SRC_3D_VIEWER_H
#define SRC_3D_VIEWER_H

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct index {
  float* arr_vertexes;
  unsigned int* arr_facets;
  int count_vertexes;    // line number of vertexes, if summ of vertexes =
                         // count_vertexes * 3
  int count_facets;      // line number of facets
  int count_facets_sum;  // summ number of facets
  int facets_in_line;    // num faceets in line
  int edges;
  float minX;
  float minY;
  float minZ;
  float maxX;
  float maxY;
  float maxZ;
  int statusERR;
} indexes;

indexes parser(char* filename);
/// @brief Количество строк с вершинами и рёбрами
/// @param file файл проекта
/// @param indexes структура с данными
void count_(FILE* file, indexes* indexes);
/// @brief Количество вершин в строке, которые нужно соединить
/// @param str текущая строка
/// @return возвращает количество вершин
int count_facets_in_line(char* str);
/// @brief парсер для строк с вершинами
/// @param str текущая строка
/// @param indexes структура с данными
/// @param i счётчик вершин для записи в массив с вершинами
void pars_v(char* str, indexes* indexes, int i);
/// @brief парсер для строк с рёбрами
/// @param str текущая строка
/// @param indexes структура с данными
/// @param i счётчик рёбер для записи в массив с рёбрами
/// @param count_vertex счётчик вершин для обработки отрицательных значений
/// @return возвращает счётчик рёбер
int pars_f(char* str, indexes* indexes, int i, int count_vertex);
/// @brief инициализация структуры
/// @return возвращает структуру
indexes init();
/// @brief поиск минимального и максимального значения
/// @param indexes структура с данными
/// @param X координата X
/// @param Y координата Y
/// @param Z координата Z
void getMinMax(indexes* indexes, float X, float Y, float Z);

// AffineTransformations

/// @brief помещения объекта в центр
/// @param indexes структура с данными
void center(indexes* indexes);
/// @brief расчёт коэффициентов масштабирования необходимого для помещения
/// объекта в поле от -1 до 1
/// @param indexes структура с данными
/// @param value коэффициент масштабирования
void scalСalc(indexes* indexes, float value);
/// @brief функция для измениения масштаба
/// @param indexes структура с данными
/// @param scal коэффициент масштабирования
void toScale(indexes* indexes, float scal);
/// @brief поиск максимального значения среди посчитанной разницы минимального и
/// максимального элемента среди координат X Y Z
/// @param scalX разница максимального и минамально элемента среди координат по
/// X
/// @param scalY разница максимального и минамально элемента среди координат по
/// Y
/// @param scalZ разница максимального и минамально элемента среди координат по
/// Z
/// @return возвращает максимальное значение
float searchMax(float scalX, float scalY, float scalZ);
/// @brief перемещение объекта по оси X Y Z
/// @param indexes структура с данными
/// @param value коэффициент перемещения
/// @param axis по какой оси двигать
void moveXYZ(indexes* indexes, float value, char axis);
/// @brief поворот объекта по оси X
/// @param indexes структура с данными
/// @param angle угол поворота
void rotateX(indexes* indexes, float angle);
/// @brief поворот объекта по оси Y
/// @param indexes структура с данными
/// @param angle угол поворота
void rotateY(indexes* indexes, float angle);
/// @brief поворот объекта по оси Z
/// @param indexes структура с данными
/// @param angle угол поворота
void rotateZ(indexes* indexes, float angle);

#endif
