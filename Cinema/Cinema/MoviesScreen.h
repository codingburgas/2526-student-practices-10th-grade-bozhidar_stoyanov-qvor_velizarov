#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Data\DataManager.h"
#include <string>
#include <map>
using namespace std;

class MoviesScreen {
public:
    void Init(DataManager* db);
    void Draw();
    void Update(gameStates* state);

    int selectedMovieId = -1;
    int selectedCinemaId = 1;

private:
    DataManager* db;
    int frameCount = 0;

    map<int, Texture2D> textures;

    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);
    Button filterAction = Button(320, 80, 100, 36, "Action", DARKGRAY);
    Button filterComedy = Button(430, 80, 100, 36, "Comedy", DARKGRAY);
    Button filterDrama = Button(540, 80, 100, 36, "Drama", DARKGRAY);
    Button filterHorror = Button(650, 80, 100, 36, "Horror", DARKGRAY);
    Button filterScifi = Button(760, 80, 100, 36, "Sci-Fi", DARKGRAY);
    Button filterEng = Button(870, 80, 110, 36, "English", DARKGRAY);
    Button filterBul = Button(990, 80, 110, 36, "Bulgarian", DARKGRAY);
    Button clearFilter = Button(1110, 80, 90, 36, "Clear", RED);

    char searchBuf[64] = {};
    bool searchActive = false;

    Genre filterGenre = (Genre)-1;
    Language filterLang = (Language)-1;

    vector<Movie> GetFiltered();
    string GenreToStr(Genre g);
    string LangToStr(Language l);
};