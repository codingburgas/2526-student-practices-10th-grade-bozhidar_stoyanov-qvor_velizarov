#pragma once
#include <string>
#include <vector>
#include "Hall.h"
using namespace std;

struct Cinema {
    int id;
    string name;
    string city;
    vector<Hall> halls;
};