#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    int board_x = mainGameMechsRef->getBoardSizeX();
    int board_y = mainGameMechsRef->getBoardSizeY();

    playerPos.setObjPos(board_x*0.5, board_y*0.5, '*');

}


Player::~Player()
{
    // :3
}

objPos Player::getPlayerPos() const
{
    return playerPos.getObjPos();
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    switch(input) { 
        case 'w':
            if(myDir != DOWN) myDir = UP;
            break;
        case 'a':
            if(myDir != RIGHT) myDir = LEFT;
            break;
        case 's':
            if(myDir != UP) myDir = DOWN;
            break;
        case 'd':
            if(myDir != LEFT) myDir = RIGHT;
            break;
        default:
            break;
    }         
}

void Player::movePlayer()
{
    int board_x = mainGameMechsRef->getBoardSizeX();
    int board_y = mainGameMechsRef->getBoardSizeY();

    int x = playerPos.pos->x;
    int y = playerPos.pos->y;
    switch(myDir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case STOP:
        default:
            break;
    }
    if(x >= board_x) {
        x = 1;
    } else if(x <= 0) {
        x = board_x -1;
    }
    if(y >= board_y) {
        y = 1;
    } else if(y <= 0) {
        y = board_y -1;
    }
    
}

// More methods to be added