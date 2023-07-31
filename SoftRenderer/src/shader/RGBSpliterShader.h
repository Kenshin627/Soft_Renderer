#pragma once
#include "Shader.h"

class RGBSpliterShader :public Shader
{
public:
	RGBSpliterShader(const glm::vec2& offset);
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_fragColor) override;
	void SetCurentPixel(const glm::vec2& p);
	void BindPrePassColorAttachment(const TGAImage& image) { prePassColorAttachment = image; }
private:
	glm::vec2 offset;
};