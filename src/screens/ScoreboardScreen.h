#pragma once
#include "Screen.h"
#include <string>
#include "../ui/Button.h"
#include "../ui/ImageButton.h"
#include "../State.h"

class ScoreboardScreen : public Screen {
private:
    ImageButton backButton;
public:
    ScoreboardScreen();
    ~ScoreboardScreen();
    
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};