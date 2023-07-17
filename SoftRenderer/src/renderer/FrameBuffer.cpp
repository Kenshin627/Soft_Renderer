#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height):width(width), height(height)
{
	colorAttachment = TGAImage(width, height, TGAImage::RGB);
	depthAttachment = TGAImage(width, height, TGAImage::GRAYSCALE);
	zBuffer = new float[width * height];
	Reset();
}

FrameBuffer::~FrameBuffer()
{
	delete[] zBuffer;
}

void FrameBuffer::Reset()
{
	for (uint32_t i = 0; i < width * height; i++)
	{
		zBuffer[i] = std::numeric_limits<float>::max();
	}
}