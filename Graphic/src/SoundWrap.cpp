/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** SoundWrap
*/

#include "SoundWrap.hpp"
#include "raylib.h"

SoundWrap::SoundWrap()
{
}

void SoundWrap::init()
{
    InitAudioDevice();
    _music = ModelsLoader::getInstance()->getMusic("Ambient");
    PlayMusicStream(_music);
}

void SoundWrap::playMusic()
{
    PlayMusicStream(_music);
}

void SoundWrap::stopMusic()
{
    StopMusicStream(_music);
}

void SoundWrap::Update()
{
    UpdateMusicStream(_music);
}

void SoundWrap::playSoundWithVolumeAdjustment(Sound sound)
{
    setMusicVolume(_currentVolume * 0.5f);
    PlaySound(sound);
    while (IsSoundPlaying(sound)) {
        Update();
    }
    setMusicVolume(_currentVolume);
}

void SoundWrap::setMusicVolume(float volume)
{
    SetMusicVolume(_music, volume);
}

void SoundWrap::changeMusic(Music music)
{
    StopMusicStream(_music);
    UnloadMusicStream(_music);
    _music = music;
    PlayMusicStream(_music);
}
