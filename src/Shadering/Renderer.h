#pragma once
#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VerticesCreator.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/VertexBufferLayout.h"

#include"Shader.h"

#include<iostream>
#include<unordered_map>

struct RegisterObject {
	GameObject* m_gameObject;
	float* vertices;
	bool isBatched;
};


struct checkObjectDiagnosis {
	bool inRegisterObjects;
	bool isBatched;
};

#define MAX_OBJECT_COUNT 1000

class Renderer {
private:
	RegisterObject m_registeredObjects[MAX_OBJECT_COUNT];
	unsigned int m_vectorIndex = 0;

	VertexBufferLayout vertexBufferLayout;
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VerticesCreator* creator;

	void Setup(const unsigned int numOfQuads, GameObject* go, float* vertices);
	//check if the game object is in m_registerObjects
	checkObjectDiagnosis CheckGameObject(GameObject* go);
	RegisterObject GetRegisterObject(GameObject* go);
public:

	Renderer();

	void ChangeBGColor(float r, float g, float b, float a) const;
	
	//draws a single quad
	void DrawSingle(GameObject* go, Shader& shaderProgram);
	void DrawBatch(GameObject* go, Shader& shaderProgram, const unsigned int quadCount, const unsigned int height);	

	unsigned int GetRegisterObjectsLen() const { return m_vectorIndex; }
};