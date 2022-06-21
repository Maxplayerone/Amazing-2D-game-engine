#include"Renderer.h"


void Renderer::ChangeBGColor(float r, float g, float b, float a) const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

Renderer::Renderer() {
    vertexArray = new VertexArray();

    vertexBufferLayout.AddFloat(2); //position vertex
    vertexBufferLayout.AddFloat(3); //color vertex
    vertexBufferLayout.AddFloat(2); //texture vertex
    vertexBufferLayout.AddFloat(1); //texture index

    creator = new VerticesCreator();
}

void Renderer::Setup(const unsigned int numOfQuads, GameObject* go, float* vertices) {
    
    const int BUFFER_SIZE = numOfQuads * VerticesCreator::QUAD_VERTEX_LENGTH;
    /*
    float* vertices = new float[BUFFER_SIZE];

    
    if (numOfQuads == 1)
        vertices = creator->CreateVerticesForQuad(go->GetComponent<Transform>(), go->GetComponent<SpriteRenderer>());
    else if (numOfQuads > 1)
        vertices = creator->CreateVerticesForBatch(numOfQuads, go->GetComponent<Transform>(), go->GetComponent<SpriteRenderer>(), height);
    */

    vertexBuffer = new VertexBuffer(BUFFER_SIZE * sizeof(float), vertices);

    vertexArray->AddVertexBuffer(*vertexBuffer, vertexBufferLayout);

    indexBuffer = new IndexBuffer(6 * numOfQuads); 
}

//EVALUATE THE BOOL IN REGISTEROBJECT HERE

checkObjectDiagnosis Renderer::CheckGameObject(GameObject* go) {
    checkObjectDiagnosis objDiagnosis;

    for (int i = 0; i < GetRegisterObjectsLen(); i++) {
        if (m_registeredObjects[i].m_gameObject->GetID() == go->GetID()) {
            objDiagnosis.inRegisterObjects = true;
            objDiagnosis.isBatched = m_registeredObjects[i].isBatched;
            return objDiagnosis;
        }
    }

    objDiagnosis.isBatched = false;
    objDiagnosis.inRegisterObjects = false;
    return objDiagnosis;
}

RegisterObject Renderer::GetRegisterObject(GameObject* go) {
    for (int i = 0; i < GetRegisterObjectsLen(); i++) {
        if (m_registeredObjects[i].m_gameObject->GetID() == go->GetID()) return m_registeredObjects[i];
    }
}

void Renderer::DrawSingle(GameObject* go, Shader& shaderProgram) {

    if (!CheckGameObject(go).inRegisterObjects && !CheckGameObject(go).isBatched) {
        RegisterObject obj;
        obj.m_gameObject = go;
        obj.vertices = creator->CreateVerticesForQuad(go->GetComponent<Transform>(), go->GetComponent<SpriteRenderer>());
        obj.isBatched = false;
        m_registeredObjects[m_vectorIndex++] = obj;

        Setup(1, go, obj.vertices);
    }
    else {
        Setup(1, go, GetRegisterObject(go).vertices);
    }

    
    shaderProgram.UseProgram();

    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
    
}

void Renderer::DrawBatch(GameObject* go, Shader& shaderProgram, const unsigned int quadCount, const unsigned int height) {
    if (!CheckGameObject(go).inRegisterObjects && CheckGameObject(go).isBatched) {
        RegisterObject obj;
        obj.m_gameObject = go;
        obj.vertices = creator->CreateVerticesForBatch(quadCount, go->GetComponent<Transform>(), go->GetComponent<SpriteRenderer>(), height);
        obj.isBatched = true;
        m_registeredObjects[m_vectorIndex++] = obj;

        Setup(quadCount, go, obj.vertices);
    }
    else {
        Setup(quadCount, go, GetRegisterObject(go).vertices);
    }

    shaderProgram.UseProgram();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

