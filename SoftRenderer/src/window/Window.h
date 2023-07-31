#pragma once
#include "../renderer/Renderer.h"
#include <glm/glm.hpp>
#include <SDL.h>

class Window
{
public:
	Window(const char* title, uint32_t width, uint32_t height);
	void SetRenderer(Renderer* renderer) { softRenderer = renderer; }
	~Window();
	void ShutDowm();
	void DrawPoint(int x, int y, const glm::vec3& color, bool flip = true);
	void Clear();
	void Run();
private:
	SDL_Window* windowHandle = nullptr;
	SDL_Renderer* drawHnadle = nullptr;
	Renderer* softRenderer = nullptr;
	bool shouldClosed = false;
	glm::vec3 clearColor = { 10/255, 10/255, 10/255 };
	glm::mat3 sdlTransform;
};