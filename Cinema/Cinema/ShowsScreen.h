#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Data\DataManager.h"
#include <string>
using namespace std;

class ShowsScreen {
public:
    void Init(DataManager* db, int movieId);
    void Draw();
    void Update(gameStates* state);

    int selectedShowId = -1;

private:
    DataManager* db;
    int movieId = -1;
    int frameCount = 0;

    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);

    Movie* GetMovie();
    string GetCinemaName(int cinemaId);
    string GetHallName(int cinemaId, int hallId);
};