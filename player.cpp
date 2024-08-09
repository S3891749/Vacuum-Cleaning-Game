#include "player.h"
#include "board.h"
#include "game.h"

// default constructor initializing Position with zero coordinates
Position::Position() : x(0), y(0) {}

// constructor for Position that allows setting initial coordinates
Position::Position(int x, int y) : x(x), y(y){}

// default constructor for Player initializing at (0, 0) facing NORTH and with zero moves
Player::Player() : position(0, 0), direction(NORTH), moves(0){}

// initializes player with a given position and direction
void Player::initialisePlayer(Position* position, Direction direction)
{
    if (position) {
        this->position = *position; // set player's position if a valid position pointer is provided
    }
    this->direction = direction; // Set player's direction
}

// changes player's direction based on the turn instruction
void Player::turnDirection(TurnDirection turnDirection)
{
    // cast current direction to an integer
    int dir = static_cast<int>(this->direction);
    if (turnDirection == TURN_LEFT) {
        // calculate new direction for left turn
        dir = (dir + 3) % 4; // Turn left
    } else {
        // Calculate new direction for right turn
        dir = (dir + 1) % 4; // Turn right
    }
    // cast back to Direction enum after calculation
    this->direction = static_cast<Direction>(dir);
}

// calculates the next forward position based on current direction
Position Player::getNextForwardPosition()
{
    Position newPos = this->position; // start with current position
    switch (this->direction) { // adjust position based on direction
        case NORTH: newPos.y -= 1; break;
        case EAST:  newPos.x += 1; break;
        case SOUTH: newPos.y += 1; break;
        case WEST:  newPos.x -= 1; break;
        case INVALID_DIRECTION:
            std::cerr << "Invalid direction encountered.\n"; // print out an error if direction is invalid
            break;
    }
    return newPos;// return the new position

}

// updates player's position to a new position and increments move count
void Player::updatePosition(Position position)
{
    this->position = position;// set new position
    this->moves++; // increment moves count
}

// displays the current direction of the player as an arrow in the console
void Player::displayDirection() {
    switch (direction) {
        case NORTH: std::cout << "↑"; break;
        case EAST:  std::cout << "→"; break;
        case SOUTH: std::cout << "↓"; break;
        case WEST:  std::cout << "←"; break;
        default:    std::cout << "?"; break; // indicates an unrecognized direction
    }
    std::cout.flush();  // flush the output to ensure it appears in the console immediately
}



