#include "Menu.h"

void Menu::Draw() {
    DrawText("CINEMA CITY",
        GetScreenWidth() / 2 - MeasureText("CINEMA CITY", 60) / 2,
        100, 60, ORANGE);
    browseBtn.Draw();
    adminBtn.Draw();
    exitBtn.Draw();
}

void Menu::Update(gameStates* state) {
    if (browseBtn.isClicked()) *state = MOVIES;
    if (adminBtn.isClicked())  *state = LOGIN;
    if (exitBtn.isClicked())   *state = EXIT;
}