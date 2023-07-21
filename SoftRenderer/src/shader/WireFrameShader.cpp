#include "WireFrameShader.h"

void WireFrameShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	//逐顶点计算光照，将光照计算结果在fragment重心坐标插值
	glm::vec3 lightDir = -light->Direction();
	vertexIntensity[vertexIndex] = glm::max<float>(0.0, glm::dot(glm::normalize(itModel * vertex.normal), lightDir));
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0f);
}

//return discard
bool WireFrameShader::Fragment(glm::vec4& gl_FragColor)
{
	if (baryCentric.x <= lineWidth || baryCentric.y <= lineWidth || baryCentric.z <= lineWidth)
	{
		gl_FragColor = { baseColor, 255 };
		return false;
	}
	return true;
}