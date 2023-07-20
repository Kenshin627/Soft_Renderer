#pragma once
#include "../renderer/Triangle.h"
#include "../light/DirectionLight.h"
#include "../renderer/FrameBuffer.h"
#include "../texture/Texture.h"
#include <memory>
#include <glm/glm.hpp>

enum ShaderType
{
	BlinnPhong = 0,
	Toon,
	Shadow,
	BlinnPhongWithShadow
};

class Shader
{
public:
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) = 0;
	virtual bool Fragment(glm::vec4& gl_fragColor) = 0;
	virtual void SetSampler(uint32_t slot, const std::shared_ptr<Texture>& texture);
	virtual glm::vec3 Sampler2D(const glm::vec2& uv, const std::shared_ptr<Texture>& texture);
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
	std::shared_ptr<Texture> diffuseTexture; //slot 0
	std::shared_ptr<Texture> specularTexture;//slot 1
	std::shared_ptr<Texture> tbnNormalTexture;//slot 2

	//TBN
	glm::vec3 tangent;
	glm::vec3 biTangent;

	//shadowMap
	std::shared_ptr<FrameBuffer> shadowBuffer;
	glm::mat4 viewport;
};