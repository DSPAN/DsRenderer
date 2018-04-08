#ifndef IMPORTER_H
#define IMPORTER_H


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Utility/module.h"
#include "../Resources/mesh.h"

class Importer :public Module<Importer> {
public:
    Importer() {}

    void loadMeshRes(std::string filename);

};
#endif // IMPORTER_H
