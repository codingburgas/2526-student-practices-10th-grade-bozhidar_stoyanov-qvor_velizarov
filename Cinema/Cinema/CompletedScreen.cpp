#include "CompletedScreen.h"

void CompletedScreen::Init() {
    progress = 0.0f;
    timer = 0.0f;
    done = false;
}

void CompletedScreen::Draw() {
    DrawText("BOOKING COMPLETED!",
        GetScreenWidth() / 2 - MeasureText("BOOKING COMPLETED!", 50) / 2,
        200, 50, GREEN);

    DrawText("Thank you for your booking.",
        GetScreenWidth() / 2 - MeasureText("Thank you for your booking.", 24) / 2,
        270, 24, LIGHTGRAY);

    int barX = 240, barY = 380, barW = 800, barH = 40;
    DrawRectangleRounded({ (float)barX, (float)barY, (float)barW, (float)barH }, 0.5f, 8, DARKGRAY);
    DrawRectangleRounded({ (float)barX, (float)barY, barW * progress, (float)barH }, 0.5f, 8, GREEN);

    string pct = to_string((int)(progress * 100)) + "%";
    DrawText(pct.c_str(),
        GetScreenWidth() / 2 - MeasureText(pct.c_str(), 22) / 2,
        barY + 8, 22, WHITE);

    if (done)
        DrawText("Returning to main menu...",
            GetScreenWidth() / 2 - MeasureText("Returning to main menu...", 20) / 2,
            440, 20, GRAY);
}

void CompletedScreen::Update(gameStates* state) {
    timer += GetFrameTime();
    progress = timer / 3.0f;
    if (progress >= 1.0f) {
        progress = 1.0f;
        done = true;
    }
    if (timer >= 3.5f)
        *state = MAIN_MENU;
}