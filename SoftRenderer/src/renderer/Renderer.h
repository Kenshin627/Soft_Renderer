#pragma once
#include "../scene/Scene.h"
#include "../shader/Shader.h"
#include "FrameBuffer.h"
#include <vector>
#include <memory>
#include <unordered_map>

class Window;
struct Viewport
{
	uint32_t width;
	uint32_t height;
	glm::mat4 transform;
};

struct BoundingBox
{
	glm::vec2 min;
	glm::vec2 max;
};

class Renderer
{
public:
	Renderer();
	~Renderer() = default;
	void InitShaders();
	void BindShader(ShaderType type);
	void BeginScene(const std::shared_ptr<Scene>& scene);
	void EndScene();
	void Draw(Window* winHandle);
	void Clear();
	void Rasterize(glm::vec4* vertices, Window* winHandle);
	BoundingBox GetBoundingBox(const glm::vec4* vertices);
	glm::vec3 BaryCentric(const glm::vec4* vertices, const glm::vec2& p);
	void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
private:
	std::shared_ptr<Scene> activeScene;
	std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaderLibs;
	std::shared_ptr<Shader> activeShader;
	Viewport viewport;
	std::unique_ptr<FrameBuffer> frameBuffer;
};