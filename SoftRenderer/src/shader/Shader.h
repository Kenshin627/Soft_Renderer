#pragma once
#include "../renderer/Triangle.h"
#include "../light/DirectionLight.h"
#include <memory>
#include <glm/glm.hpp>

enum ShaderType
{
	BlinnPhong = 0,
	Toon
};

class Shader
{
public:
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) = 0;
	virtual bool Fragment(glm::vec4& gl_fragColor) = 0;
public:
	Triangle triangle;
	glm::vec3 baryCentric;
	//uniforms
	glm::mat4 model;
	glm::mat3 itModel;
	glm::mat4 viewProjection;
	std::shared_ptr<DirectionLight> light;
};