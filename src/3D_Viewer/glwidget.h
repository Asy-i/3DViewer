#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColorDialog>
#include <QColor>
#include <QOpenGLWidget>
#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QFileDialog>
#include <iostream>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QPainter>

#include "gif.hpp"

extern "C" {
#include "../backend/3d_viewer.h"
}


class glwidget : public QOpenGLWidget, protected  QOpenGLExtraFunctions
{

public:
    glwidget(QWidget *parent = nullptr);
    ~glwidget();
    indexes indexes;
    /// @brief открытие файла
    /// @param fileName файл с расширением .obj
    void fileOpener(char *fileName);
    /// @brief очищение памяти
    void removestruct();
    /// @brief инициализация OpenGL
    void initializeGL() override;
    /// @brief отрисовка
    void paintGL() override;
    /// @brief отрисовка модели
    void paintModel();
    /// @brief изменение размера
    /// @param w ширина окна
    /// @param h высота окна
    void resizeGL( int w, int h) override;
    /// @brief поворот по оси X
    /// @param rotateValue угол поворота
    void Xrotate(float rotateValue);
    /// @brief поворот по оси Y
    /// @param rotateValue угол поворота
    void Yrotate(float rotateValue);
    /// @brief поворот по оси Z
    /// @param rotateValue угол поворота
    void Zrotate(float rotateValue);
    /// @brief масштабирование
    /// @param scaleValue коэффициент масштабирования
    void Scale(float scaleValue);
    /// @brief перемещение по осям X Y Z 
    /// @param value коэффициент перемещения
    /// @param axis ось
    void moveaxis(float value, char axis);
    /// @brief установка цвета ребер
    /// @param color значения цвета
    void setFacetColor(const QColor& color);
    /// @brief установка цвета вершин
    /// @param color значения цвета
    void setVertexColor(const QColor& color);
    /// @brief установка цвета заднего фона
    /// @param color значения цвета
    void setBackgroundColor(const QColor& color);
    /// @brief установка ширины линии
    /// @param width ширина
    void setLineWidth(int width);
    /// @brief установка ширины вершин
    /// @param width ширина
    void setVertexWidth(int width);
    /// @brief установка типа проекции 0 - паралльная, 1 - центральная
    /// @param Projection тип проекции
    void setProjection(int Projection);
    /// @brief установка типа вершин 0 - отсутствует, 1 - треугольник, 2 - квадрат
    /// @param type тип вершин
    void setVertexType(int type);
    /// @brief установка типа линии 0 - спложная, 1 - пунктирная
    /// @param type тип линии
    void setLineType(int type);

private:
    int projection;
    int lineWidth;
    int vertexWidth;
    int lineType;
    int vertexType;
    QColor facetColor;
    QColor vertexColor;
    QColor backgroundColor;

};

#endif // GLWIDGET_H
