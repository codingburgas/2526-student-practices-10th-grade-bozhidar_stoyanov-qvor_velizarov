#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Logic\FileManager.h"
#include <string>
using namespace std;

class LoginScreen {
public:
    void Init();
    void Draw();
    void Update(gameStates* state);

    string loggedInUser = "";

private:
    int frameCount = 0;
    int activeField = -1;
    bool showError = false;
    string errorMsg = "";

    char userBuf[32] = {};
    char passBuf[32] = {};

    Button loginBtn = Button(440, 400, 400, 55, "Login", ORANGE);
    Button signupBtn = Button(440, 470, 400, 55, "Sign Up", DARKGRAY);
    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);

    void HandleTextInput(char* buf, int maxLen, int fieldId);
};