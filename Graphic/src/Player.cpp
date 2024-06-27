/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** Player
*/

#include "Player.hpp"
#include <iostream>
#include "raymath.h"
#include "Utils.hpp"
#include "ModelsLoader.hpp"
#include <map>

Player::Player(int id, Vector3 position, int orientation, const std::string& teamName, int level) : _id(id), _position(position), _scale(0.09f),
_orientation(orientation), _teamName(teamName), _hover(false), _clicked(false), _level(level), _frameCounter(0), _currentAnimation(0)
{
    _model = ModelsLoader::getInstance()->getModel("PlayerModel");

    _hud = HUD::getInstance();
    _animations = ModelsLoader::getInstance()->getAnim("Player");
    loadDefaultAnimation();
    _inventory.resize(7, 0);
    _boundingBox = GetModelBoundingBox(_model);
    _boundingBox.min = Vector3Scale(_boundingBox.min, _scale);
    _boundingBox.max = Vector3Scale(_boundingBox.max, _scale);
    _boundingBox.min = Vector3Add(_boundingBox.min, position);
    _boundingBox.max = Vector3Add(_boundingBox.max, position);
}

Player::~Player() {}

void Player::Render()
{
    float angle = 0.0f;
    switch (_orientation) {
        case 1: angle = 180.0f; break;
        case 2: angle = 90.0f; break;
        case 3: angle = 0.0f; break;
        case 4: angle = -90.0f; break;
    }

    _frameCounter++;
    UpdateModelAnimation(_model, _animations.get()[_currentAnimation], _frameCounter);
    if (_frameCounter >= _animations.get()[_currentAnimation].frameCount) {
        _frameCounter = 0;
        if (_currentAnimation != 0) {
            _currentAnimation = 0;
            loadDefaultAnimation();
        }
    }
    DrawModelEx(_model, _position, (Vector3){0, 1, 0}, angle, (Vector3){_scale, _scale, _scale}, WHITE);
    // DrawBoundingBox(_boundingBox, GREEN);
}

void Player::OnClick()
{
    _hud->ClearMessages();
    std::ostringstream streamX, streamZ;
    streamX << std::fixed << std::setprecision(0) << _position.x / 10.0f;
    streamZ << std::fixed << std::setprecision(0) << _position.z / 10.0f;
    std::string message = "Player #" + std::to_string(_id) + " at (" + streamX.str() + ", " + streamZ.str() + "): ";
    _hud->AddMessage(message);
    message = "Level " + std::to_string(_level);
    _hud->AddMessage(message);
    message = "Team: \"" + _teamName + "\"";
    _hud->AddMessage(message);
    message = "Orientation: " + Utils::getInstance()->orientationToString(_orientation);
    _hud->AddMessage(message);

    message = "Inventory: ";
    _hud->AddMessage(message);
    for (size_t i = 0; i < _inventory.size(); ++i) {
        message = Utils::getInstance()->indexToString(i);
        message += std::to_string(_inventory[i]);
        _hud->AddMessage(message);
    }
    _clicked = !_clicked;
}

void Player::setHover(bool hover)
{
    _hover = hover;
}

bool Player::isHovered() const
{
    return _hover;
}

void Player::setPosition(Vector3 position)
{
    this->_position = position;
    _boundingBox = GetModelBoundingBox(_model);
    _boundingBox.min = Vector3Scale(_boundingBox.min, _scale);
    _boundingBox.max = Vector3Scale(_boundingBox.max, _scale);
    _boundingBox.min = Vector3Add(_boundingBox.min, position);
    _boundingBox.max = Vector3Add(_boundingBox.max, position);
}

void Player::setOrientation(int orientation)
{
    this->_orientation = orientation;
}

void Player::playAnimation(const std::string& animationPath)
{
    std::shared_ptr<ModelAnimation> newAnimations = ModelsLoader::getInstance()->getAnim(animationPath.c_str());
    if (newAnimations) {
        for (int i = 0; i < _animationCount; i++) {
            UnloadModelAnimation(_animations.get()[i]);
        }
        RL_FREE(_animations.get());

        _animations = newAnimations;
        _currentAnimation = 0;
        _frameCounter = 0;
    }
}

void Player::loadDefaultAnimation()
{
    _currentAnimation = 0;
}

int Player::getId() const {
    return _id;
}

Vector3 Player::getPosition() const {
    return _position;
}

int Player::getOrientation() const {
    return _orientation;
}

std::string Player::getTeamName() const {
    return _teamName;
}

void Player::addInventory(int resourceIndex, int amount)
{
    if (resourceIndex >= 0 && resourceIndex < _inventory.size()) {
        _inventory[resourceIndex] += amount;
    }
}

void Player::setInventory(const std::vector<int>& inventory)
{
    if (inventory.size() == 8) {
        for (size_t i = 0; i < _inventory.size() - 1; ++i) {
            _inventory[i] = inventory[i];
        }
    }
}

void Player::removeInventory(int resourceIndex, int amount)
{
    if (resourceIndex >= 0 && resourceIndex < _inventory.size() && _inventory[resourceIndex] >= amount) {
        _inventory[resourceIndex] -= amount;
    }
}

void Player::setPlayerLevel(int level)
{
    _level = level;
}