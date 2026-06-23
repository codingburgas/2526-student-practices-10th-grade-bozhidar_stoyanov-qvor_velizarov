#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Logic\FileManager.h"
#include <string>
using namespace std;

class SignupScreen {
public:
    void Init();
    void Draw();
    void Update(gameStates* state);

private:
    int frameCount = 0;
    int activeField = -1;
    bool showError = false;
    bool showSuccess = false;
    string errorMsg = "";

    char userBuf[32] = {};
    char passBuf[32] = {};
    char confirmBuf[32] = {};

    Button signupBtn = Button(440, 470, 400, 55, "Create Account", ORANGE);
    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);

    void HandleTextInput(char* buf, int maxLen, int fieldId);
};