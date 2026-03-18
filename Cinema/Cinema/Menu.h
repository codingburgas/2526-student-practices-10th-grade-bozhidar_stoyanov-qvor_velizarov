#pragma once
#include "utils.h"
#include "Button.h"

class Menu {
public:
    void Draw();
    void Update(gameStates* state);
private:
    Button browseBtn = Button(440, 280, 400, 60, "Browse Movies");
    Button adminBtn = Button(440, 370, 400, 60, "Admin Panel", DARKGRAY);
    Button exitBtn = Button(440, 460, 400, 60, "Exit", RED);
};