#include "App.h"

void App::Run() {
    db.Init();
    moviesScreen.Init(&db);

    while (!WindowShouldClose() && state != EXIT) {
        gameStates prevState = state;

        if (state == MAIN_MENU) menu.Update(&state);
        if (state == MOVIES)    moviesScreen.Update(&state);
        if (state == SHOWS)     showsScreen.Update(&state);
        if (state == BOOKING)   bookingScreen.Update(&state);

        if (prevState != MOVIES && state == MOVIES)
            moviesScreen.Init(&db);
        if (prevState != SHOWS && state == SHOWS)
            showsScreen.Init(&db, moviesScreen.selectedMovieId);
        if (prevState != BOOKING && state == BOOKING)
            bookingScreen.Init(&db, showsScreen.selectedShowId);

        BeginDrawing();
        ClearBackground(BLACK);
        if (state == MAIN_MENU) menu.Draw();
        if (state == MOVIES)    moviesScreen.Draw();
        if (state == SHOWS)     showsScreen.Draw();
        if (state == BOOKING)   bookingScreen.Draw();
        EndDrawing();
    }
}