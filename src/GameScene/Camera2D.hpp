#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <Math/glmath.hpp>
#include <Engine.hpp>

class Camera2D
{
public:
    Math::vec2 position;

private:
    Math::mat4x4 viewMatrix;
    Math::mat4x4 projectionMatrix;
    bool matrixUpdated;
    float cameraMoveSpeed = 5.0f;

public:
    Camera2D() : position(0.0f, 0.0f), matrixUpdated(false) {}

    void SetPosition(const Math::vec2 &newPosition)
    {
        position = newPosition;
        matrixUpdated = false;
    }
    Math::vec2 GetPosition()
    {
        return position;
    }

    void SetUpdate()
    {
        matrixUpdated = false;
    }

    void Move(const Math::vec2 &delta)
    {
        position += delta;
        matrixUpdated = false;
    }

    const Math::mat4x4 &GetViewMatrix()
    {
        if (!matrixUpdated)
        {
            UpdateMatrices();
            matrixUpdated = true;
        }
        return viewMatrix;
    }

    const Math::mat4x4 &GetProjectionMatrix()
    {
        if (!matrixUpdated)
        {
            UpdateMatrices();
            matrixUpdated = true;
        }
        return projectionMatrix;
    }

    Math::vec2 GetScreenToWorld(const Math::vec2 &screenPos, const Math::vec2 &windowSize)
    {
        Math::mat4x4 inverseView = Math::Inverse(viewMatrix);
        Math::mat4x4 inverseProj = Math::Inverse(projectionMatrix);

        // Преобразуем координаты экрана в нормализованные координаты устройства (-1 до 1)
        Math::vec2 normalizedCoords;
        normalizedCoords.x = (2.0f * screenPos.x) / windowSize.x - 1.0f;
        normalizedCoords.y = 1.0f - (2.0f * screenPos.y) / windowSize.y;

        Math::vec4 worldPos = inverseView * inverseProj * Math::vec4(normalizedCoords.x, normalizedCoords.y, 0.0f, 1.0f);
        return Math::vec2(worldPos.x, worldPos.y);
    }

    Math::vec2 GetViewportMin(const Math::vec2 &windowSize)
    {
        return GetScreenToWorld(Math::vec2(0, 0), windowSize);
    }

    Math::vec2 GetViewportMax(const Math::vec2 &windowSize)
    {
        return GetScreenToWorld(windowSize, windowSize);
    }
    
    void CameraFreeMove()
    {

        Math::vec2 moveDelta(0.0f, 0.0f);
        if (Inputs::IsKeyDown(Inputs::KEY_W))
        {
            moveDelta.y -= cameraMoveSpeed;
        }
        else if (Inputs::IsKeyDown(Inputs::KEY_S))
        {
            moveDelta.y += cameraMoveSpeed;
        }
        else if (Inputs::IsKeyDown(Inputs::KEY_D))
        {
            moveDelta.x += cameraMoveSpeed;
        }
        else if (Inputs::IsKeyDown(Inputs::KEY_A))
        {
            moveDelta.x -= cameraMoveSpeed;
        }

        if (moveDelta != Math::vec2(0.0f, 0.0f))
        {
            this->Move(moveDelta);
        }
        this->SetUpdate();
    }

private:
    void UpdateMatrices()
    {
        viewMatrix = Math::Translate(Math::vec3(-position.x, -position.y, 0.0f));
        projectionMatrix = Math::Ortho(0.0f, (float)Window::width, (float)Window::height, 0.0f, -1.0f, 1.0f);
        
    }
};

Camera2D main_camera;

#endif