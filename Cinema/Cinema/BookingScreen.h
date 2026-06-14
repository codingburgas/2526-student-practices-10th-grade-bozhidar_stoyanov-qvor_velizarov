#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Data\DataManager.h"
#include <string>
#include <vector>
using namespace std;

class BookingScreen {
public:
    void Init(DataManager* db, int showId);
    void Draw();
    void Update(gameStates* state);

private:
    DataManager* db;
    int showId = -1;
    int frameCount = 0;

    vector<pair<int, int>> selectedSeats;
    float totalPrice = 0.0f;

    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);
    Button confirmBtn = Button(900, 600, 320, 50, "Confirm Booking", ORANGE);

    Show* GetShow();
    Cinema* GetCinema();
    Hall* GetHall();
    Color    GetSeatColor(Seat& seat, bool selected);
    bool     IsSeatSelected(int row, int col);
    void     RecalcTotal();
};