#pragma once
#include <string>
#include <vector>
#include "Hall.h"
using namespace std;

class Cinema {
public:
    int id;
    string name;
    string city;
    vector<Hall> halls;

    Cinema() {}
    Cinema(int id, string name, string city) {
        this->id = id;
        this->name = name;
        this->city = city;
    }
};