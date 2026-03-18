#include "Button.h"

Button::Button(float x, float y, float width, float height,
    const char* text, Color color, Color textColor) {
    button = { x, y, width, height };
    this->text = text;
    this->color = color;
    this->textColor = textColor;
}

void Button::Draw() {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);
    Color c = hovered ? Color{ (unsigned char)(color.r + 30),
                               (unsigned char)(color.g + 30),
                               (unsigned char)(color.b + 30), 255 } : color;
    DrawRectangleRounded(button, 0.3f, 8, c);
    int tw = MeasureText(text, 25);
    DrawText(text,
        (int)(button.x + button.width / 2 - tw / 2),
        (int)(button.y + button.height / 2 - 12),
        25, textColor);
}

bool Button::isClicked() {
    return CheckCollisionPointRec(GetMousePosition(), button)
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}