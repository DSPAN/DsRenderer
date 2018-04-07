#ifndef IMPORTER_H
#define IMPORTER_H


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../Utility/module.h"
#include "../Resources/mesh.h"

class Importer :public Module<Importer> {
public:
    Importer() {}

    void loadMeshRes(std::string filename);

};
#endif // IMPORTER_H
