#include "BookingScreen.h"

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
    if (seat.type == SeatType::VIP)       return Color{ 180,140,0,255 };
    if (seat.type == SeatType::PLATINUM)  return Color{ 100,0,180,255 };
    return GRAY;
}

void BookingScreen::Draw() {
    Hall* hall = GetHall();
    Cinema* cinema = GetCinema();
    if (!hall || !cinema) return;

    DrawText("SELECT YOUR SEATS",
        GetScreenWidth() / 2 - MeasureText("SELECT YOUR SEATS", 36) / 2,
        20, 36, ORANGE);

    int seatW = 52;
    int seatH = 46;
    int gap = 8;

    int gridW = COLS * seatW + (COLS - 1) * gap;
    int startX = 60;  
    int startY = 180;

    DrawRectangleRounded({ (float)startX - 10, 100, 750, 12 }, 0.5f, 8, DARKGRAY);
    DrawText("SCREEN",
        startX + gridW / 2 - MeasureText("SCREEN", 16) / 2,
        118, 16, GRAY);

    for (int r = 0; r < ROWS; r++) {
        DrawText(TextFormat("%d", r + 1),
            startX - 30,
            startY + r * (seatH + gap) + 12,
            20,
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

            DrawRectangleRounded(seatRect, 0.3f, 8,
                hovered && !selected
                ? Color{ (unsigned char)min(color.r + 40, 255),
                         (unsigned char)min(color.g + 40, 255),
                         (unsigned char)min(color.b + 40, 255), 255 }
            : color);

            if (r == 0)
                DrawText(TextFormat("%d", c + 1),
                    x + 16,
                    startY - 22,
                    16,
                    GRAY);
        }
    }

    std::string total = "Total: " + std::to_string((int)totalPrice) + " lv";
    DrawText(total.c_str(),
        startX + gridW / 2 - MeasureText(total.c_str(), 28) / 2,
        startY + ROWS * (seatH + gap) + 20,
        28,
        ORANGE);

    int rightX = 820;
    int rightY = 150;
    int rightW = 360;
    int rightH = 520;

    DrawRectangleRounded({ (float)rightX - 15, (float)rightY - 15, (float)rightW + 30, (float)rightH + 30 }, 0.3f, 8,
        Color{ 30, 30, 30, 200 });
    DrawRectangleRoundedLines({ (float)rightX - 15, (float)rightY - 15, (float)rightW + 30, (float)rightH + 30 }, 0.3f, 8, ORANGE);

    std::string movieTitle = "Unknown";
    for (auto& m : db->movies) {
        if (m.id == movieId) {
            movieTitle = m.title;
            break;
        }
    }

    DrawText(movieTitle.c_str(),
        rightX + rightW / 2 - MeasureText(movieTitle.c_str(), 28) / 2,
        rightY, 28, ORANGE);

    DrawText("SEAT LEGEND",
        rightX + rightW / 2 - MeasureText("SEAT LEGEND", 28) / 2,
        rightY, 28, ORANGE);

    int legY = rightY + 50;
    int legItemH = 40;

    DrawRectangleRounded({ (float)rightX, (float)legY, 24, 24 }, 0.2f, 4, Color{ 160,160,160,255 });
    DrawText(cinemaId == 2 ? "Standard - 12 lv" : "Standard - 8 lv", rightX + 40, legY + 2, 22, LIGHTGRAY);

    DrawRectangleRounded({ (float)rightX, (float)legY + legItemH, 24, 24 }, 0.2f, 4, Color{ 180,140,0,255 });
    DrawText(cinemaId == 2 ? "VIP - 18 lv" : "VIP - 12 lv", rightX + 40, legY + legItemH + 2, 22, LIGHTGRAY);

    DrawRectangleRounded({ (float)rightX, (float)legY + legItemH * 2, 24, 24 }, 0.2f, 4, Color{ 100,0,180,255 });
    DrawText(cinemaId == 2 ? "Platinum - 25 lv" : "Platinum - 18 lv", rightX + 40, legY + legItemH * 2 + 2, 22, LIGHTGRAY);

    DrawRectangleRounded({ (float)rightX, (float)legY + legItemH * 3, 24, 24 }, 0.2f, 4, YELLOW);
    DrawText("Selected", rightX + 40, legY + legItemH * 3 + 2, 22, LIGHTGRAY);

    DrawRectangleRounded({ (float)rightX, (float)legY + legItemH * 4, 24, 24 }, 0.2f, 4, Color{ 0, 121, 241, 255 });
    DrawText("Your Reservation", rightX + 40, legY + legItemH * 4 + 2, 22, LIGHTGRAY);

    DrawRectangleRounded({ (float)rightX, (float)legY + legItemH * 5, 24, 24 }, 0.2f, 4, GREEN);
    DrawText("Booked", rightX + 40, legY + legItemH * 5 + 2, 22, LIGHTGRAY);

    DrawText("SELECT CINEMA",
        rightX + rightW / 2 - MeasureText("SELECT CINEMA", 24) / 2,
        legY + legItemH * 5 + 20, 24, ORANGE);

    cineGrandBtn.SetColor(cinemaId == 1 ? ORANGE : DARKGRAY);
    arenaBtn.SetColor(cinemaId == 2 ? ORANGE : DARKGRAY);
    cineGrandBtn.Draw();
    arenaBtn.Draw();

    if (!selectedSeats.empty()) confirmBtn.Draw();

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

    int seatW = 52;
    int seatH = 46;
    int gap = 8;

    int startX = 60;
    int startY = 180;

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