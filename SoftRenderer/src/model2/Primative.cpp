#include "Primative.h"

const glm::vec3& Primative::GetPosition(uint32_t nface, uint32_t triangleVertexIndex) const
{
	return positions[nface * 3 + triangleVertexIndex];
}

const glm::vec3& Primative::GetNormal(uint32_t nface, uint32_t triangleVertexIndex) const
{
	return normals[nface * 3 + triangleVertexIndex];
}

const glm::vec2& Primative::GetUv(uint32_t nface, uint32_t triangleVertexIndex) const
{
	return uvs[nface * 3 + triangleVertexIndex];
}

void Primative::InerstPosition(float x, float y, float z)
{
	positions.emplace_back(x, y, z);
}

void Primative::InsertNormal(float x, float y, float z)
{
	normals.emplace_back(x, y, z);
}

void Primative::InsertUV(float u, float v)
{
	uvs.emplace_back(u, v);
}