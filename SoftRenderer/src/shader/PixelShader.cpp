#include "PixelShader.h"

void PixelShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	normals[vertexIndex] = glm::normalize(itModel * vertex.normal);
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0f);
}

//return discard
bool PixelShader::Fragment(glm::vec4& gl_FragColor)
{
	//重心坐标插值计算当前像素点法线，逐像素计算光照
	glm::vec3 lightDir = -light->Direction();
	glm::vec3 n = normals[0] * baryCentric.x + normals[1] * baryCentric.y + normals[2] * baryCentric.z;
	n = glm::normalize(n);
	float pixelIntensity = glm::max<float>(0.0, glm::dot(n, lightDir));
	gl_FragColor = { baseColor.r * pixelIntensity, baseColor.g * pixelIntensity, baseColor.b * pixelIntensity, 255 };
	return false;
}