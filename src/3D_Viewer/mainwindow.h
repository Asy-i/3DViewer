#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>

#include "glwidget.h"
//#include "gif.hpp"

extern "C" {
#include "../backend/3d_viewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// @brief получение названия файла
    void on_choosefile_clicked();
    /// @brief получение значения поворота по оси X в диапозоне от -360 до 360
    /// @param value угол поворота
    void on_rotateX_valueChanged(int value);
    /// @brief получение значения поворота по оси Y
    /// @param value угол поворота
    void on_rotateY_valueChanged(int value);
    /// @brief получение значения поворота по оси Z
    /// @param value угол поворота
    void on_rotateZ_valueChanged(int value);
    /// @brief получение значения перемещения по оси X
    /// @param value коэффициент перемещения
    void on_xMove_valueChanged(int value);
    /// @brief получения значения для масштабирования
    void scale();
    /// @brief получение значения перемещения по оси Y
    /// @param value коэффициент перемещения
    void on_yMove_valueChanged(int value);
    /// @brief получение значения перемещения по оси Z
    /// @param value коэффициент перемещения
    void on_zMove_valueChanged(int value);
    /// @brief получение настроек для отображения
    void defaultValue();
    /// @brief выбор проекции объекта
    /// @param index 0 - паралльная, 1 - центральная
    void on_projection_activated(int index);
    /// @brief получения значения ширины линий
    /// @param arg1 значение ширины
    void on_lineWidth_valueChanged(int arg1);
    /// @brief получения значения ширины вершин
    /// @param arg1 значение ширины
    void on_vertexWidth_valueChanged(int arg1);
    /// @brief получения значения цвета ребер
    void on_lineColor_clicked();
    /// @brief получения значения цвета вершин
    void on_vertexColor_clicked();
    /// @brief получения значения цвета фона
    void on_backgroundColor_clicked();
    /// @brief получение значения типа вершин
    /// @param index 0 - отсутствует, 1 - треугольник, 2 - квадрат
    void on_vertexType_activated(int index);
    /// @brief получение значения типа линии
    /// @param index 0 - спложная, 1 - пунктирная
    void on_lineType_activated(int index);
    /// @brief загрузка настроек
    void loadSettings();
    /// @brief сохранение настроек
    void saveSettings();
    /// @brief значения настроек по умолчанию
    void on_reset_clicked();
    /// @brief возврат  ползунков на 0
    void transformsZeroing();
    /// @brief сохранение скриншота
    void on_imageSave_clicked();
    /// @brief сохранение гифки
    void on_gifSave_clicked();

private:
    Ui::MainWindow *ui;
    QColor facetColor;
    QColor vertexColor;
    QColor backgroundColor;
    int facetColorRed;
    int facetColorGreen;
    int facetColorBlue;
    int facetColorF;
    int vertexColorRed;
    int vertexColorGreen;
    int vertexColorBlue;
    float backgroundColorRed;
    float backgroundColorGreen;
    float backgroundColorBlue;
    float backgroundColorF;
    int prev;
    int xAngle;
    int yAngle;
    int zAngle;
    float xMove;
    float yMove;
    float zMove;
    int lineType;
    int vertexType;
};

#endif // MAINWINDOW_H
