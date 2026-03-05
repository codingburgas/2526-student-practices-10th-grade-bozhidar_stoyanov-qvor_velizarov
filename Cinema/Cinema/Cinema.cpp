#include <iostream>
#include "Menu.h"

using namespace std;

int main() {
    int choice = -1;

    while (choice != 0) {
        showMainMenu();
        cin >> choice;

        if (choice == 1) customerPortal();
        else if (choice == 2) adminPortal();
    }

    cout << "Exiting system..." << endl;
    return 0;
}
