/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include "Server.hpp"
#include <limits>
#include <algorithm>
#include <unistd.h>

GameEngine::GameEngine() : _isRunning(false), _sizeX(0), _sizeY(0)
{
    _camera = CameraWrapper::getInstance();
    _hud = HUD::getInstance();
    _music = SoundWrap::getInstance();
}

void GameEngine::setMapSize(float sizeX, float sizeY)
{
    _sizeX = sizeX;
    _sizeY = sizeY;
}

void GameEngine::loadTiles()
{
    for (float x = 0; x < _sizeX; ++x) {
        for (float y = 0; y < _sizeY; ++y) {
            Vector3 position = {x * 10, 0.0f, y * 10};
            _tiles.push_back(std::make_shared<Tile>(position, _tileModel, _resourceModels));
            _renderables.push_back(_tiles.back());
            _clickables.push_back(_tiles.back());
        }
    }
}

void GameEngine::loadModels()
{
    _tileModel = _modelsGetter->getModel("Island_farm");
    if (!_tileModel.meshCount) {
        std::cerr << "Failed to load model: assets/island_farm.glb" << std::endl;
        throw std::runtime_error("Failed to load model");
    }

    _resourceModels.push_back(_modelsGetter->getModel("FOOD"));
    _resourceModels.push_back(_modelsGetter->getModel("LINEMATE"));
    _resourceModels.push_back(_modelsGetter->getModel("DERAUMERE"));
    _resourceModels.push_back(_modelsGetter->getModel("SIBUR"));
    _resourceModels.push_back(_modelsGetter->getModel("MENDIANE"));
    _resourceModels.push_back(_modelsGetter->getModel("PHIRAS"));
    _resourceModels.push_back(_modelsGetter->getModel("THYSTAME"));
    _resourceModels.push_back(_modelsGetter->getModel("EGG"));
}

GameEngine::~GameEngine() {}

void GameEngine::Initialize()
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1920, 1080, "3D Game with Raylib");
    _music->init();
    _music->playMusic();
    SetTargetFPS(144);
    _modelsGetter = ModelsLoader::getInstance();
    this->loadModels();
    this->loadTiles();

    Server::getInstance()->send_data("sgt\n");

    _buttonAdd = { 100, 100, 50, 50 };
    _buttonRemove = { 200, 100, 50, 50 };

    const float lightX = (float)(_sizeX / 2 * 10);
    const float lightZ = (float)(_sizeY / 2 * 10);
    const Vector3 lightPosition = { lightX, 15, lightZ };

    _lightWrapper = LightWrapper::getInstance();
    _lightWrapper->SetShaderToModel(_renderables);
    _lightWrapper->createlight(lightPosition, Vector3Zero(), YELLOW);
}

void GameEngine::askinventory(int freq)
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - _lastSendTime).count();
    if (duration >= freq / _freq) {
        for (auto& player : _players) {
            Server::getInstance()->send_data("pin #" + std::to_string(player->getId()) + "\n");
        }
        _lastSendTime = std::chrono::steady_clock::now();
    }
}

void GameEngine::Run()
{
    Initialize();
    const float cycleDuration = 180.0f;
    const float dayPhaseDuration = cycleDuration / 4.0f;
    const float sendFrequency = 126.0f;
    float currentTime, cycleTime;
    _lastSendTime = std::chrono::steady_clock::now();

    while (!WindowShouldClose()) {
        currentTime = GetTime();
        cycleTime = fmod(currentTime, cycleDuration);
        _lightWrapper->UpdateLightDayColor(cycleTime, dayPhaseDuration);
        float deltaTime = GetFrameTime();

        _lightWrapper->updateShaderValues(_camera->getX(), _camera->getY(), _camera->getZ());
        Update(deltaTime);
        Render();
        DrawFPS(10, 10);
        if (IsKeyPressed(KEY_I)) {
            _hud->ClearMessages();
        }
        handleFrequency();
        askinventory(sendFrequency);
        // if (_isRunning == false) {
            
        // }
    }
    CloseWindow();
    exit(0);
}

void GameEngine::Shutdown() {}

void GameEngine::Update(float deltaTime)
{
    _music->Update();
    _camera->handleInput(deltaTime);
    _camera->update();

    Vector3 rayOrigin = GetMouseRay(GetMousePosition(), _camera->getCamera()).position;
    Vector3 rayDirection = GetMouseRay(GetMousePosition(), _camera->getCamera()).direction;
    float closestDistance = std::numeric_limits<float>::max();
    std::shared_ptr<IClickable> closestElement = nullptr;

    Ray ray = {rayOrigin, rayDirection};

    for (auto& clickable : _clickables) {
        clickable->setHover(false);
    }

    for (auto& player : _players) {
        RayCollision collision = GetRayCollisionBox(ray, player->getBoundingBox());
        if (collision.hit && collision.distance < closestDistance) {
            closestDistance = collision.distance;
            closestElement = player;
        }
    }

    if (!closestElement) {
        for (auto& tile : _tiles) {
            RayCollision collision = GetRayCollisionBox(ray, tile->getBoundingBox());
            if (collision.hit && collision.distance < closestDistance) {
                closestDistance = collision.distance;
                closestElement = tile;
            }
        }
    }

    if (closestElement) {
        closestElement->setHover(true);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            closestElement->OnClick();
        }
    }
}

void GameEngine::Render()
{
    try {
        std::cerr << "Start Render()" << std::endl;
        BeginDrawing();
        ClearBackground(_lightWrapper->getCurrentBackgroundColor());
        DrawText(TextFormat("Frequency: %d", _freq), 100, 10, 20, DARKGREEN);
        BeginMode3D(_camera->getCamera());

        for (auto &renderable : _renderables) {
            if (renderable) {
                renderable->Render();
            }
        }

        _lightWrapper->drawSphereOnLights();
        EndMode3D();

        _hud->Render();
        EndDrawing();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in Render(): " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught in Render()" << std::endl;
    }
}

void GameEngine::UpdateTileResources(int x, int y, const std::vector<int>& resources)
{
    int index = x * _sizeY + y;
    if (index >= 0 && index < _tiles.size()) {
        _tiles[index]->setResources(resources);   
    }
}

void GameEngine::AddPlayer(int id, int x, int y, int orientation, const std::string& teamName, int level)
{
    Vector3 position = {(float)x * 10.0f, 0.0f, (float)y * 10.0f};
    auto player = std::make_shared<Player>(id, position, orientation, teamName, level);
    _players.push_back(player);
    _renderables.push_back(player);
    _clickables.push_back(player);
}

void GameEngine::RemovePlayer(int id)
{
    auto player = std::find_if(_players.begin(), _players.end(), [id](const std::shared_ptr<Player>& player) {
        return player->getId() == id;
    });

    if (player != _players.end()) {
        _renderables.erase(std::find(_renderables.begin(), _renderables.end(), *player));
        _clickables.erase(std::find(_clickables.begin(), _clickables.end(), *player));
        _players.erase(player);
    }
}

void GameEngine::addFullPlayer(Player player)
{
    auto newPlayer = std::make_shared<Player>(player);
    _players.push_back(newPlayer);
    _renderables.push_back(newPlayer);
    _clickables.push_back(newPlayer);
}

void GameEngine::UpdatePlayerPosition(int id, int x, int y, int orientation)
{
    for (auto& player : _players) {
        if (player->getId() == id) {
            Vector3 position = {(float)x * 10.0f, 0.0f, (float)y * 10.0f};
            player->setPosition(position);
            player->setOrientation(orientation);
            break;
        }
    }
}

void GameEngine::removeResourceTail(int x, int y, int resourceIndex, int amount)
{
    int index = x * _sizeY + y;
    if (index >= 0 && index < _tiles.size()) {
        _tiles[index]->removeResource(resourceIndex, amount);
    }
}

void GameEngine::addResourceTail(int x, int y, int resourceIndex, int amount)
{
    int index = x * _sizeY + y;
    if (index >= 0 && index < _tiles.size()) {
        _tiles[index]->addResource(resourceIndex, amount);
    }
}

void GameEngine::addEgg(int id, int x, int y, int resourceIndex)
{
    int index = x * _sizeY + y;
    if (index >= 0 && index < _tiles.size()) {
        _tiles[index]->addEgg(id, {x * 10.0f, 0.0f, y * 10.0f}, resourceIndex);
    }
}

void GameEngine::RemoveEgg(int id)
{
    for (auto& tile : _tiles) {
        tile->removeEgg(id);
    }
}

void GameEngine::handleFrequency()
{
    if (IsKeyPressed(KEY_K)) {
        if (_freq < 241) {
            _freq += 10;
            Server::getInstance()->send_data("sst " + std::to_string(_freq) + "\n");
        }
    } else if (IsKeyPressed(KEY_J)) {
        if (_freq > 10) {
            _freq -= 10;
            Server::getInstance()->send_data("sst " + std::to_string(_freq) + "\n");
        }
    }
}
