#include "MoviesScreen.h"

void MoviesScreen::Init(DataManager* db) {
    this->db = db;
    frameCount = 0;
}

vector<Movie> MoviesScreen::GetFiltered() {
    vector<Movie> result;
    string search = searchBuf;

    for (auto& m : db->movies) {
        bool titleMatch = true;
        if (search.size() > 0) {
            string title = m.title;
            for (auto& c : title)  c = tolower(c);
            for (auto& c : search) c = tolower(c);
            titleMatch = title.find(search) != string::npos;
        }

        bool genreMatch = ((int)filterGenre == -1) || m.genre == filterGenre;
        bool langMatch = ((int)filterLang == -1) || m.language == filterLang;

        if (titleMatch && genreMatch && langMatch)
            result.push_back(m);
    }
    return result;
}

string MoviesScreen::GenreToStr(Genre g) {
    switch (g) {
    case Genre::ACTION: return "Action";
    case Genre::COMEDY: return "Comedy";
    case Genre::DRAMA:  return "Drama";
    case Genre::HORROR: return "Horror";
    case Genre::SCIFI:  return "Sci-Fi";
    default:            return "Unknown";
    }
}

string MoviesScreen::LangToStr(Language l) {
    switch (l) {
    case Language::ENGLISH:   return "English";
    case Language::BULGARIAN: return "Bulgarian";
    default:                  return "Unknown";
    }
}

void MoviesScreen::Draw() {
    DrawText("BROWSE MOVIES",
        GetScreenWidth() / 2 - MeasureText("BROWSE MOVIES", 40) / 2,
        20, 40, ORANGE);

    DrawText("Search:", 20, 88, 22, WHITE);
    Rectangle searchBox = { 90, 80, 100, 36 };
    DrawRectangleRounded(searchBox, 0.3f, 8,
        searchActive ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(searchBox, 0.3f, 8,
        searchActive ? ORANGE : GRAY);
    DrawText(searchBuf, 98, 88, 20, WHITE);

    filterAction.Draw();
    filterComedy.Draw();
    filterDrama.Draw();
    filterHorror.Draw();
    filterScifi.Draw();
    filterEng.Draw();
    filterBul.Draw();
    clearFilter.Draw();

    vector<Movie> filtered = GetFiltered();
    int cardX = 40, cardY = 140, cardW = 370, cardH = 110, cols = 3;

    if (filtered.empty()) {
        DrawText("No movies found.", 40, 200, 25, GRAY);
        backBtn.Draw();
        return;
    }

    for (int i = 0; i < (int)filtered.size(); i++) {
        int col = i % cols;
        int row = i / cols;
        int x = cardX + col * (cardW + 20);
        int y = cardY + row * (cardH + 16);

        Rectangle card = { (float)x, (float)y, (float)cardW, (float)cardH };
        bool hovered = CheckCollisionPointRec(GetMousePosition(), card);

        DrawRectangleRounded(card, 0.15f, 8,
            hovered ? Color{ 60,40,0,255 } : Color{ 30,30,30,255 });
        DrawRectangleRoundedLines(card, 0.15f, 8,
            hovered ? ORANGE : DARKGRAY);

        DrawText(filtered[i].title.c_str(), x + 14, y + 12, 22, ORANGE);
        DrawText(filtered[i].releaseDate.c_str(), x + 14, y + 40, 18, LIGHTGRAY);

        string info = GenreToStr(filtered[i].genre) + "  |  " + LangToStr(filtered[i].language);
        DrawText(info.c_str(), x + 14, y + 64, 18, GRAY);

        string desc = filtered[i].description;
        if (desc.size() > 45) desc = desc.substr(0, 45) + "...";
        DrawText(desc.c_str(), x + 14, y + 86, 16, LIGHTGRAY);
    }

    backBtn.Draw();
}

void MoviesScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (backBtn.isClicked()) { *state = MAIN_MENU; return; }

    Rectangle searchBox = { 90, 80, 100, 36 };
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        searchActive = CheckCollisionPointRec(GetMousePosition(), searchBox);

    if (searchActive) {
        int key = GetCharPressed();
        while (key > 0) {
            int len = strlen(searchBuf);
            if (key >= 32 && key <= 125 && len < 63) {
                searchBuf[len] = (char)key;
                searchBuf[len + 1] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            int len = strlen(searchBuf);
            if (len > 0) searchBuf[len - 1] = '\0';
        }
    }

    if (filterAction.isClicked()) filterGenre = Genre::ACTION;
    if (filterComedy.isClicked()) filterGenre = Genre::COMEDY;
    if (filterDrama.isClicked())  filterGenre = Genre::DRAMA;
    if (filterHorror.isClicked()) filterGenre = Genre::HORROR;
    if (filterScifi.isClicked())  filterGenre = Genre::SCIFI;
    if (filterEng.isClicked())    filterLang = Language::ENGLISH;
    if (filterBul.isClicked())    filterLang = Language::BULGARIAN;
    if (clearFilter.isClicked()) {
        filterGenre = (Genre)-1;
        filterLang = (Language)-1;
        memset(searchBuf, 0, sizeof(searchBuf));
    }

    vector<Movie> filtered = GetFiltered();
    int cardX = 40, cardY = 140, cardW = 370, cardH = 110, cols = 3;
    for (int i = 0; i < (int)filtered.size(); i++) {
        int col = i % cols;
        int row = i / cols;
        int x = cardX + col * (cardW + 20);
        int y = cardY + row * (cardH + 16);
        Rectangle card = { (float)x, (float)y, (float)cardW, (float)cardH };
        if (CheckCollisionPointRec(GetMousePosition(), card)
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            selectedMovieId = filtered[i].id;
            *state = SHOWS;
        }
    }
}