#include "App.h"

void App::Run() {
    db.Init();
    loginScreen.Init();
    signupScreen.Init();
    moviesScreen.Init(&db);
    adminScreen.Init(&db);

    while (!WindowShouldClose() && state != EXIT) {
        gameStates prevState = state;

        if (state == LOGIN)     loginScreen.Update(&state);
        if (state == SIGNUP)    signupScreen.Update(&state);
        if (state == MAIN_MENU) menu.Update(&state);
        if (state == MOVIES)    moviesScreen.Update(&state);
        if (state == SHOWS)     showsScreen.Update(&state);
        if (state == BOOKING)   bookingScreen.Update(&state);
        if (state == COMPLETED) completedScreen.Update(&state);
        if (state == ADMIN)     adminScreen.Update(&state);

        if (prevState != LOGIN && state == LOGIN)
            loginScreen.Init();
        if (prevState != SIGNUP && state == SIGNUP)
            signupScreen.Init();
        if (prevState != MOVIES && state == MOVIES)
            moviesScreen.Init(&db);
        if (prevState != SHOWS && state == SHOWS)
            showsScreen.Init(&db, moviesScreen.selectedMovieId);
        if (prevState != BOOKING && state == BOOKING)
            bookingScreen.Init(&db, showsScreen.selectedShowId);
        if (prevState != COMPLETED && state == COMPLETED)
            completedScreen.Init();
        if (prevState != ADMIN && state == ADMIN)
            adminScreen.Init(&db);

        BeginDrawing();
        ClearBackground(BLACK);
        if (state == LOGIN)     loginScreen.Draw();
        if (state == SIGNUP)    signupScreen.Draw();
        if (state == MAIN_MENU) menu.Draw();
        if (state == MOVIES)    moviesScreen.Draw();
        if (state == SHOWS)     showsScreen.Draw();
        if (state == BOOKING)   bookingScreen.Draw();
        if (state == COMPLETED) completedScreen.Draw();
        if (state == ADMIN)     adminScreen.Draw();
        EndDrawing();
    }
}