#pragma once
#include "utils.h"
#include "raylib.h"

class CompletedScreen {
public:
    void Init();
    void Draw();
    void Update(gameStates* state);

private:
    float progress = 0.0f;
    float timer = 0.0f;
    bool  done = false;
};