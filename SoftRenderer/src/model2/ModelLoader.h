#pragma once
#include <iostream>
#include <tinyobjloader/tinyobjloader.h>

class ModelLoader
{
public:
	static void Parse(const char* path);
};