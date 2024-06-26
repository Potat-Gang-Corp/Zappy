/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** Tile
*/

#include "Tile.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include "raymath.h"
#include "Utils.hpp"
#include "ModelsLoader.hpp"
#include <algorithm>

Tile::Tile(Vector3 position, Model tileModel, const std::vector<Model>& resourceModels)
    : _position(position), _scale(0.2f), _model(tileModel), _isHovered(false), _isClicked(false), _rotationAngle(0.0f), _resources(8, 0)
{
    _hud = HUD::getInstance();
    if (!_model.meshCount) {
        std::cerr << "Failed to load model: assets/island_farm.glb" << std::endl;
        throw std::runtime_error("Failed to load model");
    }

    _boundingBox = GetMeshBoundingBox(_model.meshes[0]);
    _boundingBox.min = Vector3Scale(_boundingBox.min, _scale);
    _boundingBox.max = Vector3Scale(_boundingBox.max, _scale);
    _boundingBox.min = Vector3Add(_boundingBox.min, position);
    _boundingBox.max = Vector3Add(_boundingBox.max, position);
    for (const auto& resourceModel : resourceModels) {
        auto resource = std::make_shared<Resource>(resourceModel, position);
        _resourceObjects.push_back(resource);
    }
}

Tile::~Tile() {}

void Tile::Render()
{
    if (_isHovered) {
        _rotationAngle += 1.0f;
        if (_rotationAngle > 360.0f) _rotationAngle -= 360.0f;
    }

    for (int i = 0; i < 10; i++) {
        Color glowColor = Fade(BLUE, 1.0f - (i * 0.1f));
        if (_isHovered)
            DrawModelEx(_model, _position, (Vector3){0, 1, 0}, _rotationAngle, (Vector3){_scale, _scale, _scale}, glowColor);
        else {
            _rotationAngle = 0.0f;
            DrawModel(_model, _position, _scale, WHITE);
        }
    }

    float radius = 0.5f;
    int resourceCount = 0;
    size_t resourceSize = _resources.size();
    for (size_t i = 0; i < resourceSize; ++i) {
        if (_resources[i] > 0) {
            float angle = resourceCount * (360.0f / resourceSize) * DEG2RAD + _rotationAngle * DEG2RAD;
            angle *= -1;
            Vector3 resourcePosition = {
                _position.x + radius * cos(angle),
                _position.y,
                _position.z + radius * sin(angle)
            };
            _resourceObjects[i]->setPosition(resourcePosition);
            _resourceObjects[i]->Render();
            resourceCount++;
        }
    }
}

BoundingBox Tile::getBoundingBox() const
{
    return _boundingBox;
}

void Tile::OnClick()
{
    _hud->ClearMessages();
    std::ostringstream streamX, streamZ;
    streamX << std::fixed << std::setprecision(0) << _position.x / 10.0f;
    streamZ << std::fixed << std::setprecision(0) << _position.z / 10.0f;
    std::string message = "Tile at (" + streamX.str() + ", " + streamZ.str() + "): ";
    _hud->AddMessage(message);
    for (size_t i = 0; i < _resources.size(); ++i) {
        message = Utils::getInstance()->indexToString(i);
        message += std::to_string(_resources[i]);
        _hud->AddMessage(message);
    }
    _isClicked = !_isClicked;
}

void Tile::setResources(const std::vector<int>& resources)
{
    if (resources.size() == 8) {
        for (size_t i = 0; i < _resources.size() - 1; ++i) {
            _resources[i] = resources[i];
        }
    }
}


std::vector<int> Tile::getResources() const
{
    return _resources;
}

void Tile::addResource(int resourceIndex, int amount)
{
    if (resourceIndex >= 0 && resourceIndex < _resources.size()) {
        _resources[resourceIndex] += amount;
    }
}

void Tile::removeResource(int resourceIndex, int amount)
{
    if (resourceIndex >= 0 && resourceIndex < _resources.size() && _resources[resourceIndex] >= amount) {
        _resources[resourceIndex] -= amount;
    }
}

void Tile::addEgg(int id, Vector3 position, int resourceIndex)
{
    auto eggModel = ModelsLoader::getInstance()->getModel("EGG");
    auto eggResource = std::make_shared<Resource>(eggModel, position);
    Egg egg = {id, position, resourceIndex, eggResource};
    _eggs.push_back(egg);
    _resources[resourceIndex]++;
}

void Tile::removeEgg(int id)
{
    auto it = std::remove_if(_eggs.begin(), _eggs.end(), [id](const Egg& egg) {
        return egg.id == id;
    });
    if (it != _eggs.end()) {
        _resources[it->resourceIndex]--;
        _eggs.erase(it);
    }
}


