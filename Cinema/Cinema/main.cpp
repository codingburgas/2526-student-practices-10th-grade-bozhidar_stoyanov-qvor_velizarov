#include "raylib.h"
#include "App.h"

int main() {
    InitWindow(1280, 720, "Cinema Booking System");
    SetTargetFPS(60);
    App app;
    app.Run();
    CloseWindow();
    return 0;
}