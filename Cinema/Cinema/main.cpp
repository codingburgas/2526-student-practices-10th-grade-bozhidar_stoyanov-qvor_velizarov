#include "raylib.h"
#include "utils.h"
#include "Menu.h"

int main() {
    InitWindow(1280, 720, "Cinema Booking System");
    SetTargetFPS(60);

    gameStates state = MAIN_MENU;
    Menu menu;

    while (!WindowShouldClose() && state != EXIT) {
        menu.Update(&state);
        BeginDrawing();
        ClearBackground(BLACK);
        if (state == MAIN_MENU) menu.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}