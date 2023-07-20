#pragma once
#include "../scene/Scene.h"
#include "../shader/Shader.h"
#include "FrameBuffer.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>

class Window;
struct Viewport
{
	Viewport() = default;
	uint32_t width = 0;
	uint32_t height = 0;
	glm::mat4 transform = glm::identity<glm::mat4>();
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
	void DrawLine(Window* winHandle);
	void ShadowPass(Window* winHandle);
	void DefaultPass(Window* winHandle);
	void Clear();
	void Rasterize(glm::vec4* vertices, Window* winHandle, std::shared_ptr<FrameBuffer>& currentBuffer, bool present = true);
	BoundingBox GetBoundingBox(const glm::vec4* vertices);
	glm::vec3 BaryCentric(const glm::vec4* vertices, const glm::vec2& p);
	void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	void ComputeTBN(glm::vec3* positions, glm::vec2* uvs);
	void BresenhamLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, const glm::vec3& color, Window* winHandle);
private:
	std::shared_ptr<Scene> activeScene;
	std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaderLibs;
	std::shared_ptr<Shader> activeShader;
	Viewport viewport = Viewport();
	std::shared_ptr<FrameBuffer> defaultPassFrameBuffer;
	std::shared_ptr<FrameBuffer> shadowPassFrameBuffer;
};