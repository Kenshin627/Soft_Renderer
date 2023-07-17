#include "Shader.h"

void Shader::SetSampler(uint32_t slot, const TGAImage& texture)
{
	switch (slot)
	{
	case 0:
		diffuse = texture; break;
	case 1:
		specular = texture; break;
	default:
		break;
	}
}