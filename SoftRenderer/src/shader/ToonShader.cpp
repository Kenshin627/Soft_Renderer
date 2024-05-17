#include "ToonShader.h"

void ToonShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, unsigned gl_VertexIndex)
{
	//�𶥵������գ������ռ�������fragment���������ֵ
	glm::vec3 lightDir = glm::normalize(-light->Direction());
	vertexIntensity[gl_VertexIndex] = glm::max<float>(0.0, glm::dot(glm::normalize(itModel * vertex.normal), lightDir));
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0f);
}

//return discard
bool ToonShader::Fragment(glm::vec4& gl_FragColor)
{
	//���������ֵ���㵱ǰ���ص����ǿ��
	float pixelIntensity = glm::max<float>(0.0, glm::dot(vertexIntensity, baryCentric));
	if (pixelIntensity >= 0.9)
	{
		pixelIntensity = 1.0;
	}
	else if (pixelIntensity >= 0.6)
	{
		pixelIntensity = 0.8;
	}
	else if (pixelIntensity >= 0.4)
	{
		pixelIntensity = 0.6;
	}
	else if (pixelIntensity >= 0.2)
	{
		pixelIntensity = 0.4;
	}
	else
	{
		pixelIntensity = 0.1;
	}
	gl_FragColor = { baseColor.r * pixelIntensity, baseColor.g * pixelIntensity, baseColor.b * pixelIntensity, 255 };
	return false;
}