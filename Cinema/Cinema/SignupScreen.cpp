#include "SignupScreen.h"

void SignupScreen::Init() {
    frameCount = 0;
    activeField = -1;
    showError = false;
    showSuccess = false;
    errorMsg = "";
    memset(userBuf, 0, sizeof(userBuf));
    memset(passBuf, 0, sizeof(passBuf));
    memset(confirmBuf, 0, sizeof(confirmBuf));
}

void SignupScreen::HandleTextInput(char* buf, int maxLen, int fieldId) {
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

void SignupScreen::Draw() {
    DrawText("CREATE ACCOUNT",
        GetScreenWidth() / 2 - MeasureText("CREATE ACCOUNT", 40) / 2,
        80, 40, ORANGE);

    DrawText("Username:", 340, 192, 22, WHITE);
    Rectangle userBox = { 340, 220, 600, 44 };
    DrawRectangleRounded(userBox, 0.3f, 8, activeField == 0 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(userBox, 0.3f, 8, activeField == 0 ? ORANGE : GRAY);
    DrawText(userBuf, 354, 230, 22, WHITE);

    DrawText("Password:", 340, 282, 22, WHITE);
    Rectangle passBox = { 340, 310, 600, 44 };
    DrawRectangleRounded(passBox, 0.3f, 8, activeField == 1 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(passBox, 0.3f, 8, activeField == 1 ? ORANGE : GRAY);
    string hidden(strlen(passBuf), '*');
    DrawText(hidden.c_str(), 354, 320, 22, WHITE);

    DrawText("Confirm Password:", 340, 372, 22, WHITE);
    Rectangle confirmBox = { 340, 400, 600, 44 };
    DrawRectangleRounded(confirmBox, 0.3f, 8, activeField == 2 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(confirmBox, 0.3f, 8, activeField == 2 ? ORANGE : GRAY);
    string hidden2(strlen(confirmBuf), '*');
    DrawText(hidden2.c_str(), 354, 410, 22, WHITE);

    if (showError)
        DrawText(errorMsg.c_str(),
            GetScreenWidth() / 2 - MeasureText(errorMsg.c_str(), 20) / 2,
            540, 20, RED);

    if (showSuccess)
        DrawText("Account created! Go back and login.",
            GetScreenWidth() / 2 - MeasureText("Account created! Go back and login.", 20) / 2,
            540, 20, GREEN);

    signupBtn.Draw();
    backBtn.Draw();
}

void SignupScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (backBtn.isClicked()) { *state = LOGIN; return; }

    Rectangle userBox = { 340, 220, 600, 44 };
    Rectangle passBox = { 340, 310, 600, 44 };
    Rectangle confirmBox = { 340, 400, 600, 44 };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), userBox))    activeField = 0;
        else if (CheckCollisionPointRec(GetMousePosition(), passBox))    activeField = 1;
        else if (CheckCollisionPointRec(GetMousePosition(), confirmBox)) activeField = 2;
        else activeField = -1;
    }

    HandleTextInput(userBuf, 32, 0);
    HandleTextInput(passBuf, 32, 1);
    HandleTextInput(confirmBuf, 32, 2);

    if (signupBtn.isClicked()) {
        if (strlen(userBuf) == 0 || strlen(passBuf) == 0) {
            showError = true;
            showSuccess = false;
            errorMsg = "Please fill in all fields.";
        }
        else if (strcmp(passBuf, confirmBuf) != 0) {
            showError = true;
            showSuccess = false;
            errorMsg = "Passwords do not match.";
        }
        else if (!FileManager::SaveUser(userBuf, passBuf)) {
            showError = true;
            showSuccess = false;
            errorMsg = "Username already exists.";
        }
        else {
            showError = false;
            showSuccess = true;
        }
    }
}