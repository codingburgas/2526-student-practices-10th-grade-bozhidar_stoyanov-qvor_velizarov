#include "ShowsScreen.h"

void ShowsScreen::Init(DataManager* db, int movieId) {
    this->db = db;
    this->movieId = movieId;
    frameCount = 0;
    selectedShowId = -1;
}

Movie* ShowsScreen::GetMovie() {
    for (auto& m : db->movies)
        if (m.id == movieId) return &m;
    return nullptr;
}

string ShowsScreen::GetCinemaName(int cinemaId) {
    for (auto& c : db->cinemas)
        if (c.id == cinemaId) return c.name;
    return "Unknown";
}

string ShowsScreen::GetHallName(int cinemaId, int hallId) {
    for (auto& c : db->cinemas)
        if (c.id == cinemaId)
            for (auto& h : c.halls)
                if (h.id == hallId) return h.name;
    return "Unknown";
}

void ShowsScreen::Draw() {
    Movie* movie = GetMovie();
    if (!movie) return;

   
    DrawText(movie->title.c_str(),
        GetScreenWidth() / 2 - MeasureText(movie->title.c_str(), 40) / 2,
        20, 40, ORANGE);

    DrawText("SELECT A SHOW",
        GetScreenWidth() / 2 - MeasureText("SELECT A SHOW", 22) / 2,
        70, 22, GRAY);

    
    vector<Show> movieShows;
    for (auto& s : db->shows)
        if (s.movieId == movieId)
            movieShows.push_back(s);

    if (movieShows.empty()) {
        DrawText("No shows available.", 40, 200, 25, GRAY);
        backBtn.Draw();
        return;
    }

    int cardX = 40, cardY = 120, cardW = 580, cardH = 90;

    for (int i = 0; i < (int)movieShows.size(); i++) {
        int x = cardX;
        int y = cardY + i * (cardH + 16);

        Rectangle card = { (float)x, (float)y, (float)cardW, (float)cardH };
        bool hovered = CheckCollisionPointRec(GetMousePosition(), card);

        DrawRectangleRounded(card, 0.15f, 8,
            hovered ? Color{ 60,40,0,255 } : Color{ 30,30,30,255 });
        DrawRectangleRoundedLines(card, 0.15f, 8,
            hovered ? ORANGE : DARKGRAY);

        string cinema = GetCinemaName(movieShows[i].cinemaId);
        string hall = GetHallName(movieShows[i].cinemaId, movieShows[i].hallId);

        DrawText(cinema.c_str(), x + 14, y + 12, 22, ORANGE);
        DrawText(hall.c_str(), x + 14, y + 40, 18, LIGHTGRAY);
        DrawText(movieShows[i].date.c_str(), x + 300, y + 12, 20, LIGHTGRAY);
        DrawText(movieShows[i].time.c_str(), x + 300, y + 40, 24, WHITE);
    }

    backBtn.Draw();
}

void ShowsScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (backBtn.isClicked()) { *state = MOVIES; return; }

    vector<Show> movieShows;
    for (auto& s : db->shows)
        if (s.movieId == movieId)
            movieShows.push_back(s);

    int cardX = 40, cardY = 120, cardW = 580, cardH = 90;
    for (int i = 0; i < (int)movieShows.size(); i++) {
        int x = cardX;
        int y = cardY + i * (cardH + 16);
        Rectangle card = { (float)x, (float)y, (float)cardW, (float)cardH };
        if (CheckCollisionPointRec(GetMousePosition(), card)
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            selectedShowId = movieShows[i].id;
            *state = BOOKING;
        }
    }
}