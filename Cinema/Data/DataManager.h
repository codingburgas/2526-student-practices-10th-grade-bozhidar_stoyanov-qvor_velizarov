#pragma once
#include <vector>
#include "Movie.h"
#include "Cinema.h"
#include "Show.h"
using namespace std;

class DataManager {
public:
    vector<Movie>  movies;
    vector<Cinema> cinemas;
    vector<Show>   shows;

    void Init() {
        movies = {
            Movie(1, "Gladiator II",    Genre::ACTION, Language::ENGLISH,   "22-11-2024", "A sequel to the legendary Gladiator."),
            Movie(2, "Oppenheimer",     Genre::DRAMA,  Language::ENGLISH,   "21-07-2023", "The story of the atomic bomb."),
            Movie(3, "Talk to Me",      Genre::HORROR, Language::ENGLISH,   "28-07-2023", "A terrifying supernatural thriller."),
            Movie(4, "The Gorge",       Genre::SCIFI,  Language::ENGLISH,   "14-02-2025", "Two snipers fall in love across a gorge."),
            Movie(5, "Dossier Bulgare", Genre::DRAMA,  Language::BULGARIAN, "01-03-2024", "A Bulgarian drama thriller."),
        };

        Cinema c1(1, "CineGrand", "Sofia");
        Hall h1; h1.id = 1; h1.name = "Hall A"; h1.Init();
        Hall h2; h2.id = 2; h2.name = "Hall B"; h2.Init();
        c1.halls = { h1, h2 };

        Cinema c2(2, "Arena Cinema", "Burgas");
        Hall h3; h3.id = 3; h3.name = "Hall 1"; h3.Init();
        c2.halls = { h3 };

        cinemas = { c1, c2 };

        shows = {
            Show(1, 1, 1, 1, "10:00", "10-05-2025"),
            Show(2, 1, 2, 1, "14:00", "10-05-2025"),
            Show(3, 2, 1, 1, "18:00", "10-05-2025"),
            Show(4, 3, 3, 2, "20:00", "10-05-2025"),
            Show(5, 4, 3, 2, "16:00", "11-05-2025"),
        };
    }
};