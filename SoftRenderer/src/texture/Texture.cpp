#include "Texture.h"

Texture::Texture(const char* path)
{
	data = stbi_load(path, &width, &height, &bytePerPixel, STBI_rgb);
}

Texture::~Texture()
{
	stbi_image_free(data);
}

 glm::vec4 Texture::Get(uint32_t x, uint32_t y) const 
{
	if (data == nullptr)
	{
		return glm::vec4(0.0f);
	}
	unsigned char* pixelOffset = data + (x + y * width) * bytePerPixel;
	unsigned char r = pixelOffset[0];
	unsigned char g = pixelOffset[1];
	unsigned char b = pixelOffset[2];
	unsigned char a = bytePerPixel == 4 ? pixelOffset[3] : 0xff;
}