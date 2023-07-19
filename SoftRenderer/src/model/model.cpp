#include "model.h"
#include <iostream>
#include <sstream>
#include <fstream>

Model::Model(const std::string filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            glm::vec3 v;
            for (int i = 0; i < 3; i++) iss >> v[i];
            verts.push_back(v);
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            glm::vec3 n;
            for (int i = 0; i < 3; i++) iss >> n[i];
            norms.push_back(glm::normalize(n));
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            glm::vec2 uv;
            for (int i = 0; i < 2; i++) iss >> uv[i];
            tex_coord.push_back({ uv.x, 1 - uv.y });
        }
        else if (!line.compare(0, 2, "f ")) {
            int f, t, n;
            iss >> trash;
            int cnt = 0;
            while (iss >> f >> trash >> t >> trash >> n) {
                facet_vrt.push_back(--f);
                facet_tex.push_back(--t);
                facet_nrm.push_back(--n);
                cnt++;
            }
            if (3 != cnt) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                return;
            }
        }
    }
    std::cerr << "# v# " << nverts() << " f# " << nfaces() << " vt# " << tex_coord.size() << " vn# " << norms.size() << std::endl;
    load_texture(filename, "_diffuse.jpg", diffusemap);
    load_texture(filename, "_nm_tangent.png", normalmap);
    load_texture(filename, "_spec.jpg", specularmap);
}

int Model::nverts() const {
    return verts.size();
}

int Model::nfaces() const {
    return facet_vrt.size() / 3;
}

glm::vec3 Model::vert(const int i) const {
    return verts[i];
}

glm::vec3 Model::vert(const int iface, const int nthvert) const {
    return verts[facet_vrt[iface * 3 + nthvert]];
}

void Model::load_texture(std::string filename, const std::string suffix, Texture& texture) {
    size_t dot = filename.find_last_of(".");
    if (dot == std::string::npos) return;
    std::string texfile = filename.substr(0, dot) + suffix;
    texture = Texture(texfile.c_str());
}

glm::vec2 Model::uv(const int iface, const int nthvert) const {
    return tex_coord[facet_tex[iface * 3 + nthvert]];
}

glm::vec3 Model::normal(const int iface, const int nthvert) const {
    return norms[facet_nrm[iface * 3 + nthvert]];
}