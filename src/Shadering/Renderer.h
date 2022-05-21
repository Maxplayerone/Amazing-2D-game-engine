#pragma once
#include"../Buffers/IndexBuffer.h"
#include"Shader.h"
#include"../Buffers/VertexArray.h"

class Renderer {
public:
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shaderProgram);
	void ChangeBGColor(float r, float g, float b, float a) const;
};