#include "AdminScreen.h"
#include <fstream>
#include <sstream>
using namespace std;

void AdminScreen::Init(DataManager* db) {
    this->db = db;
    adminState = AdminState::MAIN;
    frameCount = 0;
    selectedId = -1;
    selGenre = Genre::ACTION;
    selLang = Language::ENGLISH;
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

void AdminScreen::SaveMoviesToFile() {
    ofstream file("../Resources/movies.txt");
    if (!file.is_open()) {
        file.open("movies.txt");
        if (!file.is_open()) return;
    }
    
    for (auto& m : db->movies) {
        file << m.id << "|"
             << m.title << "|"
             << (int)m.genre << "|"
             << (int)m.language << "|"
             << m.releaseDate << "|"
             << m.description << "|"
             << m.imagePath << "\n";
    }
    file.close();
}

void AdminScreen::DrawMain() {
    DrawText("ADMIN PANEL",
        GetScreenWidth() / 2 - MeasureText("ADMIN PANEL", 40) / 2,
        100, 40, ORANGE);

    addMovieBtn.Draw();
    deleteMovieBtn.Draw();
    backBtn.Draw();
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
        DrawRectangleRoundedLines(r, 0.3f, 8, selected ? ORANGE : GRAY);
        DrawText(genres[i], (int)(370 + i * 110), 280, 18, WHITE);
    }

    DrawText("Language:", 200, 330, 22, WHITE);
    Rectangle engBox = { 360, 322, 120, 36 };
    Rectangle bulBox = { 490, 322, 120, 36 };
    DrawRectangleRounded(engBox, 0.3f, 8, selLang == Language::ENGLISH ? ORANGE : DARKGRAY);
    DrawRectangleRoundedLines(engBox, 0.3f, 8, selLang == Language::ENGLISH ? ORANGE : GRAY);
    DrawRectangleRounded(bulBox, 0.3f, 8, selLang == Language::BULGARIAN ? ORANGE : DARKGRAY);
    DrawRectangleRoundedLines(bulBox, 0.3f, 8, selLang == Language::BULGARIAN ? ORANGE : GRAY);
    DrawText("English", 368, 330, 18, WHITE);
    DrawText("Bulgarian", 498, 330, 18, WHITE);

    confirmAddMovie.Draw();
    cancelBtn.Draw();
}

void AdminScreen::DrawDeleteMovie() {
    DrawText("DELETE MOVIE",
        GetScreenWidth() / 2 - MeasureText("DELETE MOVIE", 36) / 2,
        20, 36, ORANGE);

    if (db->movies.empty()) {
        DrawText("No movies to delete", GetScreenWidth() / 2 - MeasureText("No movies to delete", 24) / 2,
            GetScreenHeight() / 2, 24, GRAY);
    } else {
        int cardW = 420;
        int cardH = 80;
        int cardSpacingX = 50;
        int cardSpacingY = 20;
        int startX = 40;
        int startY = 100;
        int cols = 2;

        for (int i = 0; i < (int)db->movies.size(); i++) {
            int col = i % cols;
            int row = i / cols;
            int x = startX + col * (cardW + cardSpacingX);
            int y = startY + row * (cardH + cardSpacingY);

            Rectangle card = { (float)x, (float)y, (float)cardW, (float)cardH };
            bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
            
            DrawRectangleRounded(card, 0.2f, 8, hovered ? Color{ 100, 0, 0, 255 } : Color{ 30, 30, 30, 255 });
            DrawRectangleRoundedLines(card, 0.2f, 8, hovered ? RED : DARKGRAY);
            
            DrawText(db->movies[i].title.c_str(), x + 15, y + 15, 20, WHITE);
            DrawText(db->movies[i].releaseDate.c_str(), x + 15, y + 45, 16, LIGHTGRAY);
            DrawText("Click to delete", x + 280, y + 30, 16, RED);
        }
    }

    cancelBtn.Draw();
}

void AdminScreen::UpdateMain(gameStates* state) {
    if (backBtn.isClicked()) { *state = MAIN_MENU; return; }
    if (addMovieBtn.isClicked()) { 
        adminState = AdminState::ADD_MOVIE;
        frameCount = 0;
        memset(titleBuf, 0, sizeof(titleBuf));
        memset(dateBuf, 0, sizeof(dateBuf));
        memset(descBuf, 0, sizeof(descBuf));
        activeField = -1;
        selGenre = Genre::ACTION;
        selLang = Language::ENGLISH;
        return; 
    }
    if (deleteMovieBtn.isClicked()) { 
        adminState = AdminState::DELETE_MOVIE; 
        frameCount = 0;
        return; 
    }
}

void AdminScreen::UpdateAddMovie() {
    if (cancelBtn.isClicked()) { 
        adminState = AdminState::MAIN;
        memset(titleBuf, 0, sizeof(titleBuf));
        memset(dateBuf, 0, sizeof(dateBuf));
        memset(descBuf, 0, sizeof(descBuf));
        activeField = -1;
        return; 
    }

    Rectangle titleBox = { 360, 112, 480, 36 };
    Rectangle dateBox = { 390, 162, 200, 36 };
    Rectangle descBox = { 360, 212, 480, 36 };
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), titleBox)) activeField = 0;
        else if (CheckCollisionPointRec(GetMousePosition(), dateBox)) activeField = 1;
        else if (CheckCollisionPointRec(GetMousePosition(), descBox)) activeField = 2;
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
        db->movies.push_back(Movie(newId, titleBuf, selGenre, selLang, dateBuf, descBuf, ""));
        
        SaveMoviesToFile();
        
        memset(titleBuf, 0, sizeof(titleBuf));
        memset(dateBuf, 0, sizeof(dateBuf));
        memset(descBuf, 0, sizeof(descBuf));
        activeField = -1;
        selGenre = Genre::ACTION;
        selLang = Language::ENGLISH;
        
        adminState = AdminState::MAIN;
    }
}

void AdminScreen::UpdateDeleteMovie() {
    if (cancelBtn.isClicked()) { 
        adminState = AdminState::MAIN; 
        return; 
    }

    int cardW = 420;
    int cardH = 80;
    int cardSpacingX = 50;
    int cardSpacingY = 20;
    int startX = 40;
    int startY = 100;
    int cols = 2;

    for (int i = 0; i < (int)db->movies.size(); i++) {
        int col = i % cols;
        int row = i / cols;
        int x = startX + col * (cardW + cardSpacingX);
        int y = startY + row * (cardH + cardSpacingY);

        Rectangle card = { (float)x, (float)y, (float)cardW, (float)cardH };
        if (CheckCollisionPointRec(GetMousePosition(), card)
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            db->movies.erase(db->movies.begin() + i);
            SaveMoviesToFile();
            adminState = AdminState::MAIN;
            return;
        }
    }
}

void AdminScreen::Draw() {
    if (adminState == AdminState::MAIN)         DrawMain();
    if (adminState == AdminState::ADD_MOVIE)    DrawAddMovie();
    if (adminState == AdminState::DELETE_MOVIE) DrawDeleteMovie();
}

void AdminScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (adminState == AdminState::MAIN)         UpdateMain(state);
    if (adminState == AdminState::ADD_MOVIE)    UpdateAddMovie();
    if (adminState == AdminState::DELETE_MOVIE) UpdateDeleteMovie();
}