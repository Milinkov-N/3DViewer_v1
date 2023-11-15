#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
 private:
  unsigned int m_RendererId;

 public:
  VertexBuffer();
  ~VertexBuffer();

  void generate();
  void setData(const void *data, unsigned int size);

  void bind();
  void unbind();
};

#endif  // VERTEXBUFFER_H
