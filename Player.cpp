#include "Player.h"


Player::Player(GameMechs* thisGMRef, int startsize)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    board_x = mainGameMechsRef->getBoardSizeX();
    board_y = mainGameMechsRef->getBoardSizeY();

    playerPosList->insertHead(objPos(board_x*0.5, board_y*0.5, '*'));
    for(int i = 1; i <= startsize; i++) {
        playerPosList->insertTail(objPos((board_x*0.5)-i, (board_y*0.5), '*'));
    }

}


Player::~Player()
{
    delete[] playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    switch(input) { 
        case 'w':
            if(myDir != DOWN) {
                myDir = UP;
            }
            break;
        case 'a':
            if(myDir != RIGHT) {
                myDir = LEFT;
            }
            break;
        case 's':
            if(myDir != UP) {
                myDir = DOWN;
            }
            break;
        case 'd':
            if(myDir != LEFT) {
                myDir = RIGHT;
            }
            break;
        // Game Exit
        case 'q': 
            mainGameMechsRef->setExitTrue();
            break;
        // Game lost
        case 'l': 
            mainGameMechsRef->setLoseFlag();
            break;
        // Debug key for ending game
        case 'p':
            mainGameMechsRef->setLoseFlag();
            break;
        // Increment score with debug key
        case 'o':
            mainGameMechsRef->incrementScore();
            break;
        default:
            break;
    }         
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{

    if (mainGameMechsRef->getLoseFlagStatus()) {
        myDir = STOP;
        return;
    }
    int board_x = mainGameMechsRef->getBoardSizeX();
    int board_y = mainGameMechsRef->getBoardSizeY();

    int x = playerPosList->getHeadElement().pos->x;
    int y = playerPosList->getHeadElement().pos->y;
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
    if(myDir != STOP) {
        head = playerPosList->getHeadElement();
        head.pos->x = x;
        head.pos->y = y;
        playerPosList->insertHead(objPos(x, y, '*'));
        playerPosList->removeTail();
    }
    }

// More methods to be added