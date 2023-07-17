#include "Window.h"
#include <iostream>

Window::Window(const char* title, uint32_t width, uint32_t height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "init sdlLibrary failed!" << std::endl;
	}
	windowHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	drawHnadle = SDL_CreateRenderer(windowHandle, -1, 0);
}

Window::~Window()
{
	ShutDowm();
}

void Window::ShutDowm()
{
	SDL_DestroyRenderer(drawHnadle);
	SDL_DestroyWindow(windowHandle);
	SDL_Quit();
}

void Window::Run()
{
	while (!shouldClosed)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			shouldClosed = true;
			return;
		}
		Clear();
		softRenderer->Clear();
		softRenderer->Draw(this);
	}
}

void Window::DrawPoint(int x, int y, const glm::vec3& color)
{
	SDL_SetRenderDrawColor(drawHnadle, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(drawHnadle, x, y);
}

void Window::Clear()
{
	SDL_SetRenderDrawColor(drawHnadle, clearColor.r, clearColor.b, clearColor.g, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(drawHnadle);
}