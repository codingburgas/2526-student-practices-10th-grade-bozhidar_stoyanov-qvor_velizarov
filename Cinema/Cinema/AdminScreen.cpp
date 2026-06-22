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