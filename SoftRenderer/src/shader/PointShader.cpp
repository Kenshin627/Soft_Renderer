#include "PointShader.h"

void PointShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	//逐顶点计算光照，将光照计算结果在fragment重心坐标插值
	glm::vec3 lightDir = -light->Direction();
	vertexIntensity[vertexIndex] = glm::max<float>(0.0, glm::dot(glm::normalize(itModel * vertex.normal), lightDir));
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0f);
}

//return discard
bool PointShader::Fragment(glm::vec4& gl_FragColor)
{
	if ((baryCentric.x == 1.0f && baryCentric.y == 0.0f && baryCentric.z == 0.0f) || (baryCentric.x == 0.0f && baryCentric.y == 1.0f && baryCentric.z == 0.0f) || (baryCentric.x == 0.0f && baryCentric.y == 0.0f && baryCentric.z == 1.0f))
	{
		gl_FragColor = { baseColor, 1.0f };
		return false;
	}
	return true;
}