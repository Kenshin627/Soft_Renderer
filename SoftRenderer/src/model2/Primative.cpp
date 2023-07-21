#include "Primative.h"

Primative::Primative(uint32_t nface):nface(nface) 
{
	positions = new glm::vec3[nface * 3];
	normals   = new glm::vec3[nface * 3];
	uvs       = new glm::vec2[nface * 3];
}

const glm::vec3& Primative::GetPosition(uint32_t nface, uint32_t triangleVertexIndex) const
{
	return positions[nface * 3 + triangleVertexIndex];
}

const glm::vec3& Primative::GetNormal(uint32_t nface, uint32_t triangleVertexIndex) const
{
	return normals[nface * 3 + triangleVertexIndex];
}

const glm::vec2& Primative::GetUV(uint32_t nface, uint32_t triangleVertexIndex) const
{
	return uvs[nface * 3 + triangleVertexIndex];
}

void Primative::InerstPosition(uint32_t idx, float x, float y, float z)
{
	positions[idx] = { x, y, z };
}

void Primative::InsertNormal(uint32_t idx, float x, float y, float z)
{
	normals[idx] = glm::normalize(glm::vec3(x, y, z));
}

void Primative::InsertUV(uint32_t idx, float u, float v)
{
	uvs[idx] = { u, v };
}