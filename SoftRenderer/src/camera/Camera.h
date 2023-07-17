#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fov, float aspect, float near, float far);
	void Update();
	const glm::vec3& Position() const { return position; }
	const glm::mat4& View() const { return view; }
	const glm::mat4& Projection() const { return projection; }
	const glm::mat4 ViewProjection() const { return viewProjection; }
private:
	glm::vec3 position;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 viewProjection;
};