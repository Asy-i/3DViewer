#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../backend/3d_viewer.h"
#include "orig.h"

START_TEST(parsing1) {
  indexes our = s21_parser("object/cube_first.txt");
  float orig_arr_vertexes[24] = {1.0,  1.0,  -1.0, 1.0, -1.0, -1.0, 1.0,  1.0,
                                 1.0,  1.0,  -1.0, 1.0, -1.0, 1.0,  -1.0, -1.0,
                                 -1.0, -1.0, -1.0, 1.0, 1.0,  -1.0, -1.0, 1.0};
  int orig_arr_facets[72] = {
      4, 2, 2, 0, 0, 4, 2, 7, 7, 3, 3, 2, 6, 5, 5, 7, 7, 6, 1, 7, 7, 5, 5, 1,
      0, 3, 3, 1, 1, 0, 4, 1, 1, 5, 5, 4, 4, 6, 6, 2, 2, 4, 2, 6, 6, 7, 7, 2,
      6, 4, 4, 5, 5, 6, 1, 3, 3, 7, 7, 1, 0, 2, 2, 3, 3, 0, 4, 0, 0, 1, 1, 4};
  int orig_count_vertexes = 8;
  int orig_count_facets = 12;
  int orig_count_facets_sum = 36;
  int orig_facets_in_line = 3;
  float orig_minX = -1;
  float orig_minY = -1;
  float orig_minZ = -1;
  float orig_maxX = 1;
  float orig_maxY = 1;
  float orig_maxZ = 1;
  for (int i = 0; i < orig_count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(orig_arr_vertexes[i], our.arr_vertexes[i], 1e-6);
  }
  for (int i = 0; i < orig_count_facets_sum * 2; i++) {
    ck_assert_int_eq(orig_arr_facets[i], our.arr_facets[i]);
  }

  ck_assert_int_eq(orig_count_vertexes, our.count_vertexes);
  ck_assert_int_eq(orig_count_facets, our.count_facets);
  ck_assert_int_eq(orig_count_facets_sum, our.count_facets_sum);
  ck_assert_int_eq(orig_facets_in_line, our.facets_in_line);
  ck_assert_double_eq_tol(orig_minX, our.minX, 1e-6);
  ck_assert_double_eq_tol(orig_minY, our.minY, 1e-6);
  ck_assert_double_eq_tol(orig_minZ, our.minZ, 1e-6);
  ck_assert_double_eq_tol(orig_maxX, our.maxX, 1e-6);
  ck_assert_double_eq_tol(orig_maxY, our.maxY, 1e-6);
  ck_assert_double_eq_tol(orig_maxZ, our.maxZ, 1e-6);

  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(parsing2) {
  indexes our = s21_parser("none.txt");
  int error = 1;
  ck_assert_int_eq(error, our.statusERR);
}
END_TEST

START_TEST(toCenter) {
  indexes our = init();
  our = s21_parser("object/cube_first.txt");
  float orig_arr_vertexes[24] = {1.0,  1.0,  -1.0, 1.0, -1.0, -1.0, 1.0,  1.0,
                                 1.0,  1.0,  -1.0, 1.0, -1.0, 1.0,  -1.0, -1.0,
                                 -1.0, -1.0, -1.0, 1.0, 1.0,  -1.0, -1.0, 1.0};

  center(&our);
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(orig_arr_vertexes[i], our.arr_vertexes[i], 1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(scale1) {
  indexes our = s21_parser("object/cube_first.txt");
  float orig_arr_vertexes[24] = {0.7,  0.7,  -0.7, 0.7, -0.7, -0.7, 0.7,  0.7,
                                 0.7,  0.7,  -0.7, 0.7, -0.7, 0.7,  -0.7, -0.7,
                                 -0.7, -0.7, -0.7, 0.7, 0.7,  -0.7, -0.7, 0.7};
  center(&our);
  scalСalc(&our, 0.7);
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(orig_arr_vertexes[i], our.arr_vertexes[i], 1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(scale2) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orToScale(&original, 0.5);
  toScale(&our, 0.5);
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST
///////начиная отсюжа переписать на правильные итоговые координаты вершин
START_TEST(moveX) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orMoveXYZ(&original, 0.2, 'X');
  moveXYZ(&our, 0.2, 'X');
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(moveY) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orMoveXYZ(&original, 0.3, 'Y');
  moveXYZ(&our, 0.3, 'Y');
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(moveZ) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orMoveXYZ(&original, 0.4, 'Z');
  moveXYZ(&our, 0.4, 'Z');
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(rotate_X) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orRotateX(&original, 0.4);
  rotateX(&our, 0.4);
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(rotate_Y) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orRotateY(&original, 3.6);
  rotateY(&our, 3.6);
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

START_TEST(rotate_Z) {
  indexes our = s21_parser("object/cube_first.txt");
  indexes original = orig();
  center(&our);
  scalСalc(&our, 0.7);
  orRotateZ(&original, 7.9);
  rotateZ(&our, 7.9);
  for (int i = 0; i < our.count_vertexes * 3; i++) {
    ck_assert_double_eq_tol(original.arr_vertexes[i], our.arr_vertexes[i],
                            1e-6);
  }
  free(our.arr_facets);
  free(our.arr_vertexes);
}
END_TEST

int main() {
  Suite* suite = suite_create("UNITS");
  TCase* tcase = tcase_create("TESTS");
  SRunner* srunner = srunner_create(suite);
  int res = 0;

  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, parsing1);
  tcase_add_test(tcase, parsing2);
  tcase_add_test(tcase, toCenter);
  tcase_add_test(tcase, scale1);
  tcase_add_test(tcase, scale2);
  tcase_add_test(tcase, moveX);
  tcase_add_test(tcase, moveY);
  tcase_add_test(tcase, moveZ);
  tcase_add_test(tcase, rotate_X);
  tcase_add_test(tcase, rotate_Y);
  tcase_add_test(tcase, rotate_Z);

  srunner_run_all(srunner, CK_NORMAL);
  res = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return res == 0 ? 0 : 1;
}