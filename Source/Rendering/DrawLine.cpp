#include "DrawLine.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

AlgGeom::DrawLine::DrawLine(Line& line)
    : Model3D()
{
    Component* component = new Component;

    Point orig = line.getPoint(-100000);
    Point dest = line.getPoint(100000);

    component->_vertices.insert(
        component->_vertices.end(),
        {VAO::Vertex {glm::vec3(orig.getX(), orig.getY(), .0f)},
         VAO::Vertex {glm::vec3(dest.getX(), dest.getY(), .0f)}});
    // component->_vertices.insert(
    //     component->_vertices.end(),
    //     {VAO::Vertex {glm::vec3(line.getA().getX(), line.getA().getY(), .0f)},
    //      VAO::Vertex {glm::vec3(line.getB().getX(), line.getB().getY(), .0f)}});

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), {0, 1});
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}

AlgGeom::DrawLine::DrawLine(Line3d& line)
    : Model3D()
{
    Component* component = new Component;

    Vect3d orig = line.getPoint(-100000);
    Vect3d dest = line.getPoint(100000);

    component->_vertices.insert(
        component->_vertices.end(),
        {VAO::Vertex {glm::vec3(orig.getX(), orig.getY(), orig.getZ())},
         VAO::Vertex {glm::vec3(dest.getX(), dest.getY(), dest.getZ())}});
    // component->_vertices.insert(
    //     component->_vertices.end(),
    //     {VAO::Vertex {glm::vec3(line.getOrigin().getX(), line.getOrigin().getY(), line.getOrigin().getZ())},
    //      VAO::Vertex {glm::vec3(line.getDestination().getX(), line.getDestination().getY(), line.getDestination().getZ())}});

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), {0, 1});
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}