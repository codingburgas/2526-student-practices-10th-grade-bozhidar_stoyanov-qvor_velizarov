#pragma once
#include "raylib.h"
#include "utils.h"
#include "Menu.h"
#include "LoginScreen.h"
#include "SignupScreen.h"
#include "MoviesScreen.h"
#include "ShowsScreen.h"
#include "BookingScreen.h"
#include "CompletedScreen.h"
#include "AdminScreen.h"
#include "..\Data\DataManager.h"

class App {
public:
    void Run();

private:
    gameStates      state = LOGIN;
    DataManager     db;
    Menu            menu;
    LoginScreen     loginScreen;
    SignupScreen    signupScreen;
    MoviesScreen    moviesScreen;
    ShowsScreen     showsScreen;
    BookingScreen   bookingScreen;
    CompletedScreen completedScreen;
    AdminScreen     adminScreen;
};