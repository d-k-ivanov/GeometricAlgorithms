#pragma once

#include "Model3D.h"

#include <Geometry/TriangleModel.h>

namespace AlgGeom
{
class DrawMesh : public Model3D
{
protected:
    Assimp::Importer _assimpImporter;

protected:
    Model3D::Component* processMesh(const aiMesh* mesh, const aiScene* scene, const std::string& folder) const;
    void                processNode(const aiNode* node, const aiScene* scene, const std::string& folder);

public:
    DrawMesh();
    DrawMesh(TriangleModel& triangleModel);
    DrawMesh(const DrawMesh& drawMesh) = delete;

    ~DrawMesh() override = default;

    DrawMesh* loadModelOBJ(const std::string& path);
};
}    // namespace AlgGeom
