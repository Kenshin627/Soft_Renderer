#include "RGBSpliterShader.h"

RGBSpliterShader::RGBSpliterShader(const glm::vec2& offset):offset(offset) {}

void RGBSpliterShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex) { }

bool RGBSpliterShader::Fragment(glm::vec4& gl_fragColor)
{
	float offsetX = offset.x;
	float offsetY = offset.y;
	float r = prePassColorAttachment.get(currentPixel.x - offsetX, currentPixel.y - offsetY).r / 255.0f;
	float g = prePassColorAttachment.get(currentPixel.x        , currentPixel.y).g / 255.0f;
	float b = prePassColorAttachment.get(currentPixel.x + offsetX, currentPixel.y + offsetY).b / 255.0f;

	gl_fragColor = glm::vec4(r, g, b, 1.0f);
	return false;
}

void RGBSpliterShader::SetCurentPixel(const glm::vec2& p)
{
	currentPixel = p;
}