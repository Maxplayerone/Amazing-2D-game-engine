#pragma once
#include<iostream>
#include"../ECS/GameObject.h"



//TODO: ADD TEXTURE INDEX TO VERTICES ARRAY

class VerticesCreator{
private:
	//checks if the modulo of checkedNum (and num * vertexSize, num * (2 * vetexSize)... because it's a quad) is 0
	bool IsMultiplication(int checkedNum, int modulo) {
		for (int i = 0; i < 4; i++) {
			if ((checkedNum % (modulo + (vertexSize * i))) != 0) return false;
		}
	}
public:
	//the size of the X wall of the cube
	float quadSizeX = 1.0f;
	//the size of the Y wall of the cube
	float quadSizeY = 1.0f;
	//the amount of data in one vertex (position * 2, color * 3, texture * 2)
	const int vertexSize = 8;

	//the amount of data needed for a single quad buffer
	const static int QUAD_VERTEX_LENGTH = 32;

	float* CreateVerticesForQuad(Transform* startingPos, SpriteRenderer* rend) {
		//4 * (2  * position data, 3 * color data, 2 * texture data)

		float* vertices = new float[QUAD_VERTEX_LENGTH];
		float* texCoords = rend->GetTexCoords();

		//left-bottom
		for (int i = 0; i < QUAD_VERTEX_LENGTH; i++) {
				vertices[0] = startingPos->x;
				vertices[1] = startingPos->y;
				vertices[2] = rend->r;
				vertices[3] = rend->g;
				vertices[4] = rend->b;
				vertices[5] = texCoords[0];
				vertices[6] = texCoords[1];
				vertices[7] = rend->GetTexIndex();

				//right-bottom
				vertices[8] = startingPos->x + quadSizeX;
				vertices[9] = startingPos->y;
				vertices[10] = rend->r;
				vertices[11] = rend->g;
				vertices[12] = rend->b;
				vertices[13] = texCoords[2];
				vertices[14] = texCoords[3];
				vertices[15] = rend->GetTexIndex();

				//left-top
				vertices[16] = startingPos->x;
				vertices[17] = startingPos->y + quadSizeY;
				vertices[18] = rend->r;
				vertices[19] = rend->g;
				vertices[20] = rend->b;
				vertices[21] = texCoords[4];
				vertices[22] = texCoords[5];
				vertices[23] = rend->GetTexIndex();

				//right-top
				vertices[24] = startingPos->x + quadSizeX;
				vertices[25] = startingPos->y + quadSizeY;
				vertices[26] = rend->r;
				vertices[27] = rend->g;
				vertices[28] = rend->b;
				vertices[29] = texCoords[6];
				vertices[30] = texCoords[7];
				vertices[31] = rend->GetTexIndex();
		}

		return vertices;
	}

	//creates a box of quads starting at a specified position
	float* CreateVerticesForBatch(unsigned int quadCount, Transform* startingPos, SpriteRenderer* rend, unsigned int height) {

		//how far are the cubes from each other
		float offsetX = 1.0f;
		float offsetY = -1.0f;

		//the amount of data in one quad (vertex * 4 (because cube lol)
		unsigned int quadBuffer = vertexSize * 4;
		//the amount of quads * the amount of data in one quad
		const unsigned int verticesArraySize = quadCount * quadBuffer;
		float* vertices = new float[verticesArraySize];

		float* texCoords = rend->GetTexCoords();


		if (quadCount % 2 != 0) {
			//test code. Change later
			std::cout << "The quad count should be bigger than 2";
			return nullptr;
		}

		unsigned int width = quadCount / height;
		unsigned int offset = 0;

		for (unsigned int j = 0; j < height; j++) {
			for (unsigned int i = 0; i < width; i++) {

				//left-bottom
				vertices[0 + (offset * quadBuffer)] = startingPos->x + (i * offsetX);
				vertices[1 + (offset * quadBuffer)] = startingPos->y + (j * offsetY);
				vertices[2 + (offset * quadBuffer)] = rend->r;
				vertices[3 + (offset * quadBuffer)] = rend->b;
				vertices[4 + (offset * quadBuffer)] = rend->g;
				vertices[5 + (offset * quadBuffer)] = 0.0f;
				vertices[6 + (offset * quadBuffer)] = 0.0f;
				vertices[7 + (offset * quadBuffer)] = rend->GetTexIndex();

				//right-bottom
				vertices[8 + (offset * quadBuffer)] = startingPos->x + quadSizeX + (i * offsetX);
				vertices[9 + (offset * quadBuffer)] = startingPos->y + (j * offsetY);
				vertices[10 + (offset * quadBuffer)] = rend->r;
				vertices[11 + (offset * quadBuffer)] = rend->g;
				vertices[12 + (offset * quadBuffer)] = rend->b;
				vertices[13 + (offset * quadBuffer)] = 1.0f;
				vertices[14 + (offset * quadBuffer)] = 0.0f;
				vertices[15 + (offset * quadBuffer)] = rend->GetTexIndex();

				//left-top
				vertices[16 + (offset * quadBuffer)] = startingPos->x + (i * offsetX);
				vertices[17 + (offset * quadBuffer)] = startingPos->y + quadSizeY + (j * offsetY);
				vertices[18 + (offset * quadBuffer)] = rend->r;
				vertices[19 + (offset * quadBuffer)] = rend->g;
				vertices[20 + (offset * quadBuffer)] = rend->b;
				vertices[21 + (offset * quadBuffer)] = 0.0f;
				vertices[22 + (offset * quadBuffer)] = 1.0f;
				vertices[23 + (offset * quadBuffer)] = rend->GetTexIndex();

				//right-top
				vertices[24 + (offset * quadBuffer)] = startingPos->x +  + quadSizeX + (i * offsetX);
				vertices[25 + (offset * quadBuffer)] = startingPos->y + quadSizeY + (j * offsetY);
				vertices[26 + (offset * quadBuffer)] = rend->r;
				vertices[27 + (offset * quadBuffer)] = rend->g;
				vertices[28 + (offset * quadBuffer)] = rend->b;
				vertices[29 + (offset * quadBuffer)] = 1.0f;
				vertices[30 + (offset * quadBuffer)] = 1.0f;
				vertices[31 + (offset * quadBuffer)] = rend->GetTexIndex();

				offset++;

			}
		}

		return vertices;
	}
};
