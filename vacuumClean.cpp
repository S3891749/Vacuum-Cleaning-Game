#include <iostream>
#include <cstdlib>
#include <string>
#include "game.h"
#include "helper.h"

using std::cout;
using std::cin;
using std::endl;

void showStudentInformation() {
    cout << "----------------------------\n";
    cout << "Name: Bui Quang Man" << endl;
    cout << "Student ID: S3891749" << endl;
    cout << "Email: s3891749@rmit.edu.vn" << endl;
    cout << "----------------------------\n";
}

int main() {
    int choice;
    bool quit = false;
    Game game;
    std::string userInput;

    while (!quit) {
        cout << "\nWelcome to Vacuum Cleaning Game!\n";
        cout << "-------------------\n";
        cout << "1. Play Game\n";
        cout << "2. Show student information\n";
        cout << "3. Quit\n";
        cout << "Please enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter a number between 1 and 3: ";
            cin.clear();  // Clear error flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
        }

        switch (choice) {
            case 1:
                // Call function to play the game
                getline(cin, userInput);
                game.start();
                break;
            case 2:
                // Call function to show student information
                showStudentInformation();
                break;
            case 3:
                cout << "Goodbye!\n";
                quit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return EXIT_SUCCESS;
}
