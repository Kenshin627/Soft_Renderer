#pragma once
#include <tgaimage/tgaimage.h>

struct FrameBuffer
{
	FrameBuffer() = default;
	FrameBuffer(uint32_t width, uint32_t height);
	~FrameBuffer();
	void Reset();
	TGAImage colorAttachment;
	TGAImage depthAttachment;
	float* zBuffer = nullptr;
	uint32_t width;
	uint32_t height;
};