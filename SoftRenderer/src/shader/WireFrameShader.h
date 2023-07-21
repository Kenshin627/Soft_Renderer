#pragma once
#include "Shader.h"

class WireFrameShader : public Shader
{
public:
	WireFrameShader(float lineWidth) :lineWidth(lineWidth) {}
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_FragColor) override;
public:
	glm::vec3 vertexIntensity;
	float lineWidth;
};