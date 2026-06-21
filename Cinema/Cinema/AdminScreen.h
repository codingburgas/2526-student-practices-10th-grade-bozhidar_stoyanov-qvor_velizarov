#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Data\DataManager.h"
#include <string>
using namespace std;

enum class AdminState {
    MAIN,
    ADD_MOVIE,
    DELETE_MOVIE,
    ADD_SHOW,
    DELETE_SHOW,
    UPDATE_SHOW
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
    Button addMovieBtn = Button(440, 200, 400, 60, "Add Movie", ORANGE);
    Button deleteMovieBtn = Button(440, 280, 400, 60, "Delete Movie", DARKGRAY);
    Button addShowBtn = Button(440, 360, 400, 60, "Add Show", ORANGE);
    Button deleteShowBtn = Button(440, 440, 400, 60, "Delete Show", DARKGRAY);
    Button updateShowBtn = Button(440, 520, 400, 60, "Update Show", DARKGRAY);

    
    char titleBuf[64] = {};
    char dateBuf[12] = {};
    char descBuf[128] = {};
    int  activeField = -1;
    Genre    selGenre = Genre::ACTION;
    Language selLang = Language::ENGLISH;

    Button confirmAddMovie = Button(440, 560, 400, 50, "Add Movie", ORANGE);
    Button cancelBtn = Button(20, 20, 120, 45, "< Cancel", DARKGRAY);

    
    char showDateBuf[12] = {};
    char showTimeBuf[8] = {};
    int  activeShowField = -1;
    int  selCinemaId = 1;
    int  selHallId = 1;
    int  selMovieId = 1;

    Button confirmAddShow = Button(440, 560, 400, 50, "Add Show", ORANGE);

    void DrawMain();
    void DrawAddMovie();
    void DrawDeleteMovie();
    void DrawAddShow();
    void DrawDeleteShow();

    void UpdateMain(gameStates* state);
    void UpdateAddMovie();
    void UpdateDeleteMovie();
    void UpdateAddShow();
    void UpdateDeleteShow();

    void HandleTextInput(char* buf, int maxLen, int fieldId);
};