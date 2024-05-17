#include "DepthMap.h"

void DepthShader::Vertex(glm::vec4& gl_Position, const VertexAttribute& vertex, uint32_t vertexIndex)
{
	triangle.vertices[vertexIndex] = { model * glm::vec4(vertex.position, 1.0), glm::normalize(itModel * vertex.normal), vertex.uv };
	gl_Position = viewProjection * model * glm::vec4(vertex.position, 1.0);
}

bool DepthShader::Fragment(glm::vec4& gl_FragColo)
{
	
}