#include"BatchRenderer.h"

void BatchRenderer::Add(GameObject* go) {
	auto itr = std::find(objectsForRender.begin(), objectsForRender.end(), go);
	//the object is already in the vector
	if (itr != objectsForRender.end()) return;
   
    objectsForRender.push_back(go);
}

void BatchRenderer::Render() {
	for (int i = 0; i < objectsForRender.size(); i++) {
        //if the position/color/texture of any object changed
        if (objectsForRender[i]->GetComponent<Transform>()->IsDirty() || objectsForRender[i]->GetComponent<SpriteRenderer>()->IsDirty() || oneTimeFlag) {
            LoadVerticesData(i);
            //std::cout << "Need to rebuffer data :/" << std::endl;
            rebufferData = true;
        }
	}
    //this is one of the stupidest things I did as a programmer, but it works
    oneTimeFlag = false;
    //TestVertices();
    if (rebufferData) {
        SetupBuffers();
        rebufferData = false;
    }

    Shader shader = AssetsPool::Get().GetShader("Assets/shaders/shader.shader");
    shader.UseProgram();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

BatchRenderer::BatchRenderer() {
	vertices = new float[MAX_BATCH_SIZE * VERTICES_DATA_FOR_QUAD];

	vertexArray = new VertexArray();

	vertexBufferLayout.AddFloat(2); //position vertex
	vertexBufferLayout.AddFloat(3); //color vertex
	vertexBufferLayout.AddFloat(2); //texture vertex
	vertexBufferLayout.AddFloat(1); //texture index

    SetupBuffers();
}

void BatchRenderer::LoadVerticesData(unsigned int gameObjectIndex) {
    GameObject* go = objectsForRender[gameObjectIndex];
    Transform* trans = go->GetComponent<Transform>();
    SpriteRenderer* rend = go->GetComponent<SpriteRenderer>();

    unsigned int texCoordsIndex = 0;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    unsigned int gameObjectOffset = gameObjectIndex * VERTICES_DATA_FOR_QUAD;

    //every iteration of the loop creates a single "point" of a quad
    for (int i = 0; i < 4; i++) {
        switch (i) {
        case 1:
            offsetX = QUAD_LENGTH;
            break;
        case 2:
            offsetX = 0.0f;
            offsetY = QUAD_LENGTH;
            break;
        case 3:
            offsetX = QUAD_LENGTH;
            break;
        default:
            break;
        }

        vertices[(0 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->x + offsetX;
        vertices[(1 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->y + offsetY;
        vertices[(2 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetR();
        vertices[(3 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetG();
        vertices[(4 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetB();
        vertices[(5 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        vertices[(6 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        vertices[(7 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexIndex();
    }
}

void BatchRenderer::TestVertices() {
    std::cout << "Vertices array" << std::endl;
    for (int i = 0; i < 2 * VERTICES_DATA_FOR_QUAD; i++) {
        if (i % DATA_IN_ONE_VERTEX == 0) std::cout << "new vertex " << std::endl;
        if (i % VERTICES_DATA_FOR_QUAD == 0) std::cout << "new game object" << std::endl;

        std::cout << "Element at index " << i << " | " << vertices[i] << std::endl;
    }
    ASSERT(false);
}

void BatchRenderer::SetupBuffers() {
    vertexBuffer = new VertexBuffer(objectsForRender.size() * VERTICES_DATA_FOR_QUAD * sizeof(float), vertices);
    vertexArray->AddVertexBuffer(*vertexBuffer, vertexBufferLayout);
    indexBuffer = new IndexBuffer(6 * objectsForRender.size());
}