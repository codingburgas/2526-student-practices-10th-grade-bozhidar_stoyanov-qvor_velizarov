#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Data\DataManager.h"
#include <string>
using namespace std;

enum class AdminState {
    MAIN,
    ADD_MOVIE,
    DELETE_MOVIE
};

class AdminScreen {
public:
    void Init(DataManager* db);
    void Draw();
    void Update(gameStates* state);

private:
    DataManager* db;
    AdminState   adminState = AdminState::MAIN;
    int          frameCount = 0;
    int          selectedId = -1;

    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);
    Button addMovieBtn = Button(440, 280, 400, 60, "Add Movie", ORANGE);
    Button deleteMovieBtn = Button(440, 360, 400, 60, "Delete Movie", DARKGRAY);

    char titleBuf[64] = {};
    char dateBuf[12] = {};
    char descBuf[128] = {};
    int  activeField = -1;
    Genre    selGenre = Genre::ACTION;
    Language selLang = Language::ENGLISH;

    Button confirmAddMovie = Button(440, 560, 400, 50, "Add Movie", ORANGE);
    Button cancelBtn = Button(20, 20, 120, 45, "< Cancel", DARKGRAY);

    void DrawMain();
    void DrawAddMovie();
    void DrawDeleteMovie();

    void UpdateMain(gameStates* state);
    void UpdateAddMovie();
    void UpdateDeleteMovie();

    void HandleTextInput(char* buf, int maxLen, int fieldId);
};