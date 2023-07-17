#include "BlinnPhongShader.h"

void BlinnPhongShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	triangle.vertices[vertexIndex] = { model * glm::vec4(vertex.position, 1.0), glm::normalize(itModel * vertex.normal), vertex.uv };
	gl_Position = viewProjection * model * glm::vec4(vertex.position.x, vertex.position.y, vertex.position.z, 1.0);
}

bool BlinnPhongShader::Fragment(glm::vec4& gl_FragColor)
{
	glm::vec3 worldPos = baryCentric.x * triangle.vertices[0].position + baryCentric.y * triangle.vertices[1].position + baryCentric.z * triangle.vertices[2].position;
	
	glm::vec3 worldNormal = glm::normalize(baryCentric.x * triangle.vertices[0].normal + baryCentric.y * triangle.vertices[1].normal + baryCentric.z * triangle.vertices[2].normal);

	glm::vec2 uv = baryCentric.x * triangle.vertices[0].uv + baryCentric.y * triangle.vertices[1].uv + baryCentric.z * triangle.vertices[2].uv;

	//光照方向取反，从像素出发
	glm::vec3 lightDir = glm::normalize(-light->Direction());
	glm::vec3 lightColor = light->Color();
	float intensity = glm::max(0.0f, glm::dot(lightDir, worldNormal));
	gl_FragColor = { intensity * lightColor.x, intensity * lightColor.y, intensity * lightColor.z, 255 };
	return false;
}