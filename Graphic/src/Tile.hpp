/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** Tile
*/

#pragma once

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include "raylib.h"
    #include "IRenderable.hpp"
    #include "IClickable.hpp"
    #include "Resource.hpp"
    #include "HUD.hpp"
    #include <vector>
    #include <memory>
    #include <map>

struct Egg {
    int id;
    Vector3 position;
    int resourceIndex;
    std::shared_ptr<Resource> resource;
};

class Tile : public IRenderable, public IClickable {
    public:
        Tile(Vector3 position, Model tileModel, const std::vector<Model>& resourceModels);
        ~Tile();

        void Render() override final;
        BoundingBox getBoundingBox() const override final;
        void OnClick() override final;
        void setHover(bool status) override final { _isHovered = status; }
        void setResources(const std::vector<int>& resources);
        std::vector<int> getResources() const;
        void addResource(int resourceIndex, int amount);
        void removeResource(int resourceIndex, int amount);
        void addEgg(int id, Vector3 position, int resourceIndex);
        void removeEgg(int id);
        Model getModel() override final { return _model; }
        Vector3 getEggPosition(int id) { return _eggs[id].position; }

    private:
        Vector3 _position;
        Model _model;
        float _scale;
        BoundingBox _boundingBox;
        bool _isHovered, _isClicked;
        float _rotationAngle;
        std::vector<int> _resources;
        std::vector<std::shared_ptr<Resource>> _resourceObjects;
        std::shared_ptr<HUD> _hud;
        std::vector<Egg> _eggs;
};

#endif /* !TILE_HPP_ */
