#include "orig.h"

indexes orig() {
  indexes orig = parser("object/cube_first.obj");
  center(&orig);
  scalСalc(&orig, 0.7);
  return orig;
}

void orToScale(indexes* indexes, float angle) { toScale(indexes, angle); }

void orMoveXYZ(indexes* indexes, float angle, char axis) {
  moveXYZ(indexes, angle, axis);
}

void orRotateX(indexes* indexes, float angle) { rotateX(indexes, angle); }

void orRotateY(indexes* indexes, float angle) { rotateY(indexes, angle); }

void orRotateZ(indexes* indexes, float angle) { rotateZ(indexes, angle); }