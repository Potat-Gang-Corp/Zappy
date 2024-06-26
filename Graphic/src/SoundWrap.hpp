/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Sound
*/

#pragma once

#ifndef SOUND_HPP_
    #define SOUND_HPP_

    #include <memory>
    #include <raylib.h>
    #include "ModelsLoader.hpp"

class SoundWrap {
    public:
        SoundWrap();
        static std::shared_ptr<SoundWrap> &getInstance() {
            static std::shared_ptr<SoundWrap> instance = std::make_shared<SoundWrap>();
            return instance;
        }
        void init();
        void playMusic();
        void stopMusic();
        void Update();
        void playSoundWithVolumeAdjustment(Sound sound);
        Music &getMusic() { return _music; }
        void setMusicVolume(float volume);
        void changeMusic(Music music);

    private:
        float _currentVolume = 1.0f;
        Music _music;
};


#endif /* !SOUND_HPP_ */
