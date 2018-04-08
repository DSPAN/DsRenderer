#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"
#include "../RenderAPI/vkvertexbuffer.h"
#include "../RenderAPI/vkindexbuffer.h"
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

    void setBuffer() {
        mVertexBuffer = std::shared_ptr<vk_vertexBuffer>(new vk_vertexBuffer(sizeof(Vertex),vertexData.size(),vertexData.data()));
        mIndexBuffer = std::shared_ptr<vk_indexBuffer>(new vk_indexBuffer(VK_INDEX_TYPE_UINT32,sizeof(uint32_t),static_cast<uint32_t>(indexData.size()),indexData.data()));
    }

    std::string mName;
    MeshHandle mHande;
    std::vector<SubMesh> mSubMesh;
    std::vector<uint32_t> indexData;
    std::vector<Vertex> vertexData;
    std::shared_ptr<vk_vertexBuffer> mVertexBuffer;
    std::shared_ptr<vk_indexBuffer> mIndexBuffer;
};

typedef std::shared_ptr<Mesh> MeshPtr;

#endif // MESH_H

