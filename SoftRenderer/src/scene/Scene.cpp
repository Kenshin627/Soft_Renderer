#include "Scene.h"
#include "../model2/ModelLoader.h"

Scene::Scene() {}

void Scene::LoadModel(const char* path)
{
	//models.emplace_back(path);
	ModelLoader::Parse(path);
}

void Scene::InitCamera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fov, float aspect, float near, float far)
{
	camera = std::make_shared<Camera>(eye, center, up);
	camera->Perspective(fov, aspect, near, far);
}

void Scene::InitLight(const glm::vec3& dir, const glm::vec3& color)
{
	light = std::make_shared<DirectionLight>(dir, color);
}