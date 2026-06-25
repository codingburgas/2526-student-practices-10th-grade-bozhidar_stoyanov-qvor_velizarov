#include "BookingScreen.h"
using namespace std;

void BookingScreen::Init(DataManager* db, int movieId, int cinemaId) {
    this->db = db;
    this->movieId = movieId;
    this->cinemaId = cinemaId;
    frameCount = 0;
    selectedSeats.clear();
    totalPrice = 0.0f;
}

Cinema* BookingScreen::GetCinema() {
    for (auto& c : db->cinemas) {
        if (c.id == cinemaId)
            return &c;
    }
    return nullptr;
}

Hall* BookingScreen::GetHall() {
    Cinema* cinema = GetCinema();
    if (!cinema || cinema->halls.empty()) return nullptr;
    return &cinema->halls[0];
}

bool BookingScreen::IsSeatSelected(int row, int col) {
    for (auto& s : selectedSeats)
        if (s.first == row && s.second == col) return true;
    return false;
}

bool BookingScreen::IsSeatBooked(int row, int col) {
    for (auto& s : bookedSeats) {
        if (s.movieId == movieId && s.cinemaId == cinemaId && s.row == row && s.col == col)
            return true;
    }
    return false;
}

void BookingScreen::RecalcTotal() {
    Hall* hall = GetHall();
    if (!hall) return;
    totalPrice = 0.0f;
    for (auto& s : selectedSeats)
        totalPrice += hall->seats[s.first][s.second].GetPrice(cinemaId);
}

bool BookingScreen::IsSeatBookedByUser(int row, int col) {
    for (auto& s : bookedSeats) {
        if (s.movieId == movieId && s.cinemaId == cinemaId && s.row == row && s.col == col) {
            return true;
        }
    }
    return false;
}

Color BookingScreen::GetSeatColor(Seat& seat, bool selected, bool bookedByUser) {
    if (bookedByUser)                     return Color{ 0, 121, 241, 255 };
    if (selected)                         return YELLOW;
    if (seat.type == SeatType::STANDARD)  return Color{ 160,160,160,255 };
    if (seat.type == SeatType::VIP)       return Color{ 220,160,0,255 };
    if (seat.type == SeatType::PLATINUM)  return Color{ 140,40,200,255 };
    return GRAY;
}

string GetMovieShowtime(int movieId) {
    switch(movieId) {
        case 1: return "18:00";
        case 2: return "20:30";
        case 3: return "16:45";
        case 4: return "21:00";
        case 5: return "19:15";
        default: return "19:30";
    }
}

string GetMovieDate(int movieId) {
    switch(movieId) {
        case 1: return "20 Nov 2024";
        case 2: return "22 Nov 2024";
        case 3: return "24 Nov 2024";
        case 4: return "25 Nov 2024";
        case 5: return "26 Nov 2024";
        default: return "22 Nov 2024";
    }
}
                        
void BookingScreen::Draw() {
    Hall* hall = GetHall();
    Cinema* cinema = GetCinema();
    if (!hall || !cinema) return;

    DrawText("SELECT YOUR SEATS",
        GetScreenWidth() / 2 - MeasureText("SELECT YOUR SEATS", 40) / 2,
        30, 40, ORANGE);

    int seatW = 48;
    int seatH = 42;
    int gap = 6;

    int gridW = COLS * seatW + (COLS - 1) * gap;
    int startX = 100;  
    int startY = 190;

    DrawRectangleRounded({ (float)startX - 10, 125, (float)gridW + 20, 30 }, 0.4f, 8, DARKGRAY);
    DrawText("SCREEN",
        startX + gridW / 2 - MeasureText("SCREEN", 16) / 2,
        133, 16, GRAY);

    for (int r = 0; r < ROWS; r++) {
        DrawText(TextFormat("%d", r + 1),
            startX - 35,
            startY + r * (seatH + gap) + 8,
            18,
            GRAY);

        for (int c = 0; c < COLS; c++) {
            int x = startX + c * (seatW + gap);
            int y = startY + r * (seatH + gap);

            Seat& seat = hall->seats[r][c];

            bool selected = IsSeatSelected(r, c);
            bool booked = IsSeatBooked(r, c);
            bool bookedByUser = IsSeatBookedByUser(r, c);

            Color color;
            if (bookedByUser)              color = Color{ 0, 121, 241, 255 };
            else if (booked)               color = GREEN;
            else if (selected)             color = YELLOW;
            else                           color = GetSeatColor(seat, false, false);

            Rectangle seatRect = { (float)x, (float)y, (float)seatW, (float)seatH };

            bool hovered = CheckCollisionPointRec(GetMousePosition(), seatRect)
                && !booked;

            DrawRectangleRounded(seatRect, 0.2f, 4,
                hovered && !selected && !booked
                ? Color{ (unsigned char)min(color.r + 40, 255),
                         (unsigned char)min(color.g + 40, 255),
                         (unsigned char)min(color.b + 40, 255), 255 }
            : color);

            if (r == 0)                     DrawText(TextFormat("%d", c + 1),
                    x + 14,
                    startY - 28,
                    14,
                    GRAY);
        }
    }

    int panelX = 720;
    int panelY = 125;
    int panelW = 360;
    int panelH = 530;

    DrawRectangleRounded({ (float)panelX - 10, (float)panelY - 10, (float)panelW + 20, (float)panelH + 20 }, 
        0.2f, 8, Color{ 30, 30, 30, 220 });
    DrawRectangleRoundedLines({ (float)panelX - 10, (float)panelY - 10, (float)panelW + 20, (float)panelH + 20 }, 
        0.2f, 8, ORANGE);

    DrawText("YOUR SELECTION",
        panelX + panelW / 2 - MeasureText("YOUR SELECTION", 20) / 2,
        panelY + 15, 20, ORANGE);

    int infoY = panelY + 55;
    int lineH = 48;

    string movieTitle = "Unknown";
    for (auto& m : db->movies) {
        if (m.id == movieId) {
            movieTitle = m.title;
            break;
        }
    }

    DrawText("MOVIE", panelX + 20, infoY, 14, ORANGE);
    DrawText(movieTitle.c_str(), panelX + 170, infoY + 2, 14, LIGHTGRAY);

    DrawText("DATE", panelX + 20, infoY + lineH, 14, ORANGE);
    string movieDate = GetMovieDate(movieId);
    DrawText(movieDate.c_str(), panelX + 170, infoY + lineH + 2, 14, LIGHTGRAY);

    DrawText("TIME", panelX + 20, infoY + lineH * 2, 14, ORANGE);
    DrawText("19:30", panelX + 170, infoY + lineH * 2 + 2, 14, LIGHTGRAY);

    DrawText("SEATS", panelX + 20, infoY + lineH * 3, 14, ORANGE);
    string seatsText = selectedSeats.empty() ? "None selected" : to_string(selectedSeats.size()) + " selected";
    DrawText(seatsText.c_str(), panelX + 170, infoY + lineH * 3 + 2, 14, LIGHTGRAY);

    DrawText("TOTAL", panelX + 20, infoY + lineH * 4, 14, ORANGE);
    string totalStr = to_string((int)totalPrice) + " lv";
    DrawText(totalStr.c_str(),
        panelX + 165,
        infoY + lineH * 4 + 2, 14, LIGHTGRAY);

    DrawLineEx(Vector2{ (float)panelX + 15, (float)infoY + lineH * 4 + 28 }, 
        Vector2{ (float)panelX + panelW - 15, (float)infoY + lineH * 4 + 28 }, 
        1.0f, Color{ 80, 80, 80, 100 });

    int legY = infoY + lineH * 4 + 48;  
    int legBoxSize = 14;
    int legBoxX = panelX + 20;
    int legTextX = legBoxX + 26;
    int legSpacing = 24;
    int colWidth = 170;

    DrawRectangleRounded({ (float)legBoxX, (float)legY, (float)legBoxSize, (float)legBoxSize }, 0.1f, 2, Color{ 160,160,160,255 });
    DrawText("Standard", legTextX, legY - 2, 12, LIGHTGRAY);
    string standardPrice = to_string((int)Seat().GetPrice(cinemaId)) + " lv";
    DrawText(standardPrice.c_str(), panelX + 105, legY - 2, 12, ORANGE);

    DrawRectangleRounded({ (float)(legBoxX + colWidth), (float)legY, (float)legBoxSize, (float)legBoxSize }, 0.1f, 2, YELLOW);
    DrawText("Selected", legTextX + colWidth, legY - 2, 12, ORANGE);

    DrawRectangleRounded({ (float)legBoxX, (float)legY + legSpacing, (float)legBoxSize, (float)legBoxSize }, 0.1f, 2, Color{ 220,160,0,255 });
    DrawText("VIP", legTextX, legY + legSpacing - 2, 12, LIGHTGRAY);
    Seat vipSeat;
    vipSeat.type = SeatType::VIP;
    string vipPrice = to_string((int)vipSeat.GetPrice(cinemaId)) + " lv";
    DrawText(vipPrice.c_str(), panelX + 105, legY + legSpacing - 2, 12, ORANGE);

    DrawRectangleRounded({ (float)(legBoxX + colWidth), (float)legY + legSpacing, (float)legBoxSize, (float)legBoxSize }, 0.1f, 2, Color{ 0, 121, 241, 255 });
    DrawText("Your Reservation", legTextX + colWidth, legY + legSpacing - 2, 12, LIGHTGRAY);

    DrawRectangleRounded({ (float)legBoxX, (float)legY + legSpacing * 2, (float)legBoxSize, (float)legBoxSize }, 0.1f, 2, Color{ 140,40,200,255 });
    DrawText("Platinum", legTextX, legY + legSpacing * 2 - 2, 12, LIGHTGRAY);
    Seat platinumSeat;
    platinumSeat.type = SeatType::PLATINUM;
    string platinumPrice = to_string((int)platinumSeat.GetPrice(cinemaId)) + " lv";
    DrawText(platinumPrice.c_str(), panelX + 105, legY + legSpacing * 2 - 2, 12, ORANGE);

    DrawRectangleRounded({ (float)(legBoxX + colWidth), (float)legY + legSpacing * 2, (float)legBoxSize, (float)legBoxSize }, 0.1f, 2, GREEN);
    DrawText("Booked", legTextX + colWidth, legY + legSpacing * 2 - 2, 12, LIGHTGRAY);

    DrawText("SELECT CINEMA",
        panelX + panelW / 2 - MeasureText("SELECT CINEMA", 13) / 2,
        legY + legSpacing * 3 + 12, 13, ORANGE);

    cineGrandBtn = Button(panelX + 20, legY + legSpacing * 3 + 35, 160, 35, "CineGrand", DARKGRAY);
    arenaBtn = Button(panelX + 190, legY + legSpacing * 3 + 35, 160, 35, "NovaCine", DARKGRAY);

    cineGrandBtn.SetColor(cinemaId == 1 ? ORANGE : DARKGRAY);
    arenaBtn.SetColor(cinemaId == 2 ? ORANGE : DARKGRAY);
    cineGrandBtn.Draw();
    arenaBtn.Draw();

    confirmBtn = Button(panelX + 20, panelY + panelH - 55, panelW - 40, 45, "Confirm Booking", ORANGE);
    if (!selectedSeats.empty()) confirmBtn.Draw();

    string bottomTotal = "TOTAL: " + to_string((int)totalPrice) + " lv";
    DrawText(bottomTotal.c_str(),
        startX + gridW / 2 - MeasureText(bottomTotal.c_str(), 20) / 2,
        startY + ROWS * (seatH + gap) + 40,
        20,
        ORANGE);

    DrawText("Click on a seat to select it.",
        50, GetScreenHeight() - 35, 12, GRAY);
    DrawText("Selected seats will be held for 5 minutes.",
        GetScreenWidth() - 380, GetScreenHeight() - 35, 12, GRAY);

    backBtn.Draw();
}

void BookingScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (backBtn.isClicked()) { *state = MOVIES; return; }

    if (cineGrandBtn.isClicked()) {
        if (cinemaId != 1) {
            cinemaId = 1;
            selectedSeats.clear();
            RecalcTotal();
        }
    }
    if (arenaBtn.isClicked()) {
        if (cinemaId != 2) {
            cinemaId = 2;
            selectedSeats.clear();
            RecalcTotal();
        }
    }

    Hall* hall = GetHall();
    if (!hall) return;

    int seatW = 48;
    int seatH = 42;
    int gap = 6;

    int startX = 100;
    int startY = 190;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Seat& seat = hall->seats[r][c];

            if (IsSeatBooked(r, c)) continue;

            Rectangle seatRect = {
                (float)(startX + c * (seatW + gap)),
                (float)(startY + r * (seatH + gap)),
                (float)seatW,
                (float)seatH
            };

            if (CheckCollisionPointRec(GetMousePosition(), seatRect)
                && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (IsSeatSelected(r, c)) {
                    for (int i = 0; i < (int)selectedSeats.size(); i++)
                        if (selectedSeats[i].first == r && selectedSeats[i].second == c)
                            selectedSeats.erase(selectedSeats.begin() + i);
                }
                else {
                    selectedSeats.push_back({ r, c });
                }

                RecalcTotal();
            }
        }
    }

    if (!selectedSeats.empty() && confirmBtn.isClicked()) {
        for (auto& s : selectedSeats) {
            bookedSeats.push_back(MovieBookedSeat(movieId, cinemaId, s.first, s.second));
        }

        selectedSeats.clear();
        totalPrice = 0.0f;
        *state = COMPLETED;
    }
}