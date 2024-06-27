/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Light
*/

#include "Light.hpp"

LightWrapper::LightWrapper()
{
    _shader = LoadShader("assets/lighting.vs", "assets/lighting.fs");
    _shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(_shader, "viewPos");
    int ambientLoc = GetShaderLocation(_shader, "ambient");
    float ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    SetShaderValue(_shader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
}

LightWrapper::~LightWrapper() {}

void LightWrapper::SetShaderToModel(std::vector<std::shared_ptr<IRenderable>> _models)
{
    for (auto &model : _models) {
        for (int i = 0; i < model->getModel().materialCount; i++) {
            model->getModel().materials[i].shader = _shader;
        }
    }
}

void LightWrapper::createlight(Vector3 position, Vector3 target, Color color)
{
    if (_indLight >= MAX_LIGHTS) {
        std::cerr << "Max lights reached" << std::endl;
        return;
    }
    _lights[_indLight] = CreateLight(LIGHT_POINT, position, target, color, _shader);
    _indLight++;
}

void LightWrapper::updateShaderValues(float CamX, float CamY, float CamZ)
{
    float cameraPos[3] = { CamX, CamY, CamZ };
    SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    for (int i = 0; i < MAX_LIGHTS; i++) {
        UpdateLightValues(_shader, _lights[i]);
    }
}

void LightWrapper::drawSphereOnLights()
{
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (_lights[i].enabled) {
            DrawSphereEx(_lights[i].position, 3.0f, 8, 8, _lights[i].color);
        }
    }
}

void LightWrapper::updateLightColor(Color color)
{
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (_lights[i].enabled) {
            _lights[i].color = color;
        }
    }
}

Color LerpColor(Color start, Color end, float amount)
{
    Color result;
    result.r = (unsigned char)((1 - amount) * start.r + amount * end.r);
    result.g = (unsigned char)((1 - amount) * start.g + amount * end.g);
    result.b = (unsigned char)((1 - amount) * start.b + amount * end.b);
    result.a = (unsigned char)((1 - amount) * start.a + amount * end.a);
    return result;
}

void LightWrapper::UpdateLightDayColor(float cycleTime, float dayPhaseDuration)
{
    if (cycleTime < dayPhaseDuration) {
        // Day to Evening
        _currentBackgroundColor = LerpColor(SKYBLUE, ORANGE, cycleTime / dayPhaseDuration);
        _currentLightColor = LerpColor(YELLOW, RED, cycleTime / dayPhaseDuration);
    } else if (cycleTime < 2 * dayPhaseDuration) {
        // Evening to Night
        _currentBackgroundColor = LerpColor(ORANGE, DARKBLUE, (cycleTime - dayPhaseDuration) / dayPhaseDuration);
        _currentLightColor = LerpColor(RED, DARKGRAY, (cycleTime - dayPhaseDuration) / dayPhaseDuration);
    } else if (cycleTime < 3 * dayPhaseDuration) {
        // Night to Morning
        _currentBackgroundColor = LerpColor(DARKBLUE, LIGHTGRAY, (cycleTime - 2 * dayPhaseDuration) / dayPhaseDuration);
        _currentLightColor = LerpColor(DARKGRAY, ORANGE, (cycleTime - 2 * dayPhaseDuration) / dayPhaseDuration);
    } else {
        // Morning to Day
        _currentBackgroundColor = LerpColor(LIGHTGRAY, SKYBLUE, (cycleTime - 3 * dayPhaseDuration) / dayPhaseDuration);
        _currentLightColor = LerpColor(ORANGE, YELLOW, (cycleTime - 3 * dayPhaseDuration) / dayPhaseDuration);
    }
    updateLightColor(_currentLightColor);
}
