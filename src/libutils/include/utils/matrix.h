#ifndef VIEWER_3D_SRC_UTILS_MATRIX_H_
#define VIEWER_3D_SRC_UTILS_MATRIX_H_

#include <math.h>

typedef struct mat4 {
  float data[16];
} mat4_t;

mat4_t mat4_orthographic(float left, float right, float bottom, float top,
                         float near, float far);

mat4_t mat4_perspective(float fovRadians, float aspect, float near, float far);

mat4_t mat4_translation(float tx, float ty, float tz);

mat4_t mat4_x_rotation(float radians);

mat4_t mat4_y_rotation(float radians);

mat4_t mat4_z_rotation(float radians);

mat4_t mat4_scaling(float sx, float sy, float sz);

mat4_t mat4_multiply(mat4_t* mat, mat4_t* other);

#endif  // VIEWER_3D_SRC_UTILS_MATRIX_H_
