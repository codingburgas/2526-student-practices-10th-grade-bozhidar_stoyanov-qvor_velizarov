#pragma once
#include "utils.h"
#include "Button.h"
#include "..\Data\DataManager.h"
#include <string>
#include <vector>
using namespace std;

class MovieBookedSeat {
public:
    int movieId;
    int row;
    int col;

    MovieBookedSeat(int movieId, int row, int col) {
        this->movieId = movieId;
        this->row = row;
        this->col = col;
    }
};

class BookingScreen {
public:
    void Init(DataManager* db, int movieId);
    void Draw();
    void Update(gameStates* state);

private:
    DataManager* db;
    int movieId = -1;
    int frameCount = 0;

    vector<pair<int, int>> selectedSeats;
    vector<MovieBookedSeat> bookedSeats;

    float totalPrice = 0.0f;

    Button backBtn = Button(20, 20, 120, 45, "< Back", DARKGRAY);
    Button confirmBtn = Button(900, 600, 320, 50, "Confirm Booking", ORANGE);

    Cinema* GetCinema();
    Hall* GetHall();
    Color GetSeatColor(Seat& seat, bool selected);
    bool IsSeatSelected(int row, int col);
    bool IsSeatBooked(int row, int col);
    void RecalcTotal();
};