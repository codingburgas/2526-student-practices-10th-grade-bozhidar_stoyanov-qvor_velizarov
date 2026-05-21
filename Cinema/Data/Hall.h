#pragma once
#include <string>
#include "Seat.h"
using namespace std;

#define ROWS 6
#define COLS 10

class Hall {
public:
    int id;
    string name;
    Seat seats[ROWS][COLS];

    Hall() {
        id = 0;
    }

    void Init() {
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                seats[r][c].row = r;
                seats[r][c].col = c;
                seats[r][c].status = SeatStatus::AVAILABLE;

                if (r < 2)      seats[r][c].type = SeatType::SILVER;
                else if (r < 4) seats[r][c].type = SeatType::GOLD;
                else            seats[r][c].type = SeatType::PLATINUM;
            }
        }
    }
};