/**
 * @startuml
 * class Button {
 * }
 * 
 * class Texture2D {
 * }
 * 
 * class Color {
 * }
 * 
 * class ImageButton extends Button {
 *     + ImageButton()
 *     + ImageButton(const char* texturePath, float x, float y)
 *     + ~ImageButton()
 *     + void Unload() <<override>>
 *     + bool Update() <<override>>
 *     + void Draw() <<override>>
 *     - Texture2D texture
 *     - const char* pathTexture
 *     - float scale
 *     - Color tint
 * }
 * 
 * ImageButton "1" *-- "1" Texture2D
 * ImageButton "1" *-- "1" Color
 * @enduml
 */

#pragma once
#include "Button.h"
#include "raylib.h"
#include <string>

class ImageButton : public Button {
private:
    Texture2D texture;
    const char* pathTexture;
    float scale;
    Color tint;

public:
    ImageButton() {};
    ImageButton(const char* texturePath, float x, float y);
    ~ImageButton();
    
    void Unload();
    bool Update() override;
    void Draw() override;
};