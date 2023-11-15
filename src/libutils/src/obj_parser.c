#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static void *s_realloc(void *ptr, size_t nsize) {
  if (ptr != NULL) {
    void *tmp = realloc(ptr, nsize);
    if (tmp != NULL) {
      ptr = tmp;
    } else {
      free(ptr);
      ptr = NULL;
    }
  }

  return ptr;
}

int vertices_is_init(vert_t *v) {
  return v != NULL && v->data != NULL && v->cap > 0;
}

int vertices_create(vert_t *dest, int capacity) {
  int res = 1;

  if (dest != NULL && capacity > 0) {
    memset(dest, 0, sizeof(vert_t));

    if ((dest->data = calloc(capacity, sizeof(float))) != NULL) {
      dest->cap = capacity;
      res = 0;
    }
  }

  return res;
}

void vertices_push(vert_t *vertices, float vertex) {
  if (vertices_is_init(vertices)) {
    if (vertices->len + 1 == vertices->cap)
      vertices->data =
          s_realloc(vertices->data, (vertices->cap *= 2) * sizeof(float));

    if (vertices->data != NULL)
      vertices->data[vertices->len++] = vertex;
    else
      memset(vertices, 0, sizeof(vert_t));
  }
}

void vertices_free(vert_t *vertices) {
  if (vertices != NULL) {
    if (vertices->data != NULL) free(vertices->data);
    memset(vertices, 0, sizeof(vert_t));
  }
}

int indices_is_init(idx_t *i) {
  return i != NULL && i->data != NULL && i->cap > 0;
}

int indices_create(idx_t *dest, int capacity) {
  int res = 1;

  if (dest != NULL && capacity > 0) {
    memset(dest, 0, sizeof(idx_t));

    if ((dest->data = calloc(capacity, sizeof(unsigned int))) != NULL) {
      dest->cap = capacity;
      res = 0;
    }
  }

  return res;
}

void indices_push(idx_t *indices, unsigned int index) {
  if (indices_is_init(indices)) {
    if (indices->len + 1 == indices->cap)
      indices->data =
          s_realloc(indices->data, (indices->cap *= 2) * sizeof(unsigned int));

    if (indices->data != NULL)
      indices->data[indices->len++] = index;
    else
      memset(indices, 0, sizeof(idx_t));
  }
}

void indices_free(idx_t *indices) {
  if (indices != NULL) {
    if (indices->data != NULL) free(indices->data);
    memset(indices, 0, sizeof(idx_t));
  }
}

void parse_vertex(const char *line, vert_t *vertices) {
  if (line != NULL && vertices != NULL) {
    float x, y, z;

    sscanf(line, "%f %f %f", &x, &y, &z);
    vertices_push(vertices, x);
    vertices_push(vertices, y);
    vertices_push(vertices, z);
  }
}

void parse_index(char *line, idx_t *indices) {
  if (line != NULL && indices != NULL) {
    idx_t tmp;
    char *token = strtok(line, " ");
    int count = 0;
    unsigned int first_idx;

    indices_create(&tmp, 4);

    while (token != NULL) {
      unsigned int idx;

      sscanf(token, "%u%*s", &idx);
      indices_push(&tmp, idx - 1);

      if (count == 0) first_idx = idx - 1;

      token = strtok(NULL, " ");
      count++;
    }

    indices_push(indices, first_idx);

    for (size_t i = 1; i < tmp.len; i++) {
      indices_push(indices, tmp.data[i]);
      indices_push(indices, tmp.data[i]);
    }

    indices_push(indices, first_idx);

    indices_free(&tmp);
  }
}

void model_create(model_t *model) {
  if (model != NULL) {
    vertices_create(&model->vertices, 128);
    indices_create(&model->indices, 128);
  }
}

void model_free(model_t *model) {
  if (model != NULL) {
    vertices_free(&model->vertices);
    indices_free(&model->indices);
  }
}

int parser_v2(model_t *model, const char *filename) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;

  fp = fopen(filename, "r");

  if (fp != NULL) {
    while (getline(&line, &len, fp) != -1) {
      if (!strncmp(line, "v ", 2)) {
        parse_vertex(&(line + 2)[0], &model->vertices);

      } else if (!strncmp(line, "f ", 2))
        parse_index(&(line + 2)[0], &model->indices);
    }

    fclose(fp);
    if (line) free(line);
  }

  return 0;
}
