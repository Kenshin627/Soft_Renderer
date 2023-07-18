#include "Renderer.h"
#include "Triangle.h"
#include "../shader/BlinnPhongShader.h"
#include "../window/Window.h"

Renderer::Renderer() { }

void Renderer::InitShaders()
{
	shaderLibs.insert({ ShaderType::BlinnPhong, std::make_shared<BlinnPhongShader>() });
}

void Renderer::BindShader(ShaderType type)
{
	auto res = shaderLibs.find(type);
	if (res != shaderLibs.cend())
	{
		activeShader = res->second;
	}
}

void Renderer::BeginScene(const std::shared_ptr<Scene>& scene)
{
	activeScene = scene;
}

void Renderer::EndScene()
{
	activeScene.reset();
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	viewport.width  = width;
	viewport.height = height;
	viewport.transform = {
		{ width / 2, 0, 0, 0 },
		{ 0, height / 2, 0, 0 },
		{ 0, 0, 1, 0 },
		{ width / 2 + x, height / 2 + y, 0, 1 }
	};
	frameBuffer = std::make_unique<FrameBuffer>(width, height);
}

void Renderer::Draw(Window* winHandle)
{
	BindShader(ShaderType::BlinnPhong);
	activeShader->light = activeScene->GetLight();
	activeShader->model = glm::identity<glm::mat4>();
	activeShader->itModel = glm::mat3(glm::transpose(glm::inverse(activeShader->model)));
	activeShader->viewProjection = activeScene->GetCamera()->ViewProjection();
	activeShader->camPos = activeScene->GetCamera()->Position();
	glm::vec4 clipCoords[3];
	glm::vec3 localPosition[3];
	glm::vec2 uvs[3];
	if (activeScene != nullptr)
	{
		const std::vector<Model>& models = activeScene->GetModels();
		uint32_t modelCount = models.size();
		for (uint32_t i = 0; i < modelCount; i++)
		{
			const Model& model = models[i];
			activeShader->SetSampler(0, model.diffuse());
			activeShader->SetSampler(1, model.specular());
			activeShader->SetSampler(2, model.normalMap());
			uint32_t faces = model.nfaces();
			for (uint32_t j = 0; j < faces; j++)
			{
				for (uint32_t k = 0; k < 3; k++) 
				{
					glm::vec3 position = model.vert(j, k);
					glm::vec3 normal = glm::normalize(model.normal(j, k));
					glm::vec2 uv = model.uv(j, k);
					glm::vec4 gl_Position;
					localPosition[k] = position;
					uvs[k] = uv;
					activeShader->Vertex(clipCoords[k], {position, normal, uv}, k);
				}
				ComputeTBN(localPosition, uvs);
				Rasterize(clipCoords, winHandle);
			}
		}
	}
}

void Renderer::Clear()
{
	frameBuffer->Reset();
}

void Renderer::Rasterize(glm::vec4* vertices, Window* windHandle)
{
	glm::vec4 beforeClippedCoords[3] = { viewport.transform * vertices[0], viewport.transform * vertices[1], viewport.transform * vertices[2] };
	glm::vec4 afterClippedCoords[3] = { beforeClippedCoords[0] / beforeClippedCoords[0].w, beforeClippedCoords[1] / beforeClippedCoords[1].w,beforeClippedCoords[2] / beforeClippedCoords[2].w };
	BoundingBox bbox = GetBoundingBox(afterClippedCoords);
	for (uint32_t y = bbox.min.y; y <= bbox.max.y; y++)
	{
		for (uint32_t x = bbox.min.x; x <= bbox.max.x; x++)
		{
			glm::vec2 p = { x + 0.5, y + 0.5 };
			glm::vec3 clipped_bc = BaryCentric(afterClippedCoords, p);
			if (clipped_bc.x < 0 || clipped_bc.y < 0 || clipped_bc.z < 0)
			{
				continue;
			}
			// 1/z = u/z0 + v/z1 + w/z2;
			float depth = 1.0 / (clipped_bc.x / beforeClippedCoords[0].z + clipped_bc.y / beforeClippedCoords[1].z + clipped_bc.z / beforeClippedCoords[2].z);
			
			uint32_t pixelIndex = x + y * viewport.height;
			if (depth < frameBuffer->zBuffer[pixelIndex])
			{
				activeShader->baryCentric = { depth * clipped_bc.x / beforeClippedCoords[0].z, depth * clipped_bc.y / beforeClippedCoords[1].z, depth * clipped_bc.z / beforeClippedCoords[2].z };				
				glm::vec4 gl_FragColor;
				if (!activeShader->Fragment(gl_FragColor))
				{					
					windHandle->DrawPoint(p.x, p.y, glm::vec3(gl_FragColor) * 255.0f);
					frameBuffer->zBuffer[pixelIndex] = depth;
				}
			}
		}
	}
}

BoundingBox Renderer::GetBoundingBox(const glm::vec4* vertices)
{
	BoundingBox bbox;
	glm::vec2 min { 0, 0 };
	glm::vec2 max { viewport.width - 1, viewport.height - 1 };
	bbox.min = max;
	bbox.max = min;
	for (uint32_t i = 0; i < 3; i++)
	{
		bbox.min.x = glm::max(min.x, glm::min(bbox.min.x, vertices[i].x));
		bbox.min.y = glm::max(min.y, glm::min(bbox.min.y, vertices[i].y));
		bbox.max.x = glm::min(max.x, glm::max(bbox.max.x, vertices[i].x));
		bbox.max.y = glm::min(max.y, glm::max(bbox.max.y, vertices[i].y));
	}
	return bbox;
}

glm::vec3 Renderer::BaryCentric(const glm::vec4* vertices, const glm::vec2& p)
{
	glm::vec2 v0 = { vertices[0].x, vertices[0].y };
	glm::vec2 v1 = { vertices[1].x, vertices[1].y };
	glm::vec2 v2 = { vertices[2].x, vertices[2].y };
	
	/*
	 * u + v + w = 1;
	 * p = v0 + (v1-v0) * v + (v2-v0) * w ->
	 * (v1-v0) * v + (v2- v0) * w + (v0 -p) * 1 = 0
	 */
	glm::vec2 v01 = v1 - v0;
	glm::vec2 v02 = v2 - v0;
	glm::vec2 vp0 = v0 - p;
	glm::vec3 uvw = glm::cross(glm::vec3(v01.x, v02.x, vp0.x), glm::vec3(v01.y, v02.y, vp0.y));
	if (uvw.z < 1e-2)
	{
		return { -1, 1, 1 };
	}
	return { 1.0f - (uvw.x + uvw.y) / uvw.z, uvw.x / uvw.z, uvw.y / uvw.z };
}

void Renderer::ComputeTBN(glm::vec3* positions, glm::vec2* uvs)
{
	glm::vec3 e1 = positions[1] - positions[0];
	glm::vec3 e2 = positions[2] - positions[0];
	glm::vec2 deltaUV1 = uvs[1] - uvs[0];
	glm::vec2 deltaUV2 = uvs[2] - uvs[0];
	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	glm::vec3 tangent;
	tangent.x = f * (deltaUV2.y * e1.x - deltaUV1.y * e2.x);
	tangent.y = f * (deltaUV2.y * e1.y - deltaUV1.y * e2.y);
	tangent.z = f * (deltaUV2.y * e1.z - deltaUV1.y * e2.z);
	tangent = glm::normalize(tangent);

	glm::vec3 bitangent;
	bitangent.x = f * (-deltaUV2.x * e1.x + deltaUV1.x * e2.x);
	bitangent.y = f * (-deltaUV2.x * e1.y + deltaUV1.x * e2.y);
	bitangent.z = f * (-deltaUV2.x * e1.z + deltaUV1.x * e2.z);
	bitangent = glm::normalize(bitangent);
	activeShader->tangent = tangent;
	activeShader->biTangent = bitangent;
}