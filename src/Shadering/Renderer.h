#pragma once
#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VerticesCreator.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/VertexBufferLayout.h"

#include"Shader.h"

#include<iostream>
#include<unordered_map>

class Renderer {
public:
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	void ChangeBGColor(float r, float g, float b, float a) const;

	//draws a single quad
	void DrawSingle(GameObject* go, Shader& shaderProgram);
	void DrawBatch(GameObject* go, Shader& shaderProgram, const unsigned int quadCount, const unsigned int height);

	//setup vertex array, vertex buffer and other funny stuff
	void Setup(const unsigned int numOfQuads, GameObject* go, const unsigned int height);
};