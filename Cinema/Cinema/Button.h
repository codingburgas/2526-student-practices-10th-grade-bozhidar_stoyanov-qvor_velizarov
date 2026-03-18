#pragma once
#include "raylib.h"

class Button {
public:
    Button(float x, float y, float width, float height,
        const char* text, Color color = ORANGE, Color textColor = WHITE);
    void Draw();
    bool isClicked();
private:
    Rectangle button;
    const char* text;
    Color color;
    Color textColor;
};