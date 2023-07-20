#pragma once
#include "Primative.h"

class Model2
{
public:
	Model2(const char* path);
	void PushPrimative(const Primative& p);
	const std::vector<Primative>& GetAllPrimatives() const { return primatives; }
private:
	std::vector<Primative> primatives;
};