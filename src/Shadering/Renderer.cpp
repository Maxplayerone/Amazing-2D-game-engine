#include"Renderer.h"


void Renderer::ChangeBGColor(float r, float g, float b, float a) const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

void Renderer::Setup(const unsigned int numOfQuads, GameObject* go, const unsigned int height) {
    const int BUFFER_SIZE = numOfQuads * VerticesCreator::QUAD_VERTEX_LENGTH;
    float* vertices = new float[BUFFER_SIZE];

    VerticesCreator* creator = new VerticesCreator();
    if (numOfQuads == 1)
        vertices = creator->CreateVerticesForQuad(go->GetComponent<Transform>(), go->GetComponent<SpriteRenderer>());
    else if (numOfQuads > 1)
        vertices = creator->CreateVerticesForBatch(numOfQuads, go->GetComponent<Transform>(), go->GetComponent<SpriteRenderer>(), height);
    
    vertexArray = new VertexArray();
    vertexBuffer = new VertexBuffer(BUFFER_SIZE * sizeof(float), vertices);

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.AddFloat(2); //position vertex
    vertexBufferLayout.AddFloat(3); //color vertex
    vertexBufferLayout.AddFloat(2); //texture vertex
    vertexBufferLayout.AddFloat(1); //texture index

    vertexArray->AddVertexBuffer(*vertexBuffer, vertexBufferLayout);

    indexBuffer = new IndexBuffer(6 * numOfQuads * numOfQuads); 
}

void Renderer::DrawSingle(GameObject* go, Shader& shaderProgram) {

    //TODO: caching or something
    Setup(1, go, 0);
    shaderProgram.UseProgram();

    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
    
}

void Renderer::DrawBatch(GameObject* go, Shader& shaderProgram, const unsigned int quadCount, const unsigned int height) {
    Setup(quadCount, go, height);
    shaderProgram.UseProgram();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

