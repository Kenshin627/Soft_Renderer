#pragma once
#include "Shader.h"

class MosaicShader :public Shader
{
public:
	MosaicShader(uint32_t size);
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_FragColor) override;
	void SetCurentPixel(const glm::vec2& p);
	void BindPrePassColorAttachment(const TGAImage& image) { prePassColorAttachment = image; }
private:
	float pixelSize;
};