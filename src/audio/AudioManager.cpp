#include "AudioManager.h"

void AudioManager::LoadSounds(const std::string& name, const std::string& filePath) {
    if (sounds.find(name) == sounds.end()) {
        Sound sound = LoadSound(filePath.c_str());
        if (sound.stream.buffer != nullptr) { // Check if the sound was loaded successfully
            sounds[name] = sound;
        }
    }
}

void AudioManager::PlaySounds(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        ::PlaySound(sounds[name]);
    }
}

void AudioManager::UnloadSounds(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        UnloadSound(sounds[name]);
        sounds.erase(name);
    }
}

void AudioManager::UnloadAllSounds() {
    for (auto& pair : sounds) {
        UnloadSound(pair.second);
    }
    sounds.clear();
}

void AudioManager::LoadMusics(const std::string& name, const std::string& filePath) {
    if (musicTracks.find(name) == musicTracks.end()) {
        Music music = LoadMusicStream(filePath.c_str());
        if (music.ctxData != nullptr) { // Check if the music was loaded successfully
            musicTracks[name] = music;
        }
    }
}

void AudioManager::PlayMusics(const std::string& name) {
    if (musicTracks.find(name) != musicTracks.end()) {
        PlayMusicStream(musicTracks[name]);
    }
}

void AudioManager::StopMusics(const std::string& name) {
    if (musicTracks.find(name) != musicTracks.end()) {
        StopMusicStream(musicTracks[name]);
    }
}

void AudioManager::UnloadMusics(const std::string& name) {
    if (musicTracks.find(name) != musicTracks.end()) {
        UnloadMusicStream(musicTracks[name]);
        musicTracks.erase(name);
    }
}

void AudioManager::UnloadAllMusics() {
    for (auto& pair : musicTracks) {
        UnloadMusicStream(pair.second);
    }
    musicTracks.clear();
}

Music& AudioManager::GetMusic(const std::string& name) {
    return musicTracks.at(name);
}