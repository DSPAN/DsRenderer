#include "importer.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "tiny_gltf.h"
#include "../ResourceManagers/meshmanager.h"
#include <memory>

void Importer::loadMeshRes(std::string filename) {
    tinygltf::Model gltfModel;
    tinygltf::TinyGLTF gltfContext;
    std::string error;

    bool fileLoaded = gltfContext.LoadASCIIFromFile(&gltfModel, &error, filename.c_str());

    if(!fileLoaded) {
        std::cout<<error<<std::endl;
        return ;
    }

    for (size_t i = 0; i < gltfModel.nodes.size(); i++) {
        std::shared_ptr<Mesh> meshPtr = std::shared_ptr<Mesh>(new Mesh());
        const tinygltf::Node node = gltfModel.nodes[i];

        if (node.mesh > -1) {
            const tinygltf::Mesh mesh = gltfModel.meshes[node.mesh];
            meshPtr->mName = mesh.name;
            for (size_t j = 0; j < mesh.primitives.size(); j++) {
                const tinygltf::Primitive &primitive = mesh.primitives[j];
                if (primitive.indices < 0) {
                    continue;
                }

                uint32_t indexStart = static_cast<uint32_t>(meshPtr->indexData.size());;
                uint32_t indexCount = 0;
                // Vertices
                const float *bufferPos = nullptr;
                const float *bufferNormals = nullptr;
                const float *bufferTexCoords = nullptr;

                assert(primitive.attributes.find("POSITION") != primitive.attributes.end());

                const tinygltf::Accessor &posAccessor = gltfModel.accessors[primitive.attributes.find("POSITION")->second];
                const tinygltf::BufferView &posView = gltfModel.bufferViews[posAccessor.bufferView];
                bufferPos = reinterpret_cast<const float *>(&(gltfModel.buffers[posView.buffer].data[posAccessor.byteOffset + posView.byteOffset]));

                if (primitive.attributes.find("NORMAL") != primitive.attributes.end()) {
                    const tinygltf::Accessor &normAccessor = gltfModel.accessors[primitive.attributes.find("NORMAL")->second];
                    const tinygltf::BufferView &normView = gltfModel.bufferViews[normAccessor.bufferView];
                    bufferNormals = reinterpret_cast<const float *>(&(gltfModel.buffers[normView.buffer].data[normAccessor.byteOffset + normView.byteOffset]));
                }

                if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) {
                    const tinygltf::Accessor &uvAccessor = gltfModel.accessors[primitive.attributes.find("TEXCOORD_0")->second];
                    const tinygltf::BufferView &uvView = gltfModel.bufferViews[uvAccessor.bufferView];
                    bufferTexCoords = reinterpret_cast<const float *>(&(gltfModel.buffers[uvView.buffer].data[uvAccessor.byteOffset + uvView.byteOffset]));
                }

                for (size_t v = 0; v < posAccessor.count; v++) {
                    Vertex vert{};
                    vert.pos = glm::vec4(glm::make_vec3(&bufferPos[v * 3]), 1.0f);
                    vert.normal = bufferNormals ? glm::make_vec3(&bufferNormals[v * 3]) : glm::vec3(0.0f);
                    vert.uv = bufferTexCoords ? glm::make_vec2(&bufferTexCoords[v * 2]) : glm::vec3(0.0f);
                    // Vulkan coordinate system
                    //vert.pos.y *= -1.0f;
                    //vert.normal.y *= -1.0f;
                    meshPtr->vertexData.push_back(vert);
                }
                // Indices
                const tinygltf::Accessor &accessor = gltfModel.accessors[primitive.indices];
                const tinygltf::BufferView &bufferView = gltfModel.bufferViews[accessor.bufferView];
                const tinygltf::Buffer &buffer = gltfModel.buffers[bufferView.buffer];

                indexCount = static_cast<uint32_t>(accessor.count);

                switch (accessor.componentType) {
                    case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: {
                        uint32_t *buf = new uint32_t[accessor.count];
                        memcpy(buf, &buffer.data[accessor.byteOffset + bufferView.byteOffset], accessor.count * sizeof(uint32_t));
                        for (size_t index = 0; index < accessor.count; index++) {
                            meshPtr->indexData.push_back(buf[index]);
                        }
                        break;
                    }
                    case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
                        uint16_t *buf = new uint16_t[accessor.count];
                        memcpy(buf, &buffer.data[accessor.byteOffset + bufferView.byteOffset], accessor.count * sizeof(uint16_t));
                        for (size_t index = 0; index < accessor.count; index++) {
                            meshPtr->indexData.push_back(buf[index]);
                        }
                        break;

                    }
                    case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: {
                        std::cout<<accessor.count<<std::endl;
                        uint8_t *buf = new uint8_t[accessor.count];
                        memcpy(buf, &buffer.data[accessor.byteOffset + bufferView.byteOffset], accessor.count * sizeof(uint8_t));
                        for (size_t index = 0; index < accessor.count; index++) {
                            meshPtr->indexData.push_back(buf[index]);
                        }
                        break;
                    }
                    default:
                        std::cerr << "Index component type " << accessor.componentType << " not supported!" << std::endl;
                        return;
                }

                meshPtr->mSubMesh.push_back({ indexStart, indexCount});
            }//primitives

            meshPtr->mHande = MeshManager::instance().getNextHandle();
            MeshManager::instance().addMesh(meshPtr);
        }//if(mesh)
    }
}
