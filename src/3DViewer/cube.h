#ifndef CUBE_H
#define CUBE_H

#include <vector>

class Cube {
 private:
  std::vector<float> m_Vertices;
  std::vector<unsigned int> m_Indices;

 public:
  Cube();

  const std::vector<float>& getVertices() const { return m_Vertices; }
  const std::vector<unsigned int>& getIndices() const { return m_Indices; }

  void toScreenSpace(float width, float height, float depth);
};

#endif  // CUBE_H
