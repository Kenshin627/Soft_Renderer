#pragma once
#include "Shader.h"

class ShadowShader:public Shader
{
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_fragColor) override;
};