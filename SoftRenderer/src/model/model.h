#pragma once
#include "../texture/Texture.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model {
    std::vector<glm::vec3> verts{};     // array of vertices
    std::vector<glm::vec2> tex_coord{}; // per-vertex array of tex coords
    std::vector<glm::vec3> norms{};     // per-vertex array of normal vectors
    std::vector<int> facet_vrt{};
    std::vector<int> facet_tex{};  // per-triangle indices in the above arrays
    std::vector<int> facet_nrm{};
    Texture diffusemap;         // diffuse color texture
    Texture normalmap;          // normal map texture
    Texture specularmap;        // specular map texture
    void load_texture(const std::string filename, const std::string suffix, Texture& texture);
public:
    Model(const std::string filename);
    int nverts() const;
    int nfaces() const;
    glm::vec3 normal(const int iface, const int nthvert) const; // per triangle corner normal vertex
    //vec3 normal(const vec2& uv);                     // fetch the normal vector from the normal map texture
    glm::vec3 vert(const int i) const;
    glm::vec3 vert(const int iface, const int nthvert) const;
    glm::vec2 uv(const int iface, const int nthvert) const;
    const Texture& diffuse()  const { return diffusemap; }
    const Texture& specular() const { return specularmap; }
    const Texture& normalMap() const { return normalmap; }
    glm::mat4 modelMatrix = glm::identity<glm::mat4>();
};
