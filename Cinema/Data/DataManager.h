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
        Hall h1; h1.id = 1; h1.name = "Hall A"; h1.Init(0); // Default layout
        Hall h2; h2.id = 2; h2.name = "Hall B"; h2.Init(0);
        c1.halls = { h1, h2 };

        Cinema c2(2, "Arena Cinema", "Burgas");
        Hall h3; h3.id = 3; h3.name = "Premium Hall"; h3.Init(1); // Premium layout
        c2.halls = { h3 };

        cinemas = { c1, c2 };
    }
};