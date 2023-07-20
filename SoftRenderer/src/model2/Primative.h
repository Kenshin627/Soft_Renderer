#pragma once
#include<glm/glm.hpp>
#include <vector>

class Primative
{
public:
	Primative() = default;
	~Primative() = default;
	const glm::vec3& GetPosition(uint32_t nface, uint32_t triangleVertexIndex) const;
	void InerstPosition(float x, float y, float z);
	void InsertNormal(float x, float y, float z);
	void InsertUV(float u, float v);
	const glm::vec3& GetNormal(uint32_t nface, uint32_t triangleVertexIndex) const;
	const glm::vec2& GetUv(uint32_t nface, uint32_t triangleVertexIndex) const;
private:
	uint32_t nface;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
};