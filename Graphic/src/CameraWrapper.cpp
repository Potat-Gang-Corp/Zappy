/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** Camera
*/

#include "CameraWrapper.hpp"
#include "raymath.h"

CameraWrapper::CameraWrapper()
{
    _camera = { 0 };
    _camera.position = (Vector3){ -10.0f, 10.0f, 0.0f };
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

void CameraWrapper::setPosition(Vector3 position) {
    _camera.position = position;
}

void CameraWrapper::setTarget(Vector3 target) {
    _camera.target = target;
}

void CameraWrapper::setUp(Vector3 up) {
    _camera.up = up;
}

void CameraWrapper::setFOV(float fov) {
    _camera.fovy = fov;
}

void CameraWrapper::update() {
    UpdateCamera(&_camera, CAMERA_PERSPECTIVE);
}

#include <iostream>

void CameraWrapper::handleInput(float deltaTime)
{
    float moveSpeed = 10.0f * deltaTime;
    float angleSpeed = 45.0f * deltaTime;
    float verticalSpeed = 5.0f * deltaTime;

    Vector3 direction = Vector3Normalize(Vector3Subtract(_camera.target, _camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(direction, _camera.up));

    if (IsKeyDown(KEY_W)) {
        _camera.position = Vector3Add(_camera.position, Vector3Scale(direction, moveSpeed));
        _camera.target = Vector3Add(_camera.target, Vector3Scale(direction, moveSpeed));
    }
    if (IsKeyDown(KEY_S)) {
        _camera.position = Vector3Subtract(_camera.position, Vector3Scale(direction, moveSpeed));
        _camera.target = Vector3Subtract(_camera.target, Vector3Scale(direction, moveSpeed));
    }
    if (IsKeyDown(KEY_A)) {
        _camera.position = Vector3Subtract(_camera.position, Vector3Scale(right, moveSpeed));
        _camera.target = Vector3Subtract(_camera.target, Vector3Scale(right, moveSpeed));
    }
    if (IsKeyDown(KEY_D)) {
        _camera.position = Vector3Add(_camera.position, Vector3Scale(right, moveSpeed));
        _camera.target = Vector3Add(_camera.target, Vector3Scale(right, moveSpeed));
    }
    if (IsKeyDown(KEY_SPACE)) {
        _camera.position.y += verticalSpeed;
        _camera.target.y += verticalSpeed;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        _camera.position.y -= verticalSpeed;
        _camera.target.y -= verticalSpeed;
    }

    if (IsKeyDown(KEY_UP)) {
        _camera.target.y += verticalSpeed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        _camera.target.y -= verticalSpeed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        float angle = angleSpeed * DEG2RAD;
        float s = sin(angle);
        float c = cos(angle);
        Vector3 newDirection = {direction.x * c - direction.z * s, direction.y, direction.x * s + direction.z * c};
        _camera.target = Vector3Add(_camera.position, newDirection);
    }
    if (IsKeyDown(KEY_LEFT)) {
        float angle = -angleSpeed * DEG2RAD;
        float s = sin(angle);
        float c = cos(angle);
        Vector3 newDirection = {direction.x * c - direction.z * s, direction.y, direction.x * s + direction.z * c};
        _camera.target = Vector3Add(_camera.position, newDirection);
    }
}
