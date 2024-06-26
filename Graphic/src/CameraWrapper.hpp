/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** Camera
*/

#pragma once

#ifndef CAMERA_HPP
    #define CAMERA_HPP

    #include "raylib.h"
    #include <memory>

class CameraWrapper {
    public:
        CameraWrapper();
        static std::shared_ptr<CameraWrapper> &getInstance() {
            static std::shared_ptr<CameraWrapper> instance = std::make_shared<CameraWrapper>();
            return instance;
        }
        void setPosition(Vector3 position);
        void setTarget(Vector3 target);
        void setUp(Vector3 up);
        void setFOV(float fov);
        void update();
        void handleInput(float deltaTime);
        Camera3D getCamera() { return _camera; }
        float getX() { return _camera.position.x; }
        float getY() { return _camera.position.y; }
        float getZ() { return _camera.position.z; }

    private:
        Camera3D _camera;
};

#endif // CAMERA_HPP

