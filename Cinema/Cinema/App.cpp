#include "App.h"

void App::Run() {
    db.Init();
    moviesScreen.Init(&db);

    while (!WindowShouldClose() && state != EXIT) {
        gameStates prevState = state;

        if (state == MAIN_MENU) menu.Update(&state);
        if (state == MOVIES)    moviesScreen.Update(&state);
        if (state == SHOWS)     showsScreen.Update(&state);

        if (prevState != MOVIES && state == MOVIES)
            moviesScreen.Init(&db);
        if (prevState != SHOWS && state == SHOWS)
            showsScreen.Init(&db, moviesScreen.selectedMovieId);

        BeginDrawing();
        ClearBackground(BLACK);
        if (state == MAIN_MENU) menu.Draw();
        if (state == MOVIES)    moviesScreen.Draw();
        if (state == SHOWS)     showsScreen.Draw();
        if (state == BOOKING)   DrawText("BOOKING SCREEN - COMING SOON", 400, 300, 30, ORANGE);
        EndDrawing();
    }
}