#include "DirectionLight.h"

DirectionLight::DirectionLight(const glm::vec3& dir, const glm::vec3& color) :direction(glm::normalize(dir)), color(color) {}