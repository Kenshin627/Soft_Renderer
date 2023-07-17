#pragma once
#include <glm/glm.hpp>

class DirectionLight
{
public:
	DirectionLight(const glm::vec3& dir, const glm::vec3& color);
	const glm::vec3& Direction() const { return direction; }
	const glm::vec3& Color() const { return color; }
private:
	glm::vec3 direction;
	glm::vec3 color;
};