#include "Shader.h"

void Shader::SetSampler(uint32_t slot, const TGAImage& texture)
{
	switch (slot)
	{
	case 0:
		diffuseTexture = texture; break;
	case 1:
		specularTexture = texture; break;
	default:
		break;
	}
}

glm::vec3 Shader::Sampler2D(const glm::vec2& uv, const TGAImage& texture)
{
	TGAColor color = texture.get(uv.x * (texture.get_width() - 1.0f), uv.y * (texture.get_height() - 1.0f));
	return glm::vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}