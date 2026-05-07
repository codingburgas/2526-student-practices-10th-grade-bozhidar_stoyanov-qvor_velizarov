#pragma once
#include <string>
#include "Movie.h"
#include "Hall.h"
using namespace std;

struct Show {
    int id;
    int movieId;
    int hallId;
    int cinemaId;
    string time;
    string date;
};