#include "FlatShader.h"

void FlatShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, unsigned gl_VertexIndex)
{
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0f);
}

bool FlatShader::Fragment(glm::vec4& gl_FragColor)
{
	if (flatShadeIntensity <= 0)
	{
		return true;
	}
	gl_FragColor = { baseColor.r * flatShadeIntensity, baseColor.g * flatShadeIntensity, baseColor.b * flatShadeIntensity, 255.0 };
	return false;
}