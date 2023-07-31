#include "MosaicShader.h"

MosaicShader::MosaicShader(uint32_t size) :pixelSize(size) {}

void MosaicShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	
}

bool MosaicShader::Fragment(glm::vec4& gl_FragColor)
{
	int imageWidth = prePassColorAttachment.get_width();
	int imageHeight = prePassColorAttachment.get_height();
	float u = currentPixel.x / (float)imageWidth;
	float v = currentPixel.y / (float)imageHeight;
	float newU = glm::floor(u * pixelSize) / pixelSize;
	float newV = glm::floor(v * pixelSize) / pixelSize;
	TGAColor samplerColor = prePassColorAttachment.get(newU * imageWidth, newV * imageHeight);
	gl_FragColor = { samplerColor.r / 255.0f, samplerColor.g / 255.0f, samplerColor.b / 255.0f, 1.0f };
	return false;
}

void MosaicShader::SetCurentPixel(const glm::vec2& p)
{
	currentPixel = p;
}