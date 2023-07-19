#include "BlinnPhongWithShadowShader.h"

void BlinnPhongWithShadowShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	triangle.vertices[vertexIndex] = { model * glm::vec4(vertex.position, 1.0), glm::normalize(itModel * vertex.normal), vertex.uv };
	gl_Position = viewProjection * model * glm::vec4(vertex.position.x, vertex.position.y, vertex.position.z, 1.0);
}

bool BlinnPhongWithShadowShader::Fragment(glm::vec4& gl_FragColor)
{
	glm::vec2 uv = baryCentric.x * triangle.vertices[0].uv + baryCentric.y * triangle.vertices[1].uv + baryCentric.z * triangle.vertices[2].uv;
	glm::vec3 worldPos = baryCentric.x * triangle.vertices[0].position + baryCentric.y * triangle.vertices[1].position + baryCentric.z * triangle.vertices[2].position;
	glm::vec3 worldNormal = glm::normalize(baryCentric.x * triangle.vertices[0].normal + baryCentric.y * triangle.vertices[1].normal + baryCentric.z * triangle.vertices[2].normal);

	//计算阴影
	glm::vec4 lightSpacePos = viewport * light->GetLightSpace().ViewProjection() * glm::vec4(worldNormal, 1.0);
	float x = lightSpacePos[0] / lightSpacePos[3];
	float y = lightSpacePos[1] / lightSpacePos[3];
	float z = lightSpacePos[2] / lightSpacePos[3];
	float shadow = 1.0f;
	//在阴影中
	if (shadowBuffer->zBuffer[(int)x + (int)y * shadowBuffer->width] < z)
	{
		shadow = 0.3f;
	}

	//构造TBN
	glm::vec3 N = worldNormal;
	glm::vec3 T = glm::normalize(glm::cross(biTangent, N));
	glm::vec3 B = glm::normalize(glm::cross(N, tangent));
	glm::mat3 TBN = {
		T, B, N
	};
	glm::vec3 samplerN = glm::normalize(Sampler2D(uv, tbnNormalTexture)) * 2.0f - 1.0f;
	glm::vec3 normal = glm::normalize(TBN * samplerN);

	//光照方向取反，从像素出发
	glm::vec3 lightDir = glm::normalize(-light->Direction());
	glm::vec3 lightColor = light->Color();

	//diffuse
	glm::vec3 diffuseColor = Sampler2D(uv, diffuseTexture); //[0-1]
	float diffuse = glm::max(0.0f, glm::dot(lightDir, normal));
	diffuseColor = diffuse * diffuseColor;

	//specular
	glm::vec3 viewDir = glm::normalize(camPos - worldPos);
	glm::vec3 h = glm::normalize((viewDir + lightDir));
	float specular = glm::pow(glm::max(0.0f, glm::dot(h, normal)), 128);
	float samplerSpecular = Sampler2D(uv, specularTexture).b;//[0-1]
	glm::vec3 specularColor = glm::vec3(samplerSpecular);
	specularColor = specularColor * specular;

	//ambient
	glm::vec3 ambientColor = glm::vec3(0.01);

	glm::vec3 color = ((diffuseColor + specularColor) * shadow + ambientColor) * lightColor;
	color.r = glm::min(1.0f, color.r);
	color.g = glm::min(1.0f, color.g);
	color.b = glm::min(1.0f, color.b);
	gl_FragColor = { color, 1.0f };
	return false;
}