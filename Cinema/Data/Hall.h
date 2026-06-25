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

    // Accepts a layout type for custom arrangement
    void Init(int layoutType = 0) {
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                seats[r][c].row = r;
                seats[r][c].col = c;
                seats[r][c].status = SeatStatus::AVAILABLE;

                if (layoutType == 0) {
                    // Default layout
                    if (r < 2)      seats[r][c].type = SeatType::STANDARD;
                    else if (r < 4) seats[r][c].type = SeatType::VIP;
                    else            seats[r][c].type = SeatType::PLATINUM;
                } else if (layoutType == 1) {
                    // Premium layout: more VIP/Platinum, fewer standard
                    if (r == 0)         seats[r][c].type = SeatType::STANDARD;
                    else if (r < 3)     seats[r][c].type = SeatType::VIP;
                    else                seats[r][c].type = SeatType::PLATINUM;
                }
            }
        }
    }
};