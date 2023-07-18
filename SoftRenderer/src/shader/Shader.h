#pragma once
#include "../renderer/Triangle.h"
#include "../light/DirectionLight.h"
#include <memory>
#include <glm/glm.hpp>
#include <tgaimage/tgaimage.h>

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
	virtual void SetSampler(uint32_t slot, const TGAImage& texture);
	virtual glm::vec3 Sampler2D(const glm::vec2& uv, const TGAImage& texture);
public:
	Triangle triangle;
	glm::vec3 baryCentric;
	//uniforms
	glm::mat4 model;
	glm::mat3 itModel;
	glm::mat4 viewProjection;
	std::shared_ptr<DirectionLight> light;
	glm::vec3 camPos;
	//samplers
	TGAImage diffuseTexture; //slot 0
	TGAImage specularTexture;//slot 1
	TGAImage tbnNormalTexture;//slot 2

	//TBN
	glm::vec3 tangent;
	glm::vec3 biTangent;
};