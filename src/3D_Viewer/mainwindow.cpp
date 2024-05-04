#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(scale()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(scale()));
}

MainWindow::~MainWindow()
{
    transformsZeroing();
    saveSettings();
    delete ui;
}

void MainWindow::transformsZeroing() {
    ui->rotateX->setValue(0);
    ui->rotateY->setValue(0);
    ui->rotateZ->setValue(0);
    ui->xMove->setValue(0);
    ui->zMove->setValue(0);
    ui->yMove->setValue(0);
}

void MainWindow::saveSettings() {
    QSettings settings("3DViewer", "OpenGlWidget");
    settings.setValue("Xmove", ui->xMove->value());
    settings.setValue("Ymove", ui->yMove->value());
    settings.setValue("Zmove", ui->zMove->value());
    settings.setValue("Xrotate", ui->rotateX->value());
    settings.setValue("Yrotate", ui->rotateY->value());
    settings.setValue("Zrotate", ui->rotateZ->value());
    settings.setValue("valueScale", ui->valueScale->value());
    settings.setValue("lineWidth", ui->lineWidth->value());
    settings.setValue("vertexWidth", ui->vertexWidth->value());
    settings.setValue("projection",ui->projection->currentIndex());
    facetColor.getRgb(&facetColorRed, &facetColorGreen, &facetColorBlue);
    settings.setValue("facetColorRed", facetColorRed);
    settings.setValue("facetColorGreen", facetColorGreen);
    settings.setValue("facetColorBlue", facetColorBlue);
    vertexColor.getRgb(&vertexColorRed, &vertexColorGreen, &vertexColorBlue);
    settings.setValue("vertexColorRed", vertexColorRed);
    settings.setValue("vertexColorGreen", vertexColorGreen);
    settings.setValue("vertexColorBlue", vertexColorBlue);
    backgroundColor.getRgbF(&backgroundColorRed, &backgroundColorGreen, &backgroundColorBlue, &backgroundColorF);
    settings.setValue("backgroundColorRed", backgroundColorRed);
    settings.setValue("backgroundColorGreen", backgroundColorGreen);
    settings.setValue("backgroundColorBlue", backgroundColorBlue);
    settings.setValue("backgroundColorF", backgroundColorF);
    settings.setValue("lineType", ui->lineType->currentIndex());
    settings.setValue("vertexType", ui->vertexType->currentIndex());
}

void MainWindow::loadSettings() {
    QSettings settings("3DViewer", "OpenGlWidget");
    facetColor.setRgb(settings.value("facetColorRed", 0).toInt(), settings.value("facetColorGreen", 0).toInt(), settings.value("facetColorBlue", 0).toInt());
    vertexColor.setRgb(settings.value("vertexColorRed", 0).toInt(), settings.value("vertexColorGreen", 0).toInt(), settings.value("vertexColorBlue", 0).toInt());
    backgroundColor.setRgbF(settings.value("backgroundColorRed", 0).toFloat(), settings.value("backgroundColorGreen", 0).toFloat(), settings.value("backgroundColorBlue", 0).toFloat(),settings.value("backgroundColorBlue", 0).toFloat());
    ui->xMove->setValue(settings.value("Xmove", 0).toInt());
    ui->yMove->setValue(settings.value("Ymove", 0).toInt());
    ui->zMove->setValue(settings.value("Zmove", 0).toInt());
    ui->rotateX->setValue(settings.value("Xrotate", 0).toInt());
    ui->rotateY->setValue(settings.value("Yrotate", 0).toInt());
    ui->rotateZ->setValue(settings.value("Zrotate", 0).toInt());
    ui->valueScale->setValue(settings.value("valueScale", 0).toDouble());
    ui->valueScale->setValue(settings.value("valueScale", 0).toDouble());
    ui->openGLWidget->setLineWidth(settings.value("lineWidth", 0).toInt());
    ui->lineWidth->setValue(settings.value("lineWidth", 0).toInt());
    ui->openGLWidget->setVertexWidth(settings.value("vertexWidth", 0).toInt());
    ui->vertexWidth->setValue(settings.value("vertexWidth", 0).toInt());
    ui->openGLWidget->setProjection(settings.value("projection", 0).toInt());
    ui->projection->setCurrentIndex(settings.value("projection", 0).toInt());
    ui->openGLWidget->setFacetColor(facetColor);
    ui->openGLWidget->setVertexColor(vertexColor);
    ui->openGLWidget->setBackgroundColor(backgroundColor);
    ui->openGLWidget->setVertexType(settings.value("vertexType", 0).toInt());
    ui->vertexType->setCurrentIndex(settings.value("vertexType", 0).toInt());
    ui->openGLWidget->setLineType(settings.value("lineType", 0).toInt());
    ui->lineType->setCurrentIndex(settings.value("lineType", 0).toInt());
}

void MainWindow::defaultValue() {
    ui->xMove->setValue(0);
    ui->yMove->setValue(0);
    ui->zMove->setValue(0);
    ui->rotateX->setValue(0);
    ui->rotateY->setValue(0);
    ui->rotateZ->setValue(0);
    ui->valueScale->setValue(0.1);
    ui->openGLWidget->setLineWidth(1);
    ui->lineWidth->setValue(1);
    ui->openGLWidget->setVertexWidth(1);
    ui->vertexWidth->setValue(1);
    ui->openGLWidget->setProjection(0);
    ui->projection->setCurrentIndex(0);
    ui->openGLWidget->setFacetColor(Qt::white);
    facetColor = Qt::white;
    ui->openGLWidget->setVertexColor(Qt::cyan);
    vertexColor = Qt::cyan;
    ui->openGLWidget->setBackgroundColor(Qt::black);
    backgroundColor = Qt::black;
    ui->openGLWidget->setVertexType(0);
    ui->openGLWidget->setLineType(0);
    ui->openGLWidget->setVertexType(1);
    ui->lineType->setCurrentIndex(0);
    ui->vertexType->setCurrentIndex(1);
}

void MainWindow::on_choosefile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "",
                                                    "Файлы OBJ (*.obj)");
    std::string FName = fileName.toStdString();
    char *str = (char *)FName.c_str();
    transformsZeroing();
    ui->openGLWidget->fileOpener(str);
    if(!ui->openGLWidget->indexes.statusERR) {
        ui->NameFile->setText(fileName);
        ui->countVertex->setText(QString::number(ui->openGLWidget->indexes.count_vertexes));
        ui->countEdges->setText(QString::number(ui->openGLWidget->indexes.edges));
    } else {
        ui->NameFile->setText("ERROR");
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.exec();
    }

}

void MainWindow::on_rotateX_valueChanged(int value)
{
    int x = xAngle;
    xAngle = value - x;
    ui->openGLWidget->Xrotate(xAngle);
    xAngle = value;
}


void MainWindow::on_rotateY_valueChanged(int value)
{
    int y = yAngle;
    yAngle = value - y;
    ui->openGLWidget->Yrotate(yAngle);
    yAngle = value;
}


void MainWindow::on_rotateZ_valueChanged(int value)
{
    int z = zAngle;
    zAngle = value - z;
    ui->openGLWidget->Zrotate(zAngle);
    zAngle = value;
}

void MainWindow::scale() {
    QPushButton *button = (QPushButton *)sender();
    float valueScale = 1;
    if(button->text() == "+") {
        valueScale += ui->valueScale->value();
        ui->openGLWidget->Scale(valueScale);
    } else if (button->text() == "-") {
        valueScale -= ui->valueScale->value();
        ui->openGLWidget->Scale(valueScale);
    }
}

void MainWindow::on_xMove_valueChanged(int value)
{
    float value_ = (float)value / 100;
    float xMoveValue = xMove;
    xMove = value_ - xMoveValue;
    ui->openGLWidget->moveaxis(xMove, 'X');
    xMove = value_;
}

void MainWindow::on_yMove_valueChanged(int value)
{
    float value_ = (float)value / 100;
    float yMoveValue = yMove;
    yMove = value_ - yMoveValue;
    ui->openGLWidget->moveaxis(yMove, 'Y');
    yMove = value_;
}


void MainWindow::on_zMove_valueChanged(int value)
{
    float value_ = (float)value / 100;
    float zMoveValue = zMove;
    zMove = value_ - zMoveValue;
    ui->openGLWidget->moveaxis(zMove, 'Z');
    zMove = value_;
}



void MainWindow::on_projection_activated(int index)
{
        ui->openGLWidget->setProjection(index);
}


void MainWindow::on_lineWidth_valueChanged(int arg1)
{
    ui->openGLWidget->setLineWidth(arg1);
}


void MainWindow::on_vertexWidth_valueChanged(int arg1)
{
    ui->openGLWidget->setVertexWidth(arg1);
}


void MainWindow::on_lineColor_clicked()
{
    facetColor =
        QColorDialog::getColor(Qt::white, this, "Выберите цвет ребер");
    if (facetColor.isValid()) {
      ui->openGLWidget->setFacetColor(facetColor);
    }
}


void MainWindow::on_vertexColor_clicked()
{
    vertexColor =
         QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");
    if(vertexColor.isValid()) {
       ui->openGLWidget->setVertexColor(vertexColor);
    }
}

void MainWindow::on_backgroundColor_clicked() {
    backgroundColor =
         QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
    if(backgroundColor.isValid()) {
        ui->openGLWidget->setBackgroundColor(backgroundColor);
    }
}


void MainWindow::on_vertexType_activated(int index)
{
    vertexType = index;
    ui->openGLWidget->setVertexType(vertexType);
}


void MainWindow::on_lineType_activated(int index)
{
    lineType = index;
    ui->openGLWidget->setLineType(lineType);
}


void MainWindow::on_reset_clicked()
{
    defaultValue();
}


void MainWindow::on_imageSave_clicked()
{
    QTime time = QTime::currentTime();
    QString curTime = time.toString("hh:mm:ss");
    QPixmap pix = ui->openGLWidget->grab();

    QString formatImage = ui->imageFormat->itemText(ui->imageFormat->currentIndex());
    if(!pix.save(QDir::homePath() + "/Desktop/image_" + curTime + "." + formatImage)) {
        QMessageBox::warning(this, tr("ERROR"), tr("Save error"));
    } else {
        QMessageBox msgBox;
        msgBox.setText("The image was successfully saved in /Desktop/image_" + curTime + "." + formatImage);
        msgBox.exec();
    }
}


void MainWindow::on_gifSave_clicked()
{
     QTime time = QTime::currentTime();
     QString curTime = time.toString("hh:mm:ss");
     QImage img(ui->openGLWidget->size(), QImage::Format_RGBA8888);
     QPainter painter(&img);
     int delay = 100;
     GifWriter gifFigure;
     GifBegin(
         &gifFigure,
         (QDir::homePath() + "/Desktop/gif_" + curTime + ".gif").toStdString().c_str(),
         ui->openGLWidget->width(), ui->openGLWidget->height(), delay);

     for (int i = 0; i <= 5000; i = i + delay) {
       ui->openGLWidget->render(&painter);
       QImage new_img = img.transformed(QTransform().rotate(180));
       new_img = new_img.transformed(
           QTransform().scale(-1, 1).translate(new_img.width(), 0));
       GifWriteFrame(&gifFigure, new_img.bits(), ui->openGLWidget->width(),
                     ui->openGLWidget->height(), 10);
       QTime time_t = QTime::currentTime().addMSecs(100);
       while (QTime::currentTime() < time_t) {
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
       }
     }
     GifEnd(&gifFigure);
     QMessageBox msgBox;
     msgBox.setText("Gif successfully saved in /Desktop/image_" + curTime + ".gif");;
     msgBox.exec();
}

