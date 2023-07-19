#pragma once
#include "../camera/Camera.h"
#include <glm/glm.hpp>

class DirectionLight
{
public:
	DirectionLight(const glm::vec3& dir, const glm::vec3& color);
	void BuildLightSpace();
	const glm::vec3& Direction() const { return direction; }
	const glm::vec3& Color() const { return color; }
	const Camera& GetLightSpace() const { return lightSpace; }
private:
	glm::vec3 direction;
	glm::vec3 color;
	Camera lightSpace;
};