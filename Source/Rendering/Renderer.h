#pragma once

#include "ApplicationState.h"
#include "Camera.h"
#include "FBOScreenshot.h"
#include "GUI.h"
#include "InputManager.h"
#include "Model3D.h"
#include "RenderingShader.h"
#include "SceneContent.h"

namespace GDSA::Render
{
class Renderer : public Singleton<Renderer>, public ResizeListener, public ScreenshotListener
{
    friend class Singleton<Renderer>;

private:
    ApplicationState* _appState;
    SceneContent*     _content;
    GUI*              _gui;
    FBOScreenshot*    _screenshoter;
    RenderingShader * _triangleShader, *_lineShader, *_pointShader;

private:
    Renderer();

    void renderLine(Model3D::MatrixRenderInformation* matrixInformation);
    void renderPoint(Model3D::MatrixRenderInformation* matrixInformation);
    void renderTriangle(Model3D::MatrixRenderInformation* matrixInformation);
    void transferLightUniforms(RenderingShader* shader);

public:
    virtual ~Renderer();
    void    createCamera(uint16_t width, uint16_t height);
    void    createModels();
    void    createShaderProgram();
    Camera* getCamera() const { return _content->_camera[_appState->_selectedCamera].get(); }
    void    prepareOpenGL(uint16_t width, uint16_t height, ApplicationState* appState);
    void    removeModel();
    void    render(float alpha = 1.0f, bool renderGui = true, bool bindScreenshoter = false);
    void    resizeEvent(uint16_t width, uint16_t height) override;
    void    screenshotEvent(const ScreenshotEvent& event) override;
};
}    // namespace GDSA::Render
