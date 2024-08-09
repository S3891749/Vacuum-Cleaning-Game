#include "board.h"
#include "common.h"
#include "player.h"
#include "game.h"

using std::vector;
constexpr int BOARD_SIZE = 10;

// predefined configurations for board layouts
const vector<vector<Cell>> Board::BOARD_1 =
{
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};
// constructor of the board class, initializes the board to a 10x10 of empty Cell
Board::Board(): grid(10, vector<Cell>(10, EMPTY)){}

// destructor with empty body
Board::~Board(){}

// loads a board configuration based on the board ID provided
void Board::load(int boardId)
{
    clearBoard(); // reset the board before loading new configuration
    const auto& boardConfig = (boardId == 1) ? BOARD_1 : BOARD_2; // select the board configuration
    grid = boardConfig; // set the grid to the chosen configuration
}

// attempts to place a player on the board at a specified position
bool Board::placePlayer(Position position) {
    if (position.x < 0 || position.x >= BOARD_SIZE || position.y < 0 || position.y >= BOARD_SIZE) {
        std::cout << "Invalid input.\n";
        return false;  // position is out of bounds
    }
    if (grid[position.y][position.x] != EMPTY) {
        std::cout << "Unable to place at that positions.\n";
        return false;  // position is occupied or invalid
    }

    grid[position.y][position.x] = PLAYER;  // assuming PLAYER is defined in Cell enum
    


    return true;
}

// displays the current state of the board with player and block positions
void Board::display(Player* player) {
    // Display the column headers
    std::cout << " |";
    for (int x = 0; x < 10; ++x) {
        std::cout << x << "|";
    }
    std::cout << "\n";

    // display the grid
    for (int y = 0; y < 10; ++y) {
        std::cout << y << "|"; // row header
        for (int x = 0; x < 10; ++x) {
            if (player && player->position.x == x && player->position.y == y) {
                // display the player with the direction arrow based on the facing direction
                player->displayDirection();
            } else {
                // display cells as either empty or blocked
                std::cout << (grid[y][x] == Cell::EMPTY ? ' ' : '*');
            }
            std::cout << "|"; // cell boundary
        }
        std::cout << "\n";
    }
}



void Board::clearBoard() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), EMPTY);
    }
}
void Board::displayEmptyBoard() {
    // print the column header
    std::cout << " |";
    for (int x = 0; x < 10; ++x) {
        std::cout << x << "|";
    }
    std::cout << "\n";
    // nested loop to print out the row of the empty board
    for (int y = 0; y < 10; ++y) {
        std::cout << "|" << y;
        for (int x = 0; x < 10; ++x) {
            std::cout << " " << "|";
        }
        std::cout << "\n";
    }
}

// handles the player's forward movement on the board, checking for boundaries and obstacles
PlayerMove Board::movePlayerForward(Player* player) {
    Position newPos = player->getNextForwardPosition();

    // ensure new position is within bounds and not blocked
    if (newPos.x < 0 || newPos.x >= BOARD_SIZE || newPos.y < 0 || newPos.y >= BOARD_SIZE) {
        failedMoves++;
        std::cout << "The vacuum cleaner is at the edge of the board and cannot move further in that direction.\n" << std::endl;
        return CELL_BLOCKED;  // Movement blocked by boundary or obstacle
    } else if (grid[newPos.y][newPos.x] == BLOCKED){
        failedMoves++;
        std::cout << "Error: Unable to move - cell is blocked." << std::endl;
        return CELL_BLOCKED;
    }
    // update the grid to reflect the player's new position
    grid[player->position.y][player->position.x] = EMPTY; // clear old position
    grid[newPos.y][newPos.x] = PLAYER;                    // set new position
    player->position = newPos; // directly setting new position
    player->moves++; // increment moves
    return PLAYER_MOVED;  // indicate successful movement
}

void Board::setPlayer(Player* p) {
    player = p;
}

// validates if a given position on the board is within bounds and not blocked
bool Board::isPositionValid(const Position& pos) {
    if (pos.x < 0 || pos.x >= BOARD_SIZE || pos.y < 0 || pos.y >= BOARD_SIZE) {
        return false;  // check if position is out of bounds
    }
    return grid[pos.y][pos.x] == EMPTY;  // ensure the cell is empty and not blocked
}
// resets failed moves counter
void Board::reset() {
    failedMoves = 0;
}

