#pragma once
#include "utils.h"
#include "raylib.h"
#include <string>
using namespace std;

class CompletedScreen {
public:
    void Init();
    void Draw();
    void Update(gameStates* state);

private:
    float progress = 0.0f;
    float timer = 0.0f;
    bool done = false;
};