#include "AdminScreen.h"

void AdminScreen::Init(DataManager* db) {
    this->db = db;
    adminState = AdminState::MAIN;
    frameCount = 0;
    selectedId = -1;
}

void AdminScreen::HandleTextInput(char* buf, int maxLen, int fieldId) {
    if (activeField != fieldId) return;
    int key = GetCharPressed();
    while (key > 0) {
        int len = strlen(buf);
        if (key >= 32 && key <= 125 && len < maxLen - 1) {
            buf[len] = (char)key;
            buf[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(buf);
        if (len > 0) buf[len - 1] = '\0';
    }
}

void AdminScreen::DrawMain() {
    DrawText("ADMIN PANEL",
        GetScreenWidth() / 2 - MeasureText("ADMIN PANEL", 40) / 2,
        100, 40, ORANGE);

    addMovieBtn.Draw();
    deleteMovieBtn.Draw();
    addShowBtn.Draw();
    deleteShowBtn.Draw();
    updateShowBtn.Draw();
    backBtn.Draw();
}

void AdminScreen::DrawDeleteMovie() {
    DrawText("DELETE MOVIE",
        GetScreenWidth() / 2 - MeasureText("DELETE MOVIE", 36) / 2,
        20, 36, ORANGE);

    int y = 100;
    for (auto& m : db->movies) {
        Rectangle card = { 300, (float)y, 680, 50 };
        bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
        DrawRectangleRounded(card, 0.2f, 8, hovered ? Color{ 100,0,0,255 } : Color{ 30,30,30,255 });
        DrawRectangleRoundedLines(card, 0.2f, 8, hovered ? RED : DARKGRAY);
        DrawText(m.title.c_str(), 320, y + 14, 22, WHITE);
        DrawText("Click to delete", 820, y + 14, 18, RED);
        y += 66;
    }

    cancelBtn.Draw();
}