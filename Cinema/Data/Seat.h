#pragma once

enum class SeatType {
    STANDARD,
    VIP,
    PLATINUM
};

enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

class Seat {
public:
    int row;
    int col;
    SeatType type;
    SeatStatus status;

    Seat() {
        row = 0;
        col = 0;
        type = SeatType::STANDARD;
        status = SeatStatus::AVAILABLE;
    }

    float GetPrice(int cinemaId = 1) const {
        if (cinemaId == 2) {
            if (type == SeatType::STANDARD)  return 12.0f;
            if (type == SeatType::VIP)       return 18.0f;
            if (type == SeatType::PLATINUM)  return 25.0f;
        }
        if (type == SeatType::STANDARD)  return 8.0f;
        if (type == SeatType::VIP)       return 12.0f;
        if (type == SeatType::PLATINUM)  return 18.0f;
        return 0.0f;
    }
};