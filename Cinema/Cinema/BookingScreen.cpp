#include "BookingScreen.h"

void BookingScreen::Init(DataManager* db, int showId) {
    this->db = db;
    this->showId = showId;
    frameCount = 0;
    selectedSeats.clear();
    totalPrice = 0.0f;
}

Show* BookingScreen::GetShow() {
    for (auto& s : db->shows)
        if (s.id == showId) return &s;
    return nullptr;
}

Cinema* BookingScreen::GetCinema() {
    Show* show = GetShow();
    if (!show) return nullptr;
    for (auto& c : db->cinemas)
        if (c.id == show->cinemaId) return &c;
    return nullptr;
}

Hall* BookingScreen::GetHall() {
    Show* show = GetShow();
    Cinema* cinema = GetCinema();
    if (!show || !cinema) return nullptr;
    for (auto& h : cinema->halls)
        if (h.id == show->hallId) return &h;
    return nullptr;
}

bool BookingScreen::IsSeatSelected(int row, int col) {
    for (auto& s : selectedSeats)
        if (s.first == row && s.second == col) return true;
    return false;
}

void BookingScreen::RecalcTotal() {
    Hall* hall = GetHall();
    if (!hall) return;
    totalPrice = 0.0f;
    for (auto& s : selectedSeats)
        totalPrice += hall->seats[s.first][s.second].GetPrice();
}

Color BookingScreen::GetSeatColor(Seat& seat, bool selected) {
    if (seat.status == SeatStatus::BOOKED) return RED;
    if (selected)                          return ORANGE;
    if (seat.type == SeatType::STANDARD)   return Color{ 160,160,160,255 };
    if (seat.type == SeatType::VIP)        return Color{ 180,140,0,255 };
    if (seat.type == SeatType::PLATINUM)   return Color{ 100,0,180,255 };
    return GRAY;
}

void BookingScreen::Draw() {
    Show* show = GetShow();
    Hall* hall = GetHall();
    Cinema* cinema = GetCinema();
    if (!show || !hall || !cinema) return;

    DrawText("SELECT YOUR SEATS",
        GetScreenWidth() / 2 - MeasureText("SELECT YOUR SEATS", 36) / 2,
        20, 36, ORANGE);

    string info = cinema->name + "  |  " + show->date + "  |  " + show->time;
    DrawText(info.c_str(),
        GetScreenWidth() / 2 - MeasureText(info.c_str(), 20) / 2,
        65, 20, GRAY);

    DrawRectangleRounded({ 200, 100, 880, 12 }, 0.5f, 8, DARKGRAY);
    DrawText("SCREEN",
        GetScreenWidth() / 2 - MeasureText("SCREEN", 16) / 2,
        118, 16, GRAY);

    int startX = 160, startY = 150, seatW = 52, seatH = 46, gap = 8;

    for (int r = 0; r < ROWS; r++) {
        DrawText(TextFormat("%d", r + 1), startX - 30, startY + r * (seatH + gap) + 12, 20, GRAY);

        for (int c = 0; c < COLS; c++) {
            int x = startX + c * (seatW + gap);
            int y = startY + r * (seatH + gap);

            Seat& seat = hall->seats[r][c];
            bool selected = IsSeatSelected(r, c);
            Color color = GetSeatColor(seat, selected);

            Rectangle seatRect = { (float)x, (float)y, (float)seatW, (float)seatH };
            bool hovered = CheckCollisionPointRec(GetMousePosition(), seatRect)
                && seat.status != SeatStatus::BOOKED;

            DrawRectangleRounded(seatRect, 0.3f, 8,
                hovered && !selected
                ? Color{ (unsigned char)min(color.r + 40, 255),
                         (unsigned char)min(color.g + 40, 255),
                         (unsigned char)min(color.b + 40, 255), 255 }
            : color);

            if (r == 0)
                DrawText(TextFormat("%d", c + 1), x + 16, startY - 22, 16, GRAY);
        }
    }

    int lx = 160, ly = 480;
    DrawRectangleRounded({ (float)lx,       (float)ly,      30, 24 }, 0.3f, 8, Color{ 160,160,160,255 });
    DrawText("Standard - 8 lv", lx + 38, ly + 2, 18, LIGHTGRAY);
    DrawRectangleRounded({ (float)lx,       (float)ly + 32, 30, 24 }, 0.3f, 8, Color{ 180,140,0,255 });
    DrawText("VIP - 12 lv", lx + 38, ly + 34, 18, LIGHTGRAY);
    DrawRectangleRounded({ (float)lx,       (float)ly + 64, 30, 24 }, 0.3f, 8, Color{ 100,0,180,255 });
    DrawText("Platinum - 18 lv", lx + 38, ly + 66, 18, LIGHTGRAY);
    DrawRectangleRounded({ (float)lx + 220, (float)ly,      30, 24 }, 0.3f, 8, ORANGE);
    DrawText("Selected", lx + 258, ly + 2, 18, LIGHTGRAY);
    DrawRectangleRounded({ (float)lx + 220, (float)ly + 32, 30, 24 }, 0.3f, 8, RED);
    DrawText("Booked", lx + 258, ly + 34, 18, LIGHTGRAY);

    string total = "Total: " + to_string((int)totalPrice) + " lv";
    DrawText(total.c_str(), 900, 560, 28, ORANGE);

    if (!selectedSeats.empty()) confirmBtn.Draw();
    backBtn.Draw();
}

void BookingScreen::Update(gameStates* state) {
    frameCount++;
    if (frameCount < 10) return;

    if (backBtn.isClicked()) { *state = SHOWS; return; }

    Hall* hall = GetHall();
    if (!hall) return;

    int startX = 160, startY = 150, seatW = 52, seatH = 46, gap = 8;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Seat& seat = hall->seats[r][c];
            if (seat.status == SeatStatus::BOOKED) continue;

            Rectangle seatRect = {
                (float)(startX + c * (seatW + gap)),
                (float)(startY + r * (seatH + gap)),
                (float)seatW, (float)seatH
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
        for (auto& s : selectedSeats)
            hall->seats[s.first][s.second].status = SeatStatus::BOOKED;
        selectedSeats.clear();
        totalPrice = 0.0f;
        *state = MAIN_MENU;
    }
}