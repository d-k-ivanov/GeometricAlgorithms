#pragma once

#include "ShaderProgram.h"

namespace AlgGeom
{
class RenderingShader : public ShaderProgram
{
public:
    RenderingShader();
    ~RenderingShader() override;
    void   applyActiveSubroutines() override;
    GLuint createShaderProgram(const char* filename) override;
};
}    // namespace AlgGeom
