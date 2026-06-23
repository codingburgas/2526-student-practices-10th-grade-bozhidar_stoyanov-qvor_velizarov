#include "pch.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
using namespace std;

string FileManager::usersFile = "users.txt";
string FileManager::moviesFile = "movies.txt";

string FileManager::GenreToStr(Genre g) {
    switch (g) {
    case Genre::ACTION: return "ACTION";
    case Genre::COMEDY: return "COMEDY";
    case Genre::DRAMA:  return "DRAMA";
    case Genre::HORROR: return "HORROR";
    case Genre::SCIFI:  return "SCIFI";
    default:            return "ACTION";
    }
}

string FileManager::LangToStr(Language l) {
    switch (l) {
    case Language::ENGLISH:   return "ENGLISH";
    case Language::BULGARIAN: return "BULGARIAN";
    default:                  return "ENGLISH";
    }
}

Genre FileManager::StrToGenre(string s) {
    if (s == "ACTION")  return Genre::ACTION;
    if (s == "COMEDY")  return Genre::COMEDY;
    if (s == "DRAMA")   return Genre::DRAMA;
    if (s == "HORROR")  return Genre::HORROR;
    if (s == "SCIFI")   return Genre::SCIFI;
    return Genre::ACTION;
}

Language FileManager::StrToLang(string s) {
    if (s == "BULGARIAN") return Language::BULGARIAN;
    return Language::ENGLISH;
}

bool FileManager::UserExists(string username) {
    ifstream file(usersFile);
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        if (user == username) return true;
    }
    return false;
}

bool FileManager::SaveUser(string username, string password) {
    if (UserExists(username)) return false;
    ofstream file(usersFile, ios::app);
    file << username << "," << password << "\n";
    return true;
}

bool FileManager::CheckUser(string username, string password) {
    ifstream file(usersFile);
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, ',');
        if (user == username && pass == password) return true;
    }
    return false;
}

void FileManager::SaveMovies(vector<Movie>& movies) {
    ofstream file(moviesFile);
    for (auto& m : movies) {
        file << m.id << ","
            << m.title << ","
            << GenreToStr(m.genre) << ","
            << LangToStr(m.language) << ","
            << m.releaseDate << ","
            << m.description << "\n";
    }
}

vector<Movie> FileManager::LoadMovies() {
    vector<Movie> movies;
    ifstream file(moviesFile);
    if (!file.is_open()) return movies;

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string idStr, title, genre, lang, date, desc;
        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, lang, ',');
        getline(ss, date, ',');
        getline(ss, desc, ',');

        if (idStr.empty()) continue;
        Movie m(stoi(idStr), title, StrToGenre(genre), StrToLang(lang), date, desc);
        movies.push_back(m);
    }
    return movies;
}