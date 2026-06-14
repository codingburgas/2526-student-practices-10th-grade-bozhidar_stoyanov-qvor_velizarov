#pragma once
#include "raylib.h"
#include "utils.h"
#include "Menu.h"
#include "MoviesScreen.h"
#include "ShowsScreen.h"
#include "BookingScreen.h"
#include "..\Data\DataManager.h"

class App {
public:
    void Run();

private:
    gameStates state = MAIN_MENU;
    DataManager db;
    Menu menu;
    MoviesScreen moviesScreen;
    ShowsScreen  showsScreen;
    BookingScreen bookingScreen;
};