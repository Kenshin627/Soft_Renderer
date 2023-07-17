#pragma once
#include <glm/glm.hpp>

struct VertexAttribute
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Triangle
{
	VertexAttribute* vertices = new VertexAttribute[3];
};