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
	void DrawPoint(int x, int y, const glm::vec3& color);
	void Clear();
	void Run();
private:
	SDL_Window* windowHandle;
	SDL_Renderer* drawHnadle;
	Renderer* softRenderer;
	bool shouldClosed = false;
	glm::vec3 clearColor = { 10/255, 10/255, 10/255 };
};