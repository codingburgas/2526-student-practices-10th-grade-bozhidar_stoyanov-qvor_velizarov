#include "AdminScreen.h"

void AdminScreen::Init(DataManager* db) {
    this->db = db;
    adminState = AdminState::MAIN;
    frameCount = 0;
    selectedId = -1;
}

void AdminScreen::HandleTextInput(char* buf, int maxLen, int fieldId) {
    if (activeField != fieldId) return;
    int key = GetCharPressed();
    while (key > 0) {
        int len = strlen(buf);
        if (key >= 32 && key <= 125 && len < maxLen - 1) {
            buf[len] = (char)key;
            buf[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(buf);
        if (len > 0) buf[len - 1] = '\0';
    }
}

void AdminScreen::DrawMain() {
    DrawText("ADMIN PANEL",
        GetScreenWidth() / 2 - MeasureText("ADMIN PANEL", 40) / 2,
        100, 40, ORANGE);

    addMovieBtn.Draw();
    deleteMovieBtn.Draw();
    addShowBtn.Draw();
    deleteShowBtn.Draw();
    updateShowBtn.Draw();
    backBtn.Draw();
}

void AdminScreen::DrawDeleteMovie() {
    DrawText("DELETE MOVIE",
        GetScreenWidth() / 2 - MeasureText("DELETE MOVIE", 36) / 2,
        20, 36, ORANGE);

    int y = 100;
    for (auto& m : db->movies) {
        Rectangle card = { 300, (float)y, 680, 50 };
        bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
        DrawRectangleRounded(card, 0.2f, 8, hovered ? Color{ 100,0,0,255 } : Color{ 30,30,30,255 });
        DrawRectangleRoundedLines(card, 0.2f, 8, hovered ? RED : DARKGRAY);
        DrawText(m.title.c_str(), 320, y + 14, 22, WHITE);
        DrawText("Click to delete", 820, y + 14, 18, RED);
        y += 66;
    }

    cancelBtn.Draw();
}

void AdminScreen::DrawAddMovie() {
    DrawText("ADD MOVIE",
        GetScreenWidth() / 2 - MeasureText("ADD MOVIE", 36) / 2,
        20, 36, ORANGE);

    DrawText("Title:", 200, 120, 22, WHITE);
    Rectangle titleBox = { 360, 112, 480, 36 };
    DrawRectangleRounded(titleBox, 0.3f, 8, activeField == 0 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(titleBox, 0.3f, 8, activeField == 0 ? ORANGE : GRAY);
    DrawText(titleBuf, 368, 120, 20, WHITE);

    DrawText("Release Date:", 200, 170, 22, WHITE);
    Rectangle dateBox = { 390, 162, 200, 36 };
    DrawRectangleRounded(dateBox, 0.3f, 8, activeField == 1 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(dateBox, 0.3f, 8, activeField == 1 ? ORANGE : GRAY);
    DrawText(dateBuf, 398, 170, 20, WHITE);
    DrawText("DD-MM-YYYY", 600, 170, 18, GRAY);

    DrawText("Description:", 200, 220, 22, WHITE);
    Rectangle descBox = { 360, 212, 480, 36 };
    DrawRectangleRounded(descBox, 0.3f, 8, activeField == 2 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(descBox, 0.3f, 8, activeField == 2 ? ORANGE : GRAY);
    DrawText(descBuf, 368, 220, 20, WHITE);

    DrawText("Genre:", 200, 280, 22, WHITE);
    const char* genres[] = { "Action", "Comedy", "Drama", "Horror", "Sci-Fi" };
    for (int i = 0; i < 5; i++) {
        Rectangle r = { (float)(360 + i * 110), 272, 100, 36 };
        bool selected = (int)selGenre == i;
        DrawRectangleRounded(r, 0.3f, 8, selected ? ORANGE : DARKGRAY);
        DrawText(genres[i], (int)(370 + i * 110), 280, 18, WHITE);
    }

    DrawText("Language:", 200, 330, 22, WHITE);
    Rectangle engBox = { 360, 322, 120, 36 };
    Rectangle bulBox = { 490, 322, 120, 36 };
    DrawRectangleRounded(engBox, 0.3f, 8, selLang == Language::ENGLISH ? ORANGE : DARKGRAY);
    DrawRectangleRounded(bulBox, 0.3f, 8, selLang == Language::BULGARIAN ? ORANGE : DARKGRAY);
    DrawText("English", 368, 330, 18, WHITE);
    DrawText("Bulgarian", 498, 330, 18, WHITE);

    confirmAddMovie.Draw();
    cancelBtn.Draw();
}

void AdminScreen::DrawAddShow() {
    DrawText("ADD SHOW",
        GetScreenWidth() / 2 - MeasureText("ADD SHOW", 36) / 2,
        20, 36, ORANGE);

    DrawText("Movie:", 200, 120, 22, WHITE);
    int mx = 360, my = 112;
    for (auto& m : db->movies) {
        Rectangle r = { (float)mx, (float)my, 480, 36 };
        bool selected = selMovieId == m.id;
        DrawRectangleRounded(r, 0.2f, 8, selected ? ORANGE : DARKGRAY);
        DrawText(m.title.c_str(), mx + 10, my + 8, 18, WHITE);
        my += 46;
    }

    DrawText("Cinema:", 200, 380, 22, WHITE);
    int cx = 360, cy = 372;
    for (auto& c : db->cinemas) {
        Rectangle r = { (float)cx, (float)cy, 220, 36 };
        bool selected = selCinemaId == c.id;
        DrawRectangleRounded(r, 0.2f, 8, selected ? ORANGE : DARKGRAY);
        DrawText(c.name.c_str(), cx + 10, cy + 8, 18, WHITE);
        cx += 230;
    }

    DrawText("Date:", 200, 430, 22, WHITE);
    Rectangle dateBox = { 360, 422, 200, 36 };
    DrawRectangleRounded(dateBox, 0.3f, 8, activeShowField == 0 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(dateBox, 0.3f, 8, activeShowField == 0 ? ORANGE : GRAY);
    DrawText(showDateBuf, 368, 430, 20, WHITE);
    DrawText("DD-MM-YYYY", 570, 430, 18, GRAY);

    DrawText("Time:", 200, 480, 22, WHITE);
    Rectangle timeBox = { 360, 472, 120, 36 };
    DrawRectangleRounded(timeBox, 0.3f, 8, activeShowField == 1 ? DARKGRAY : Color{ 40,40,40,255 });
    DrawRectangleRoundedLines(timeBox, 0.3f, 8, activeShowField == 1 ? ORANGE : GRAY);
    DrawText(showTimeBuf, 368, 480, 20, WHITE);
    DrawText("HH:MM", 490, 480, 18, GRAY);

    confirmAddShow.Draw();
    cancelBtn.Draw();
}

void AdminScreen::DrawDeleteShow() {
    DrawText("DELETE SHOW",
        GetScreenWidth() / 2 - MeasureText("DELETE SHOW", 36) / 2,
        20, 36, ORANGE);

    int y = 100;
    for (auto& s : db->shows) {
        string movieName = "Unknown";
        for (auto& m : db->movies)
            if (m.id == s.movieId) movieName = m.title;

        string cinemaName = "Unknown";
        for (auto& c : db->cinemas)
            if (c.id == s.cinemaId) cinemaName = c.name;

        Rectangle card = { 200, (float)y, 880, 50 };
        bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
        DrawRectangleRounded(card, 0.2f, 8, hovered ? Color{ 100,0,0,255 } : Color{ 30,30,30,255 });
        DrawRectangleRoundedLines(card, 0.2f, 8, hovered ? RED : DARKGRAY);

        string info = movieName + "  |  " + cinemaName + "  |  " + s.date + "  " + s.time;
        DrawText(info.c_str(), 220, y + 14, 18, WHITE);
        DrawText("Click to delete", 940, y + 14, 18, RED);
        y += 66;
    }

    cancelBtn.Draw();
}

void AdminScreen::Draw() {
    if (adminState == AdminState::MAIN)         DrawMain();
    if (adminState == AdminState::ADD_MOVIE)    DrawAddMovie();
    if (adminState == AdminState::DELETE_MOVIE) DrawDeleteMovie();
    if (adminState == AdminState::ADD_SHOW)     DrawAddShow();
    if (adminState == AdminState::DELETE_SHOW)  DrawDeleteShow();
}

void AdminScreen::UpdateMain(gameStates* state) {
    if (backBtn.isClicked()) { *state = MAIN_MENU; return; }
    if (addMovieBtn.isClicked()) { adminState = AdminState::ADD_MOVIE;    frameCount = 0; return; }
    if (deleteMovieBtn.isClicked()) { adminState = AdminState::DELETE_MOVIE; frameCount = 0; return; }
    if (addShowBtn.isClicked()) { adminState = AdminState::ADD_SHOW;     frameCount = 0; return; }
    if (deleteShowBtn.isClicked()) { adminState = AdminState::DELETE_SHOW;  frameCount = 0; return; }
}

void AdminScreen::UpdateAddMovie() {
    if (cancelBtn.isClicked()) { adminState = AdminState::MAIN; return; }

    Rectangle titleBox = { 360, 112, 480, 36 };
    Rectangle dateBox = { 390, 162, 200, 36 };
    Rectangle descBox = { 360, 212, 480, 36 };
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), titleBox)) activeField = 0;
        else if (CheckCollisionPointRec(GetMousePosition(), dateBox))  activeField = 1;
        else if (CheckCollisionPointRec(GetMousePosition(), descBox))  activeField = 2;
        else activeField = -1;
    }

    HandleTextInput(titleBuf, 64, 0);
    HandleTextInput(dateBuf, 12, 1);
    HandleTextInput(descBuf, 128, 2);

    for (int i = 0; i < 5; i++) {
        Rectangle r = { (float)(360 + i * 110), 272, 100, 36 };
        if (CheckCollisionPointRec(GetMousePosition(), r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            selGenre = (Genre)i;
    }

    Rectangle engBox = { 360, 322, 120, 36 };
    Rectangle bulBox = { 490, 322, 120, 36 };
    if (CheckCollisionPointRec(GetMousePosition(), engBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        selLang = Language::ENGLISH;
    if (CheckCollisionPointRec(GetMousePosition(), bulBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        selLang = Language::BULGARIAN;

    if (confirmAddMovie.isClicked() && strlen(titleBuf) > 0) {
        int newId = db->movies.empty() ? 1 : db->movies.back().id + 1;
        db->movies.push_back(Movie(newId, titleBuf, selGenre, selLang, dateBuf, descBuf));
        memset(titleBuf, 0, sizeof(titleBuf));
        memset(dateBuf, 0, sizeof(dateBuf));
        memset(descBuf, 0, sizeof(descBuf));
        adminState = AdminState::MAIN;
    }
}

void AdminScreen::UpdateDeleteMovie() {
    if (cancelBtn.isClicked()) { adminState = AdminState::MAIN; return; }

    int y = 100;
    for (int i = 0; i < (int)db->movies.size(); i++) {
        Rectangle card = { 300, (float)y, 680, 50 };
        if (CheckCollisionPointRec(GetMousePosition(), card)
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            db->movies.erase(db->movies.begin() + i);
            return;
        }
        y += 66;
    }
}

void AdminScreen::UpdateAddShow() {
    if (cancelBtn.isClicked()) { adminState = AdminState::MAIN; return; }

    int my = 112;
    for (auto& m : db->movies) {
        Rectangle r = { 360, (float)my, 480, 36 };
        if (CheckCollisionPointRec(GetMousePosition(), r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            selMovieId = m.id;
        my += 46;
    }

    int cx = 360;
    for (auto& c : db->cinemas) {
        Rectangle r = { (float)cx, 372, 220, 36 };
        if (CheckCollisionPointRec(GetMousePosition(), r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            selCinemaId = c.id;
        cx += 230;
    }

    Rectangle dateBox = { 360, 422, 200, 36 };
    Rectangle timeBox = { 360, 472, 120, 36 };
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), dateBox)) activeShowField = 0;
        else if (CheckCollisionPointRec(GetMousePosition(), timeBox)) activeShowField = 1;
        else activeShowField = -1;
    }

    HandleTextInput(showDateBuf, 12, 0);
    HandleTextInput(showTimeBuf, 8, 1);

    if (confirmAddShow.isClicked() && strlen(showDateBuf) > 0 && strlen(showTimeBuf) > 0) {
        int newId = db->shows.empty() ? 1 : db->shows.back().id + 1;
        db->shows.push_back(Show(newId, selMovieId, selHallId, selCinemaId, showTimeBuf, showDateBuf));
        memset(showDateBuf, 0, sizeof(showDateBuf));
        memset(showTimeBuf, 0, sizeof(showTimeBuf));
        adminState = AdminState::MAIN;
    }
}

void AdminScreen::UpdateDeleteShow() {
    if (cancelBtn.isClicked()) { adminState = AdminState::MAIN; return; }

    int y = 100;
    for (int i = 0; i < (int)db->shows.size(); i++) {
        Rectangle card = { 200, (float)y, 880, 50 };
        if (CheckCollisionPointRec(GetMousePosition(), card)
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            db->shows.erase(db->shows.begin() + i);
            return;
        }
        y += 66;
    }
}

void AdminScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (adminState == AdminState::MAIN)         UpdateMain(state);
    if (adminState == AdminState::ADD_MOVIE)    UpdateAddMovie();
    if (adminState == AdminState::DELETE_MOVIE) UpdateDeleteMovie();
    if (adminState == AdminState::ADD_SHOW)     UpdateAddShow();
    if (adminState == AdminState::DELETE_SHOW)  UpdateDeleteShow();
}