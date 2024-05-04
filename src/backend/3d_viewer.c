#include "3d_viewer.h"

indexes s21_parser(char* filename) {
  setlocale(LC_NUMERIC, "C");
  indexes indexes = init();
  FILE* file = fopen(filename, "r");
  if (file) {
    count_(file, &indexes);
  } else {
    indexes.statusERR = 1;
  }
  if (indexes.count_facets == 0 || indexes.count_vertexes == 0) {
    indexes.statusERR = 1;
  }
  if (!indexes.statusERR) {
    size_t len = {0};
    char* str = NULL;
    indexes.arr_facets = (unsigned int*)malloc(sizeof(unsigned int) *
                                               indexes.count_facets_sum * 2);
    indexes.arr_vertexes =
        (float*)malloc(sizeof(float) * indexes.count_vertexes * 3);
    memset(indexes.arr_facets, 0, indexes.count_facets_sum * 2);
    memset(indexes.arr_vertexes, 0, indexes.count_vertexes * 3);

    fseek(file, 0, SEEK_SET);
    int i = 0, j = 0, count_vertex = 0;
    while (getline(&str, &len, file) != -1 && !indexes.statusERR) {
      if (strncmp(str, "v ", 2) == 0) {
        s21_pars_v(str, &indexes, i);
        i += 3;
        count_vertex++;
      }
      if (strncmp(str, "f ", 2) == 0) {
        j = s21_pars_f(str, &indexes, j, count_vertex);
      }
    }
    indexes.edges = indexes.count_facets + indexes.count_vertexes - 2;

    free(str);
    fclose(file);
  } else {
    indexes.statusERR = 1;
  }
  return indexes;
}

void count_(FILE* file,
            indexes* indexes) {  // return number of vertexes and facets
  char* str = NULL;
  size_t len = 0;
  while (getline(&str, &len, file) != -1) {
    strncmp(str, "v ", 2) == 0 ? indexes->count_vertexes++ : 0;
    if (strncmp(str, "f ", 2) == 0) {
      indexes->count_facets++;
      int count = count_facets_in_line(str);
      if (count <= 2) {
        indexes->statusERR = 1;
        break;
      }
      indexes->facets_in_line = count;
      indexes->count_facets_sum += count;
    }
  }
  free(str);
}

int count_facets_in_line(char* str) {  // return number of facets in line
  char* tmp_str = str;
  int count = 0;
  while (*tmp_str) {
    if (*tmp_str == ' ' && (isdigit(*(tmp_str + 1)) || *(tmp_str + 1) == '-')) {
      count++;
    }
    tmp_str++;
  }
  return count;
}

void s21_pars_v(char* str, indexes* indexes, int i) {  // parser vertexes line
  sscanf(str, "v %f %f %f", &(indexes->arr_vertexes[i]),
         &(indexes->arr_vertexes[i + 1]), &(indexes->arr_vertexes[i + 2]));
  getMinMax(indexes, indexes->arr_vertexes[i], indexes->arr_vertexes[i + 1],
            indexes->arr_vertexes[i + 2]);
}

int s21_pars_f(char* str, indexes* indexes, int i,
               int count_vertex) {  // parser facets line
  int check = 0;
  int in_line = count_facets_in_line(str);
  unsigned int start = 0;
  while (*str && in_line >= 3) {
    if (*str == ' ' && (isdigit(*(str + 1)) || *(str + 1) == '-')) {
      int get = strtol(str, &str, 10);

      if (get < 0) {
        get = count_vertex + get;
      } else {
        get -= 1;
      }

      if (check == 0) {
        indexes->arr_facets[i] = get;
        start = get;
      } else if (check != in_line) {
        indexes->arr_facets[i] = get;
        indexes->arr_facets[i + 1] = get;
        i++;
      }
      if (check == in_line - 1) {
        i++;
        indexes->arr_facets[i] = start;
      }
      i++;
      check++;
    } else {
      str++;
    }
  }

  return i;
}

void getMinMax(indexes* indexes, float X, float Y, float Z) {
  indexes->minX > X ? indexes->minX = X : 0;
  indexes->minY > Y ? indexes->minY = Y : 0;
  indexes->minZ > Z ? indexes->minZ = Z : 0;
  indexes->maxX < X ? indexes->maxX = X : 0;
  indexes->maxY < Y ? indexes->maxY = Y : 0;
  indexes->maxZ < Z ? indexes->maxZ = Z : 0;
}

indexes init() {
  indexes indexes;
  indexes.arr_facets = NULL;
  indexes.arr_vertexes = NULL;
  indexes.count_facets = 0;
  indexes.count_facets_sum = 0;
  indexes.count_vertexes = 0;
  indexes.facets_in_line = 0;
  indexes.maxX = -INFINITY;
  indexes.maxY = -INFINITY;
  indexes.maxZ = -INFINITY;
  indexes.minX = INFINITY;
  indexes.minY = INFINITY;
  indexes.minZ = INFINITY;
  indexes.statusERR = 0;
  indexes.edges = 0;
  return indexes;
}
