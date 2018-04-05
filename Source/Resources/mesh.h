#ifndef MESH_H
#define MESH_H
#include "util.h"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 color;
};

struct SubMesh{
    uint32_t indexOffset;
    uint32_t indexCount;
};

class Mesh
{
public:
    Mesh() {
    }

private:
    std::vector<SubMesh> mSubMeshs;

};

#endif
