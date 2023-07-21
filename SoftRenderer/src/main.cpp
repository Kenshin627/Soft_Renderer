#include "window/Window.h"
#include <glm/gtc/type_ptr.hpp>
int main(int argc, char* argv[])
{
	uint32_t width = 1920;
	uint32_t height = 1080;
	float aspect = (float)width / height;

	//1.Scene
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	//scene->LoadModel("resource/models/head/head/african_head.obj");
	//scene->LoadModel("resource/models/head/eye_inner/african_head_eye_inner.obj");
	//scene->LoadModel("resource/models/head/eye_outter/african_head_eye_outer.obj");

	scene->LoadModel("resource/models/FlightHelmet/FlightHelmet.obj");

	scene->InitLight({ -1, -1, -1 }, { 1, 1, 1 });
	scene->InitCamera({ 0.5f, 1.0f, 0.8f }, { 0, 0.3, 0 }, { 0, 1, 0 }, 1.0f / glm::four_over_pi<float>(), aspect, 0.01f, 10.0f);

	//2. Renderer
	Renderer renderer;
	renderer.InitShaders();
	renderer.SetViewport(0, 0, width, height);
	renderer.BeginScene(scene);

	//3. Window
	Window window{ "softRenderer", width, height };
	window.SetRenderer(&renderer);
	window.Run();
	window.ShutDowm();
	return 0;
}