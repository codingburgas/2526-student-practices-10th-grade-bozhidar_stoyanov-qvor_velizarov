#include "raylib.h"
#include "utils.h"
#include "Menu.h"
#include "MoviesScreen.h"
#include "..\Data\DataManager.h"

int main() {
    InitWindow(1280, 720, "Cinema Booking System");
    SetTargetFPS(60);

    DataManager db;
    db.Init();

    gameStates state = MAIN_MENU;

    Menu menu;
    MoviesScreen moviesScreen;
    moviesScreen.Init(&db);

    while (!WindowShouldClose() && state != EXIT) {
        gameStates prevState = state;
        if (state == MAIN_MENU) menu.Update(&state);
        if (state == MOVIES)    moviesScreen.Update(&state);
        if (prevState != MOVIES && state == MOVIES) moviesScreen.Init(&db);

        BeginDrawing();
        ClearBackground(BLACK);
        if (state == MAIN_MENU) menu.Draw();
        if (state == MOVIES)    moviesScreen.Draw();
        if (state == SHOWS)     DrawText("SHOWS SCREEN - COMING SOON", 400, 300, 30, ORANGE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}