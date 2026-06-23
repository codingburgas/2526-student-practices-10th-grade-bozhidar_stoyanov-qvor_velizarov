#include "LoginScreen.h"
#include <cstring>

void LoginScreen::Init() {
    frameCount = 0;
    activeField = -1;
    showError = false;
    errorMsg = "";
    memset(userBuf, 0, sizeof(userBuf));
    memset(passBuf, 0, sizeof(passBuf));
}

void LoginScreen::HandleTextInput(char* buf, int maxLen, int fieldId) {
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

void LoginScreen::Draw() {
    DrawText("ADMIN PANEL",
        GetScreenWidth() / 2 - MeasureText("ADMIN PANEL", 40) / 2,
        80, 40, ORANGE);

    DrawText("Login to your account",
        GetScreenWidth() / 2 - MeasureText("Login to your account", 22) / 2,
        130, 22, GRAY);

    DrawText("Username:", 340, 222, 22, WHITE);
    Rectangle userBox = { 340, 250, 600, 44 };
    DrawRectangleRounded(userBox, 0.3f, 8, activeField == 0 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(userBox, 0.3f, 8, activeField == 0 ? ORANGE : GRAY);
    DrawText(userBuf, 354, 260, 22, WHITE);

    DrawText("Password:", 340, 312, 22, WHITE);
    Rectangle passBox = { 340, 340, 600, 44 };
    DrawRectangleRounded(passBox, 0.3f, 8, activeField == 1 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(passBox, 0.3f, 8, activeField == 1 ? ORANGE : GRAY);

    string hidden(strlen(passBuf), '*');
    DrawText(hidden.c_str(), 354, 350, 22, WHITE);

    if (showError)
        DrawText(errorMsg.c_str(),
            GetScreenWidth() / 2 - MeasureText(errorMsg.c_str(), 20) / 2,
            540, 20, RED);

    loginBtn.Draw();
    signupBtn.Draw();
    backBtn.Draw();
}

void LoginScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    Rectangle userBox = { 340, 250, 600, 44 };
    Rectangle passBox = { 340, 340, 600, 44 };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), userBox)) activeField = 0;
        else if (CheckCollisionPointRec(GetMousePosition(), passBox)) activeField = 1;
        else activeField = -1;
    }

    HandleTextInput(userBuf, 32, 0);
    HandleTextInput(passBuf, 32, 1);

    if (loginBtn.isClicked()) {
        if (strlen(userBuf) == 0 || strlen(passBuf) == 0) {
            showError = true;
            errorMsg = "Please fill in all fields.";
        }
        else if (FileManager::CheckUser(userBuf, passBuf)) {
            loggedInUser = userBuf;
            *state = ADMIN;
        }
        else {
            showError = true;
            errorMsg = "Wrong username or password.";
        }
    }

    if (signupBtn.isClicked()) {
        *state = SIGNUP;
    }

    if (backBtn.isClicked())
    {
        *state = MAIN_MENU;
    }
}