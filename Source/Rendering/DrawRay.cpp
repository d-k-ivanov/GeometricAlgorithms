#include "StdAfx.h"

#include "DrawRay.h"

AlgGeom::DrawRay::DrawRay(RayLine& ray): Model3D() , _ray(ray)
{
    Component* component = new Component;

    Point dest = ray.getPoint(INT_MAX);

    component->_vertices.insert(component->_vertices.end(), {VAO::Vertex {vec3(ray.getA().getX(), ray.getA().getY(), .0f)}, VAO::Vertex {vec3(dest.getX(), dest.getY(), .0f)}});

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), {0, 1});
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}