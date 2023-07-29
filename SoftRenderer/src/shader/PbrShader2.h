#pragma once
#include "Shader.h"

//ao roughness metalness»˝’≈Ã˘Õº∑÷¿Î
class PbrShader2 :public Shader
{
	virtual void Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) override;
	virtual bool Fragment(glm::vec4& gl_fragColor) override;
	float DistributionGGX(const glm::vec3& N, const glm::vec3& H, float roughness);
	float GeometrySchlickGGX(float NdotV, float roughness);
	float GeometrySmith(const glm::vec3& N, const glm::vec3& V, const glm::vec3& L, float roughness);
	glm::vec3 FreshelSchlick(float cosTheta, const glm::vec3& F0);
};