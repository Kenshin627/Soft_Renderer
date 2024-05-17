#pragma once
#include "Shader.h"

class PointShader : public Shader
{
public:
	PointShader() = default;
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_FragColor) override;
public:
	glm::vec3 vertexIntensity{ 0.0f, 0.0f, 0.0f };
};