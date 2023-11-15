#ifndef VIEWER_3D_SRC_UTILS_OBJ_PARSER_H_
#define VIEWER_3D_SRC_UTILS_OBJ_PARSER_H_

typedef struct vertices {
  size_t cap;
  size_t len;
  float* data;
} vert_t;

int vertices_is_init(vert_t* v);

int vertices_create(vert_t* dest, int capacity);

void vertices_push(vert_t* vertices, float vertex);

void vertices_free(vert_t* vertices);

typedef struct indices {
  size_t cap;
  size_t len;
  unsigned int* data;
} idx_t;

int indices_is_init(idx_t* i);

int indices_create(idx_t* dest, int capacity);

void indices_push(idx_t* indices, unsigned int index);

void indices_free(idx_t* indices);

typedef struct model {
  vert_t vertices;
  idx_t indices;
} model_t;

void model_create(model_t* model);

void model_free(model_t* model);

int parser_v2(model_t* model, const char* filename);

#endif  // VIEWER_3D_SRC_UTILS_OBJ_PARSER_H_
