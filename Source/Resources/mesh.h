#ifndef MESH_H
#define MESH_H

#include "glm.hpp"
#include <vector>
#include <memory>

typedef unsigned long long int MeshHandle;

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct SubMesh{
    uint32_t indexOffset;
    uint32_t indexCount;
};

//need set vk_vexture_buffer, vk_index_buffer
class Mesh
{
public:
    Mesh() {}

    std::string mName;
    MeshHandle mHande;
    std::vector<SubMesh> mSubMesh;
    std::vector<uint32_t> indexData;
    std::vector<Vertex> vertexData;
};

typedef std::shared_ptr<Mesh> MeshPtr;

#endif // MESH_H


#endif
