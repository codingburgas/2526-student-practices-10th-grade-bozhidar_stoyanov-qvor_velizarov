#pragma once
#include <string>
using namespace std;

enum class Genre {
    ACTION,
    COMEDY,
    DRAMA,
    HORROR,
    SCIFI
};

enum class Language {
    ENGLISH,
    BULGARIAN
};

struct Movie {
    int id;
    string title;
    Genre genre;
    Language language;
    string releaseDate;
    string description;
};
