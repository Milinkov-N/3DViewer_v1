#include "vertexbuffer.h"

#include "utl.h"

VertexBuffer::VertexBuffer() {}

VertexBuffer::~VertexBuffer() {
  utl::GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::generate() { utl::GLCall(glGenBuffers(1, &m_RendererId)); }

void VertexBuffer::setData(const void *data, unsigned int size) {
  utl::GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
  utl::GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() {
  utl::GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::unbind() { utl::GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
