#include "Player.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    board_x = mainGameMechsRef->getBoardSizeX();
    board_y = mainGameMechsRef->getBoardSizeY();

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
    playerPos.setObjPos(x, y, playerPos.getObjPos().symbol);
}

// More methods to be added