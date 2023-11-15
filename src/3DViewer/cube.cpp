#include "cube.h"

Cube::Cube()
    : m_Vertices({
          -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0,  -1.0, -1.0, 1.0,  1.0, -1.0,
          1.0,  -1.0, 1.0,  1.0,  1.0, 1.0,  -1.0, -1.0, 1.0,  -1.0, 1.0, 1.0,
      }),

      m_Indices({
          1, 2, 4, 3, 4, 6, 5, 6, 8, 7, 8, 2, 2, 8, 6, 7, 1, 3,
          1, 4, 3, 3, 6, 5, 5, 8, 7, 7, 2, 1, 2, 6, 4, 7, 3, 5,
      }) {
  for (auto& idx : m_Indices) idx -= 1;
}

void Cube::toScreenSpace(float width, float height, float depth) {
  int pos_idx = 0;
  for (int i = 0; i < (int)m_Vertices.size(); i++, pos_idx++) {
    if (pos_idx == 0) {
      m_Vertices[i] = (m_Vertices[i] + 1) * width;
    } else if (pos_idx == 1) {
      m_Vertices[i] = (m_Vertices[i] + 1) * height;
    } else if (pos_idx == 2) {
      m_Vertices[i] = (m_Vertices[i] + 1) * depth;
      pos_idx = -1;
    }
  }
}
