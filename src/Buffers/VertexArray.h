#pragma once
#include"VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
private:
	unsigned int m_BufferID;
public:
	VertexArray();
	~VertexArray();

	void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};
