#pragma once

enum class SeatType {
    SILVER,
    GOLD,
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
        type = SeatType::SILVER;
        status = SeatStatus::AVAILABLE;
    }

    float GetPrice() const {
        if (type == SeatType::SILVER)   return 8.0f;
        if (type == SeatType::GOLD)     return 12.0f;
        if (type == SeatType::PLATINUM) return 18.0f;
        return 0.0f;
    }
};