#include"Renderer.h"

void Renderer::ChangeBGColor(float r, float g, float b, float a) const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shaderProgram) {
	va.Bind();
	ib.Bind();
	shaderProgram.UseProgram();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr))
}