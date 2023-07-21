#pragma once
#include "Primative.h"
#include <memory>
#include <tinyobjloader/tinyobjloader.h>

class Model2
{
public:
	Model2(const std::string& path);
	void ParseMaterial(const std::vector<tinyobj::material_t>& mats, const std::string& path);
	void PushPrimative(const Primative& p);
	const std::vector<Primative>& GetAllPrimatives() const { return primatives; }
private:
	std::vector<Primative> primatives;
	std::vector<std::shared_ptr<Material>> materials;
};