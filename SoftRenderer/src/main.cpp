#include "window/Window.h"
#include <glm/gtc/type_ptr.hpp>
int main(int argc, char* argv[])
{
	uint32_t width = 1024;
	uint32_t height = 768;
	float aspect = (float)width / height;

	//1.Scene
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	scene->LoadModel("resource/models/head/head/african_head.obj");
	scene->InitLight({ -1, -1, -1 }, { 1, 1, 1 });
	scene->InitCamera({ 1,1,3 }, { 0, 0, 0 }, { 0, 1, 0 }, 1.0f / glm::four_over_pi<float>(), aspect, 0.01f, 10.0f);
	Renderer renderer;
	renderer.InitShaders();
	renderer.SetViewport(0, 0, width, height);
	renderer.BeginScene(scene);
	Window window{ "softRenderer", width, height };
	window.SetRenderer(&renderer);
	window.Run();
	window.ShutDowm();
	return 0;
}