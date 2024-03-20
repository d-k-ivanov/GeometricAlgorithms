#include "InputManager.h"

#include "Renderer.h"

#include <glm/gtc/epsilon.hpp>

#include <vector>

GDSA::Render::ApplicationState GDSA::Render::InputManager::_applicationState;
const glm::vec2                GDSA::Render::InputManager::_defaultCursorPosition = glm::vec2(-1.0f, -1.0f);

GDSA::Render::InputManager::InputManager()
    : _lastCursorPosition(_defaultCursorPosition)
    , _leftClickPressed(false)
    , _rightClickPressed(false)
{
    this->buildMoveRelatedBuffers();
}

void GDSA::Render::InputManager::buildMoveRelatedBuffers()
{
    _movementMultiplier = 0.1f;
    _moveSpeedUp        = 1.0f;

    _moveSpeed                   = std::vector<float>(static_cast<size_t>(Events::NUM_EVENTS), .0f);
    _moveSpeed[Events::BOOM]     = 0.1f;
    _moveSpeed[Events::DOLLY]    = 0.08f;
    _moveSpeed[Events::ORBIT_XZ] = 0.05f;
    _moveSpeed[Events::ORBIT_Y]  = 0.03f;
    _moveSpeed[Events::PAN]      = 0.002f;
    _moveSpeed[Events::TILT]     = 0.002f;
    _moveSpeed[Events::TRUCK]    = 0.01f;
    _moveSpeed[Events::ZOOM]     = 0.008f;

    _eventKey                         = std::vector<glm::ivec2>(static_cast<size_t>(Events::NUM_EVENTS), glm::ivec2(0));
    _eventKey[Events::ALTER_POINT]    = glm::ivec2(GLFW_KEY_0);
    _eventKey[Events::ALTER_LINE]     = glm::ivec2(GLFW_KEY_1);
    _eventKey[Events::ALTER_TRIANGLE] = glm::ivec2(GLFW_KEY_2);

    _eventKey[Events::BOOM]           = glm::ivec2(GLFW_KEY_UP, GLFW_KEY_DOWN);
    _eventKey[Events::DOLLY]          = glm::ivec2(GLFW_KEY_W, GLFW_KEY_S);
    _eventKey[Events::DOLLY_SPEED_UP] = glm::ivec2(GLFW_MOD_SHIFT);
    _eventKey[Events::ORBIT_XZ]       = glm::ivec2(GLFW_KEY_Y);
    _eventKey[Events::ORBIT_Y]        = glm::ivec2(GLFW_KEY_X);
    _eventKey[Events::PAN]            = glm::ivec2(GLFW_KEY_P);
    _eventKey[Events::RESET]          = glm::ivec2(GLFW_KEY_B);
    _eventKey[Events::SCREENSHOT]     = glm::ivec2(GLFW_KEY_K, GLFW_KEY_L);
    _eventKey[Events::TILT]           = glm::ivec2(GLFW_KEY_T);
    _eventKey[Events::TRUCK]          = glm::ivec2(GLFW_KEY_D, GLFW_KEY_A);

    _moves = std::vector<GLuint>(static_cast<size_t>(Events::NUM_EVENTS), 0);
}

bool GDSA::Render::InputManager::checkPanTilt(const float xPos, const float yPos)
{
    Camera* camera = Renderer::getInstance()->getCamera();

    _leftClickPressed &= glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    _rightClickPressed &= glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    if(_leftClickPressed || _rightClickPressed)
    {
        if(_lastCursorPosition.x >= 0.0f)
        {
            if(!glm::epsilonEqual(xPos, _lastCursorPosition.x, glm::epsilon<float>()))
            {
                camera->pan(-_moveSpeed[Events::PAN] * (xPos - _lastCursorPosition.x));
            }

            if(!glm::epsilonEqual(yPos, _lastCursorPosition.y, glm::epsilon<float>()))
            {
                camera->tilt(-_moveSpeed[Events::TILT] * (yPos - _lastCursorPosition.y));
            }
        }

        _lastCursorPosition = glm::vec2(xPos, yPos);
        return true;
    }

    return false;
}

void GDSA::Render::InputManager::processPressedKeyEvent(const int key, const int mods)
{
    Renderer* renderer = Renderer::getInstance();
    Camera*   camera   = renderer->getCamera();

    if(key == _eventKey[Events::ALTER_POINT][0])
    {
        _applicationState._activeRendering[VAO::IBO_POINT] = !_applicationState._activeRendering[VAO::IBO_POINT];
    }
    else if(key == _eventKey[Events::ALTER_LINE][0])
    {
        _applicationState._activeRendering[VAO::IBO_LINE] = !_applicationState._activeRendering[VAO::IBO_LINE];
    }
    else if(key == _eventKey[Events::ALTER_TRIANGLE][0])
    {
        _applicationState._activeRendering[VAO::IBO_TRIANGLE] = !_applicationState._activeRendering[VAO::IBO_TRIANGLE];
    }
    else if(key == _eventKey[Events::RESET][0])
    {
        camera->reset();
    }
    else if(key == _eventKey[Events::ORBIT_XZ][0])
    {
        if(mods == GLFW_MOD_CONTROL)
        {
            camera->orbitXZ(_moveSpeed[Events::ORBIT_XZ]);
        }
        else
        {
            camera->orbitXZ(-_moveSpeed[Events::ORBIT_XZ]);
        }
    }
    else if(key == _eventKey[Events::ORBIT_Y][0])
    {
        if(mods == GLFW_MOD_CONTROL)
        {
            camera->orbitY(-_moveSpeed[Events::ORBIT_Y]);
        }
        else
        {
            camera->orbitY(_moveSpeed[Events::ORBIT_Y]);
        }
    }
    else if(key == _eventKey[Events::DOLLY][0])
    {
        if(_rightClickPressed)
        {
            camera->dolly(_moveSpeed[Events::DOLLY] + _moves[Events::DOLLY] * _moveSpeed[Events::DOLLY] * _movementMultiplier);
            ++_moves[Events::DOLLY];
        }
    }
    else if(key == _eventKey[Events::DOLLY][1])
    {
        if(_rightClickPressed)
        {
            camera->dolly(-(_moveSpeed[Events::DOLLY] + _moves[Events::DOLLY] * _moveSpeed[Events::DOLLY] * _movementMultiplier));
            ++_moves[Events::DOLLY];
        }
    }
    else if(key == _eventKey[Events::TRUCK][0])
    {
        if(_rightClickPressed)
        {
            camera->truck(_moveSpeed[Events::TRUCK] + _moves[Events::TRUCK] * _moveSpeed[Events::TRUCK] * _movementMultiplier);
            ++_moves[Events::TRUCK];
        }
    }
    else if(key == _eventKey[Events::TRUCK][1])
    {
        if(_rightClickPressed)
        {
            camera->truck(-(_moveSpeed[Events::TRUCK] + _moves[Events::TRUCK] * _moveSpeed[Events::TRUCK] * _movementMultiplier));
            ++_moves[Events::TRUCK];
        }
    }
    else if(key == _eventKey[Events::BOOM][0])
    {
        camera->boom(_moveSpeed[Events::BOOM]);
    }
    else if(key == _eventKey[Events::BOOM][1])
    {
        camera->crane(_moveSpeed[Events::BOOM]);
    }
    else if(key == _eventKey[Events::SCREENSHOT][0])
    {
        this->pushScreenshotEvent(ScreenshotListener::ScreenshotEvent {ScreenshotListener::RGBA});
    }
}

void GDSA::Render::InputManager::processReleasedKeyEvent(const int key, const int mods)
{
    if(key == _eventKey[Events::DOLLY][0] || key == _eventKey[Events::DOLLY][1])
    {
        _moves[Events::DOLLY] = 0;
    }

    if(key == _eventKey[Events::TRUCK][0] || key == _eventKey[Events::TRUCK][0])
    {
        _moves[Events::TRUCK] = 0;
    }
}

GDSA::Render::InputManager::~InputManager()
{
}

void GDSA::Render::InputManager::init(GLFWwindow* window)
{
    _window = window;

    // We register the callbacks that will respond to the main events
    glfwSetWindowRefreshCallback(window, windowRefreshCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCursorCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void GDSA::Render::InputManager::pushScreenshotEvent(const ScreenshotListener::ScreenshotEvent& event)
{
    _screenshotEvents.push_back(event);
}

void GDSA::Render::InputManager::suscribeResize(ResizeListener* listener)
{
    _resizeListeners.push_back(listener);
}

void GDSA::Render::InputManager::suscribeScreenshot(ScreenshotListener* listener)
{
    _screenshotListeners.push_back(listener);
}

// This callback function will be called every time the OpenGL drawing area is resized.
void GDSA::Render::InputManager::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    InputManager* inputManager = InputManager::getInstance();
    for(ResizeListener* listener : inputManager->_resizeListeners)
    {
        listener->resizeEvent(static_cast<uint16_t>(width), static_cast<uint16_t>(height));
    }
}

// This callback function will be called every time a key directed to the OpenGL drawing area is pressed.
void GDSA::Render::InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager* inputManager = InputManager::getInstance();

    if(action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        inputManager->processPressedKeyEvent(key, mods);
    }
    else
    {
        inputManager->processReleasedKeyEvent(key, mods);
    }
}

// This callback function will be called every time a mouse button is pressed on the OpenGL drawing area.
void GDSA::Render::InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(GUI::getInstance()->isMouseActive())
        return;

    InputManager* inputManager = InputManager::getInstance();

    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        inputManager->_leftClickPressed   = action == GLFW_PRESS;
        inputManager->_lastCursorPosition = _defaultCursorPosition;
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        inputManager->_rightClickPressed  = action == GLFW_PRESS;
        inputManager->_lastCursorPosition = _defaultCursorPosition;
    }
}

void GDSA::Render::InputManager::mouseCursorCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputManager* inputManager = InputManager::getInstance();
    inputManager->checkPanTilt(static_cast<float>(xpos), static_cast<float>(ypos));
}

// This callback function will be called every time the mouse wheel is moved over the OpenGL drawing area.
void GDSA::Render::InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    InputManager* inputManager = InputManager::getInstance();
    Camera*       camera       = Renderer::getInstance()->getCamera();

    camera->zoom(static_cast<float>(yoffset) * inputManager->_moveSpeed[ZOOM]);
}

// This callback function will be called every time the OpenGL drawing area needs to be redrawn.
void GDSA::Render::InputManager::windowRefreshCallback(GLFWwindow* window)
{
    InputManager* inputManager = InputManager::getInstance();
    while(!inputManager->_screenshotEvents.empty())
    {
        for(ScreenshotListener* listener : inputManager->_screenshotListeners)
        {
            listener->screenshotEvent(inputManager->_screenshotEvents[0]);
        }

        inputManager->_screenshotEvents.erase(inputManager->_screenshotEvents.begin());
    }

    Renderer::getInstance()->render();
}
