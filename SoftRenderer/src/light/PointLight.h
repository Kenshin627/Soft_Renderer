#pragma once
#include <glm/glm.hpp>

class PointLight
{
public:
	PointLight(const glm::vec3& position, const glm::vec3& color);
	const glm::vec3& GetPosition() const { return position; }
	const glm::vec3& GetColor() const { return color; }
private:
	glm::vec3 position;
	glm::vec3 color;
};