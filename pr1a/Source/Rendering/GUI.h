#pragma once

#include "ApplicationState.h"
#include "CameraGuiAdapter.h"
#include "ImGuizmo.h"
#include "SceneContent.h"

#include "Patterns/Singleton.h"

namespace AlgGeom
{
class GUI : public Singleton<GUI>
{
    friend class Singleton<GUI>;

protected:
    enum MenuButtons
    {
        RENDERING,
        MODELS,
        CAMERA,
        LIGHT,
        SCREENSHOT,
        NUM_GUI_MENU_BUTTONS
    };
    enum FileDialog
    {
        OPEN_MESH,
        NONE
    };
    inline static std::string              DEFAULT_DIRECTORY = ".";
    inline static std::vector<std::string> FILE_DIALOG_TEXT {"Choose Model"};
    inline static std::vector<std::string> FILE_DIALOG_EXTENSION {".obj, .gltf, .fbx"};

    ApplicationState*   _appState;
    CameraGuiAdapter*   _cameraGuiAdapter;
    FileDialog          _fileDialog;
    Model3D::Component* _modelCompSelected;
    std::string         _path, _lastDirectory;
    bool*               _showMenuButtons;

    // ImGuizmo
    ImGuizmo::OPERATION _currentGizmoOperation;
    ImGuizmo::MODE      _currentGizmoMode;

protected:
    void editTransform(ImGuizmo::OPERATION& operation, ImGuizmo::MODE& mode);
    void loadFonts();
    void loadImGUIStyle();
    void processSelectedFile(FileDialog fileDialog, const std::string& filename, SceneContent* sceneContent);
    void renderGuizmo(Model3D::Component* component, SceneContent* sceneContent);
    void showCameraMenu(SceneContent* sceneContent);
    void showFileDialog(SceneContent* sceneContent);
    void showLightMenu(SceneContent* sceneContent);
    void showModelMenu(SceneContent* sceneContent);
    void showRenderingMenu(SceneContent* sceneContent);
    void showScreenshotMenu(SceneContent* sceneContent);

protected:
    GUI();

public:
    virtual ~GUI();

    void initialize(GLFWwindow* window, const int openGLMinorVersion);
    void render(SceneContent* sceneContent);

    uint16_t getFrameRate() { return static_cast<uint16_t>(ImGui::GetIO().Framerate); }
    bool     isMouseActive() { return ImGui::GetIO().WantCaptureMouse; }
};
}
