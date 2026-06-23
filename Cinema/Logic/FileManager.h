#pragma once
#include <string>
#include <vector>
#include "..\Data\Movie.h"
using namespace std;

class FileManager {
public:
    static bool       SaveUser(string username, string password);
    static bool       CheckUser(string username, string password);
    static bool       UserExists(string username);

    static void       SaveMovies(vector<Movie>& movies);
    static vector<Movie> LoadMovies();

private:
    static string     usersFile;
    static string     moviesFile;

    static string     GenreToStr(Genre g);
    static string     LangToStr(Language l);
    static Genre      StrToGenre(string s);
    static Language   StrToLang(string s);
};