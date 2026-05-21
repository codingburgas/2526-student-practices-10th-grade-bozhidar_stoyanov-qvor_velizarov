#pragma once
#include <string>
#include "Movie.h"
#include "Hall.h"
using namespace std;

class Show {
public:
    int id;
    int movieId;
    int hallId;
    int cinemaId;
    string time;
    string date;

    Show() {}
    Show(int id, int movieId, int hallId, int cinemaId,
        string time, string date) {
        this->id = id;
        this->movieId = movieId;
        this->hallId = hallId;
        this->cinemaId = cinemaId;
        this->time = time;
        this->date = date;
    }
};