#include "../backend/3d_viewer.h"

indexes orig();
void orToScale(indexes* indexes, float angle);
void orMoveXYZ(indexes* indexes, float angle, char axis);
void orRotateX(indexes* indexes, float angle);
void orRotateY(indexes* indexes, float angle);
void orRotateZ(indexes* indexes, float angle);