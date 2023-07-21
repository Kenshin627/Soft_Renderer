#pragma once
#include "Shader.h"

class PixelShader : public Shader
{
public:
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_FragColor) override;
public:
	glm::vec3 normals[3];
};