#include"IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int indiciesCount, const void* indiciesPointer)
    : m_indiciesCount(indiciesCount) {
    GLCall(glGenBuffers(1, &m_BufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indiciesCount, indiciesPointer, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_BufferID);
}

void IndexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}