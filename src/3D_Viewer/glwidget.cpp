#include "glwidget.h"

glwidget::glwidget (QWidget *parent) : QOpenGLWidget(parent) {
//    indexes.arr_facets = NULL;
//    indexes.arr_vertexes = NULL;
    indexes = init();
}

glwidget::~glwidget() {
    removestruct();
}

void glwidget::removestruct() {
    if (indexes.arr_facets) free(indexes.arr_facets);
    if (indexes.arr_vertexes) free(indexes.arr_vertexes);
}

void glwidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void glwidget::paintGL() {
    if(indexes.arr_facets && indexes.arr_vertexes) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(projection) {
    glFrustum(-1, 1, -1.0, 1.0, 1.0, 10000.0);
    glTranslatef(0, 0, -2);
    update();
    } else {
    glOrtho(-1, 1, -1, 1, -10, 1000);
    glTranslatef(0, 0, -1);
    update();
    }

    paintModel();
    update();
    }
}

void glwidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void glwidget::fileOpener(char *fileName) {
    indexes = init();
    indexes = parser(fileName);
    if(!indexes.statusERR) {
        center(&indexes);
        scalСalc(&indexes, 0.7);
        update();
    } else {
        removestruct();
        indexes = init();
        indexes.statusERR = 1;
    }
}

void glwidget::paintModel() {
    glVertexPointer(3, GL_FLOAT, 0, indexes.arr_vertexes);
    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_POINTS);

    glLineWidth(lineWidth);
    glPointSize(vertexWidth);

  // Установка цвета вершин
    glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glClear(GL_COLOR_BUFFER_BIT);
    update();
    if(vertexType == 2) {
        glDrawArrays(GL_POINTS, 0, indexes.count_vertexes);
    } else if(vertexType == 1) {
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, indexes.count_vertexes);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_POINT_SMOOTH);
    }
    update();

    if(lineType) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1,0xaa);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }

//   Установка цвета граней
    glColor3f(facetColor.redF(), facetColor.greenF(), facetColor.blueF());
    glClear(GL_COLOR_BUFFER_BIT);
    update();


    glDrawElements(GL_LINES, indexes.count_facets_sum * 2 , GL_UNSIGNED_INT, indexes.arr_facets);

    glDisableClientState(GL_VERTEX_ARRAY);


}

void glwidget::Xrotate(float rotateValue) {
    rotateX(&indexes, rotateValue);
    update();
}

void glwidget::Yrotate(float rotateValue) {
    rotateY(&indexes, rotateValue);
    update();
}

void glwidget::Zrotate(float rotateValue) {
    rotateZ(&indexes, rotateValue);
    update();
}

void glwidget::Scale(float scaleValueNew) {
    toScale(&indexes, scaleValueNew);
    update();
}

void glwidget::moveaxis(float value, char axis) {
    switch(axis) {
    case 'X': moveXYZ(&indexes, value, 'X');
    break;
    case 'Y': moveXYZ(&indexes, value, 'Y');
    break;
    case 'Z': moveXYZ(&indexes, value, 'Z');
    break;
    }
    update();
}

void glwidget::setFacetColor(const QColor& color) {
    facetColor = color;
}

void glwidget::setVertexColor(const QColor& color) {
    vertexColor = color;
}

void glwidget::setBackgroundColor(const QColor& color) {
    backgroundColor = color;
}

void glwidget::setLineWidth(int width) {
    lineWidth = width;
}

void glwidget::setVertexWidth(int width) {
    vertexWidth = width;
}

void glwidget::setProjection(int Projection) {
    projection = Projection;
}

void glwidget::setVertexType(int type) {
    vertexType = type;
}

void glwidget::setLineType(int type) {
    lineType = type;
}







