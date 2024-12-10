#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>

class AudioManager {
public:
    static AudioManager& GetInstance() {
        static AudioManager instance;
        return instance;
    }

    void LoadSounds(const std::string& name, const std::string& filePath);
    void PlaySounds(const std::string& name);
    void UnloadSounds(const std::string& name);
    void UnloadAllSounds();

    void LoadMusics(const std::string& name, const std::string& filePath);
    void PlayMusics(const std::string& name);
    void StopMusics(const std::string& name);
    void UnloadMusics(const std::string& name);
    void UnloadAllMusics();

    Music& GetMusic(const std::string& name);

private:
    AudioManager() {}
    ~AudioManager() {
        UnloadAllSounds();
        UnloadAllMusics();
    }

    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> musicTracks;
};