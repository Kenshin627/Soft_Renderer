#include "GouraudShader.h"

void GouraudShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	//逐顶点计算光照，将光照计算结果在fragment重心坐标插值
	glm::vec3 lightDir = -light->Direction();
	vertexIntensity[vertexIndex] = glm::max<float>(0.0, glm::dot(glm::normalize(itModel * vertex.normal), lightDir));
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0f);
}

//return discard
bool GouraudShader::Fragment(glm::vec4& gl_FragColor)
{
	//重心坐标插值计算当前像素点光照强度
	float pixelIntensity = glm::max<float>(0.0, glm::dot(vertexIntensity, baryCentric));
	gl_FragColor = { baseColor.r * pixelIntensity, baseColor.g * pixelIntensity, baseColor.b * pixelIntensity, 255 };
	return false;
}