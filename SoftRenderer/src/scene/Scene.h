#pragma once
#include "../model2/model2.h"
#include "../camera/Camera.h"
#include "../light/DirectionLight.h"
#include <vector>
#include <memory>

class Scene
{
public:
	Scene();
	void LoadModel(const char* path);
	void InitCamera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fov, float aspect, float near, float far);
	void InitLight(const glm::vec3& dir, const glm::vec3& color);
	const std::vector<Model2>& GetModels() const { return models; }
	const std::shared_ptr<Camera>& GetCamera() const { return camera; }
	const std::shared_ptr<DirectionLight>& GetLight() const { return light; }
private:
	std::vector<Model2> models;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<DirectionLight> light;
};