#pragma once
#include"../Utils/ErrorHandling.h"

class IndexBuffer {
private:
	unsigned int m_BufferID;
	unsigned int m_indiciesCount;
public:
	IndexBuffer(unsigned int indiciesCount, const void* indiciesPointer);
	~IndexBuffer();
	void Bind();
	void Unbind();
	unsigned int GetCount() { return m_indiciesCount; }
};
