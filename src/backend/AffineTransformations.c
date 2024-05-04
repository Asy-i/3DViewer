#include "3d_viewer.h"

void center(indexes* indexes) {
  float centerX = indexes->minX + (indexes->maxX - indexes->minX) / 2;
  float centerY = indexes->minY + (indexes->maxY - indexes->minY) / 2;
  float centerZ = indexes->minZ + (indexes->maxZ - indexes->minZ) / 2;
  for (int i = 0; i < indexes->count_vertexes * 3; i += 3) {
    indexes->arr_vertexes[i] -= centerX;
    indexes->arr_vertexes[i + 1] -= centerY;
    indexes->arr_vertexes[i + 2] -= centerZ;
  }
}

void scalСalc(indexes* indexes, float value) {
  float scalX = indexes->maxX - indexes->minX;
  float scalY = indexes->maxY - indexes->minY;
  float scalZ = indexes->maxZ - indexes->minZ;
  float scaleMax = searchMax(scalX, scalY, scalZ);
  float scal = (value - (value * (-1))) / scaleMax;
  toScale(indexes, scal);
}

void toScale(indexes* indexes, float scal) {
  for (int i = 0; i < indexes->count_vertexes * 3; i += 3) {
    indexes->arr_vertexes[i] *= scal;
    indexes->arr_vertexes[i + 1] *= scal;
    indexes->arr_vertexes[i + 2] *= scal;
  }
}

float searchMax(float scalX, float scalY, float scalZ) {
  float max = 0;
  scalX > max ? max = scalX : 0;
  scalY > max ? max = scalY : 0;
  scalZ > max ? max = scalZ : 0;
  return max;
}

void moveXYZ(indexes* indexes, float value, char axis) {
  int i = 0;
  if (axis == 'Y') {
    i = 1;
  }
  if (axis == 'Z') {
    i = 2;
  }
  for (; i < indexes->count_vertexes * 3; i += 3) {
    indexes->arr_vertexes[i] += value;
  }
}

void rotateX(indexes* indexes, float angle) {
  angle = angle * M_PI / 180;
  // float angle_ch = angle - indexes->xAngle;
  for (int i = 0; i < indexes->count_vertexes * 3; i += 3) {
    float temp_y = indexes->arr_vertexes[i + 1];
    float temp_z = indexes->arr_vertexes[i + 2];
    indexes->arr_vertexes[i + 1] = cos(angle) * temp_y - sin(angle) * temp_z;
    indexes->arr_vertexes[i + 2] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotateY(indexes* indexes, float angle) {
  angle = angle * M_PI / 180;
  for (int i = 0; i < indexes->count_vertexes * 3; i += 3) {
    float temp_x = indexes->arr_vertexes[i];
    float temp_z = indexes->arr_vertexes[i + 2];
    indexes->arr_vertexes[i] = cos(angle) * temp_x + sin(angle) * temp_z;
    indexes->arr_vertexes[i + 2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotateZ(indexes* indexes, float angle) {
  angle = angle * M_PI / 180;
  for (int i = 0; i < indexes->count_vertexes * 3; i += 3) {
    float temp_x = indexes->arr_vertexes[i];
    float temp_y = indexes->arr_vertexes[i + 1];
    indexes->arr_vertexes[i] = cos(angle) * temp_x - sin(angle) * temp_y;
    indexes->arr_vertexes[i + 1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}