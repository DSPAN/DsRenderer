#ifndef MESH_H
#define MESH_H
#include "util.h"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 color;
};

class Mesh
{
public:
    Mesh() {

    }

private:

};

#endif
