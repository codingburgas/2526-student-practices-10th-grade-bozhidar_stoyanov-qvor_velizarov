#pragma once
#include <vector>
#include "Movie.h"
#include "Cinema.h"
#include "..\Logic\FileManager.h"
using namespace std;

class DataManager {
public:
    vector<Movie>  movies;
    vector<Cinema> cinemas;

    void Init() {
        movies = FileManager::LoadMovies();

        Cinema c1(1, "CineGrand", "Sofia");
        Hall h1; h1.id = 1; h1.name = "Hall A"; h1.Init();
        Hall h2; h2.id = 2; h2.name = "Hall B"; h2.Init();
        c1.halls = { h1, h2 };

        Cinema c2(2, "Arena Cinema", "Burgas");
        Hall h3; h3.id = 3; h3.name = "Hall 1"; h3.Init();
        c2.halls = { h3 };

        cinemas = { c1, c2 };
    }
};