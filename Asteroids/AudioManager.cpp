#include "AudioManager.h"
#include <iostream>

bool AudioManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load sound file: " << filename << std::endl;
        return false;
    }

    buffers[name] = buffer;

    sf::Sound sound;
    sound.setBuffer(buffers[name]);
    sounds[name] = sound;

    return true;
}

void AudioManager::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.play();
    }
    else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void AudioManager::stopSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.stop();
    }
}

void AudioManager::stopAllSounds() {
    for (auto& pair : sounds) {
        pair.second.stop();
    }
}

bool AudioManager::playMusic(const std::string& filename, bool loop) {
    if (!backgroundMusic.openFromFile(filename)) {
        std::cerr << "Failed to load music file: " << filename << std::endl;
        return false;
    }
    backgroundMusic.setLoop(loop);
    backgroundMusic.play();
    return true;
}

void AudioManager::stopMusic() {
    backgroundMusic.stop();
}

void AudioManager::pauseMusic() {
    backgroundMusic.pause();
}

void AudioManager::resumeMusic() {
    backgroundMusic.play();
}

void AudioManager::setMusicVolume(float volume) {
    backgroundMusic.setVolume(volume); // volume từ 0 đến 100
}
