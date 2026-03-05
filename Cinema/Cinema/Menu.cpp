#include<iostream>
#include "Menu.h"

using namespace std;

void showMainMenu() {
    cout << "\n====================================" << endl;
    cout << "      CINEMA BOOKING SYSTEM        " << endl;
    cout << "====================================" << endl;
    cout << "1. [Customer] Browse & Book" << endl;
    cout << "2. [Admin] Manage Shows/Movies" << endl;
    cout << "0. Exit" << endl;
    cout << "Selection: ";
}

void customerPortal() {
    int choice;
    cout << "\n--- CUSTOMER INTERFACE ---" << endl;
    cout << "1. Search Movies (Title/Genre/Date)" << endl;
    cout << "2. View All Available Shows" << endl;
    cout << "3. Book a Ticket" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Choice: ";
    cin >> choice;
}

void adminPortal() {
    int choice;
    cout << "\n--- ADMINISTRATIVE PANEL ---" << endl;
    cout << "1. Add New Movie" << endl;
    cout << "2. Add/Edit/Delete Show" << endl;
    cout << "3. View Booking Notifications" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Choice: ";
    cin >> choice;
}