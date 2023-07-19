#include "Shader.h"

void Shader::SetSampler(uint32_t slot, const Texture& texture)
{
	switch (slot)
	{
	case 0:
		diffuseTexture = texture; break;
	case 1:
		specularTexture = texture; break;
	case 2:
		tbnNormalTexture = texture; break;
	default:
		break;
	}
}

glm::vec3 Shader::Sampler2D(const glm::vec2& uv, const Texture& texture)
{
	glm::vec4 color = texture.Get(uv.x * (texture.GetWidth() - 1.0f), uv.y * (texture.GetHeight() - 1.0f));
	return glm::vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}