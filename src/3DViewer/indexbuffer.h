#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer {
 private:
  unsigned int m_RendererId;
  unsigned int m_Count;

 public:
  IndexBuffer();
  ~IndexBuffer();

  void generate();
  void setData(const unsigned int *data, unsigned int count);
  unsigned int getCount() { return m_Count; }

  void bind();
  void unbind();
};

#endif  // INDEXBUFFER_H
