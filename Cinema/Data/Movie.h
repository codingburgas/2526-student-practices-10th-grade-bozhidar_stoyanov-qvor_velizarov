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

class Movie {
public:
    int id;
    string title;
    Genre genre;
    Language language;
    string releaseDate;
    string description;

    Movie() {}
    Movie(int id, string title, Genre genre, Language language,
        string releaseDate, string description) {
        this->id = id;
        this->title = title;
        this->genre = genre;
        this->language = language;
        this->releaseDate = releaseDate;
        this->description = description;
    }
};