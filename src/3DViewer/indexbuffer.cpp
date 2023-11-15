#include "indexbuffer.h"

#include "utl.h"

IndexBuffer::IndexBuffer() : m_Count(0) {}

IndexBuffer::~IndexBuffer() { utl::GLCall(glDeleteBuffers(1, &m_RendererId)); }

void IndexBuffer::generate() { utl::GLCall(glGenBuffers(1, &m_RendererId)); }

void IndexBuffer::setData(const unsigned int *data, unsigned int count) {
  m_Count = count;
  utl::GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
  utl::GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                           count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::bind() {
  utl::GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::unbind() {
  utl::GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
