#pragma once
#include<glm/glm.hpp>
#include <vector>

class Primative
{
public:
	Primative(uint32_t nface);
	~Primative() = default;
	const glm::vec3& GetPosition(uint32_t nface, uint32_t triangleVertexIndex) const;
	void InerstPosition(uint32_t idx, float x, float y, float z);
	void InsertNormal(uint32_t idx, float x, float y, float z);
	void InsertUV(uint32_t idx, float u, float v);
	const glm::vec3& GetNormal(uint32_t nface, uint32_t triangleVertexIndex) const;
	const glm::vec2& GetUV(uint32_t nface, uint32_t triangleVertexIndex) const;
	const uint32_t getNface() const { return nface; }
private:
	uint32_t nface;
	glm::vec3* positions;
	glm::vec3* normals;
	glm::vec2* uvs;
};