#include "utils.h"

mat4_t mat4_orthographic(float left, float right, float bottom, float top,
                         float near, float far) {
  mat4_t matrix = {{
      2 / (right - left),
      0,
      0,
      0,
      0,
      2 / (top - bottom),
      0,
      0,
      0,
      0,
      2 / (near - far),
      0,
      (left + right) / (left - right),
      (bottom + top) / (bottom - top),
      (near + far) / (near - far),
      1,
  }};

  return matrix;
}

mat4_t mat4_perspective(float fovRadians, float aspect, float near, float far) {
  float f = tanf(M_PI * 0.5f - 0.5f * fovRadians);
  float rangeInv = 1.0f / (near - far);
  mat4_t matrix = {{f / aspect, 0, 0, 0, 0, f, 0, 0, 0, 0,
                    (near + far) * rangeInv, -1.0f, 0, 0,
                    near * far * rangeInv * 2.0f, 0}};

  return matrix;
}

mat4_t mat4_translation(float tx, float ty, float tz) {
  mat4_t matrix = {{
      1,
      0,
      0,
      0,
      0,
      1,
      0,
      0,
      0,
      0,
      1,
      0,
      tx,
      ty,
      tz,
      1,
  }};

  return matrix;
}

mat4_t mat4_x_rotation(float radians) {
  float sine = sin(radians);
  float cosine = cos(radians);
  mat4_t matrix = {{
      1,
      0,
      0,
      0,
      0,
      cosine,
      sine,
      0,
      0,
      -sine,
      cosine,
      0,
      0,
      0,
      0,
      1,
  }};

  return matrix;
}

mat4_t mat4_y_rotation(float radians) {
  float sine = sin(radians);
  float cosine = cos(radians);
  mat4_t matrix = {{
      cosine,
      0,
      -sine,
      0,
      0,
      1,
      0,
      0,
      sine,
      0,
      cosine,
      0,
      0,
      0,
      0,
      1,
  }};

  return matrix;
}

mat4_t mat4_z_rotation(float radians) {
  float sine = sin(radians);
  float cosine = cos(radians);
  mat4_t matrix = {{
      cosine,
      sine,
      0,
      0,
      -sine,
      cosine,
      0,
      0,
      0,
      0,
      1,
      0,
      0,
      0,
      0,
      1,
  }};

  return matrix;
}

mat4_t mat4_scaling(float sx, float sy, float sz) {
  mat4_t matrix = {{
      sx,
      0,
      0,
      0,
      0,
      sy,
      0,
      0,
      0,
      0,
      sz,
      0,
      0,
      0,
      0,
      1,
  }};

  return matrix;
}

mat4_t mat4_multiply(mat4_t* mat, mat4_t* other) {
  mat4_t out = {0};

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        out.data[i * 4 + j] += mat->data[i * 4 + k] * other->data[k * 4 + j];

  return out;
}
