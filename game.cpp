#include "game.h"
#include "player.h"
#include "board.h"
#include <sstream>  

using std::stringstream;

using std::cout;
using std::cin;
using std::endl;
using std::string;

// constructors for game class, initialize the board and set the player pointer to nullptr
Game::Game()
{
    board = new Board();
    player = nullptr;

}

// deconstructors for game class
Game::~Game()
{
    delete board;
    if (player) {
        delete player; // Safely delete player if it has been initialized
    }

}
// start function to display all the command prompts and wait for user's input
void Game::start()
{
    // display initial game commands and prompt the user to press enter to continue
    std::cout << "\nYou can use the following commands to play the game:\n";
    std::cout << "load <g>\n";
    std::cout << "g: number of the game board to load\n";
    std::cout << "init <x>,<y>,<direction>\n";
    std::cout << "x: horizontal position of the vacuum cleaner in the room (between 0 & 9)\n";
    std::cout << "y: vertical position of the vacuum cleaner in the room (between 0 & 9)\n";
    std::cout << "direction: direction of the vacuum cleaner’s movement (north, east, south, west)\n";
    std::cout << "forward (or f)\n";
    std::cout << "turn_left (or l)\n";
    std::cout << "turn_right (or r)\n";
    std::cout << "quit\n";
    std::cout << "\nPress enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // command line to wait for user to press Enter
    
    // after user press Enter, display the empty board
    Board::displayEmptyBoard();

    // notify player about the available commands from this point
    cout << "At this stage of the program, only two commands are acceptable:\n";
    cout << "load <g>\n";
    cout << "quit\n";
    cout << endl;
    // attempt to load the board
    if (!loadBoard()) {
        cout << "Game loading failed or was terminated by the user." << endl;
        return;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // initialize player's position & direction
    if (!initializePlayer()) {
        cout << "Initialization failed." << endl;
        return;
    }
    
    play(); // start the gameplay loop
    
}

// load a game board based on the user's input
bool Game::loadBoard()
{
    string command;
    int boardNumber;
    while (cin >> command) {
        if (command == "quit") {
            return false; // exit loop if user input "quit"
        }
        else if (!Helper::isNumber(command)) { // validate if input is a number using Helper function
            std::cout << "Invalid input. Please enter a board number (1 or 2), or 'quit' to exit: ";
            continue; // ask for input again if invalid
        } 
        else if (command == "1" || command == "2") {
            boardNumber = std::stoi(command); // convert command into the integer
            board->load(boardNumber); // load the board based on boardNumber that user input in
            cout << "\nload " << boardNumber; // print out the message before load
            cout << endl;
            board->display(); // display loaded board
            return true; // indicate loading successful
        } else {
            cout << "Invalid board number. Please enter a board number (1 or 2), or 'quit' to exit: ";
        }
    }
    return false;
}

// initializes the player based on user commands
bool Game::initializePlayer() {
    cout << "\nInit <x>,<y>,<direction>:\n";
    string command;
    getline(cin, command);  // Read the full line after the prompt

    int x, y;
    char comma1, comma2;
    string dir;
    stringstream ss(command);

    ss >> x >> comma1 >> y >> comma2 >> dir;
    if (ss.fail() || comma1 != ',' || comma2 != ',') {
        cout << "\nInvalid Input. Correct format: <x>,<y>,<direction>.\n";
        return false;
    }

    Direction direction = stringToDirection(dir);
    if (direction == INVALID_DIRECTION) {
        cout << "Invalid direction specified.\n";
        return false;
    }

    Position pos(x, y);
    if (!board->isPositionValid(pos)) {
        cout << "Unable to place player at specified position.\n";
        return false;
    }

    if (player != nullptr) {
        delete player; // Safely delete any existing player before reinitializing
    }
    player = new Player();
    player->initialisePlayer(&pos, direction);
    
    

    if (!board->placePlayer(player->position)) {
        cout << "Unable to place player at specified position.\n";
        return false;
    }
    board->display(player); // Display the board with the player
    return true;
}


// Gameplay loop: processes user commands to control the game
void Game::play() {
    std::string command;
    cout << "\nAt this stage of the program, only four commands are acceptable:\n";
    cout << "forward (or f)\n";
    cout << "turn_left (or l)\n";
    cout << "turn_right (or r)\n";
    cout << "quit\n";
    while (true) {
        cout << "\nEnter command: ";
        if (!getline(cin, command)) {
            cout << "Failed to read input, exiting game.\n";
            break;
        }

        if (command == "quit") {
            cout << "Game ended by user.\n";
            cout << "Total player moves: " << successfulMoves << endl; // Display total successful moves
            cout << "Moves hit the block: " << board->failedMoves << endl;
            reset();
            board->reset();
            break;
        } else if (command == "forward" or command == "f") {
            // Implement moving forward
            board->movePlayerForward(player);
            cout << "forward\n";
            successfulMoves++;
        } else if (command == "turn_left" or command == "l") {
            // Implement turning left
            player->turnDirection(TURN_LEFT);
            cout << "\nturn_left\n";
        } else if (command == "turn_right" or command == "r") {
            // Implement turning right
            player->turnDirection(TURN_RIGHT);
            cout << "\nturn_right\n";
        } else {
            cout << "\nInvalid input.\n";
            break;
        }
        // Optionally display the game state after each command
        board->display(player);  
    }
}
// Converts string to direction enum
Direction Game::stringToDirection(const std::string& dir) {
    if (dir == "north") return NORTH;
    else if (dir == "east") return EAST;
    else if (dir == "south") return SOUTH;
    else if (dir == "west") return WEST;
    else return INVALID_DIRECTION;
}
// Resets game statistics
void Game::reset() {
    successfulMoves = 0;
}
