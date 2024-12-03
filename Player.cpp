#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* food)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    
    mainFood = food;
    board_x = mainGameMechsRef->getBoardSizeX();
    board_y = mainGameMechsRef->getBoardSizeY();

    playerPosList->insertHead(objPos(board_x*0.5, board_y*0.5, '*'));

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
    //checkSelfCollision();

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

    bool foodEaten = false;

    if(foodEaten == false) {
        playerPosList->insertHead(objPos(x, y, '*'));
        playerPosList->removeTail();
    }

    if(x == mainFood->getFoodPos().pos->x && y == mainFood->getFoodPos().pos->y) {
        foodEaten = true;
        playerPosList->insertHead(objPos(x, y, '*'));
        mainFood->generateFood(*playerPosList, mainGameMechsRef);
        mainGameMechsRef->incrementScore();
    }       


    // Food* mainFood;
    // objPos foodPos = mainFood->getFoodPos();
    // bool foodEaten = (x == foodPos.pos->x && y == foodPos.pos->y);
    // if(foodEaten) {
    //     playerPosList->insertTail(head);
    //     mainFood->generateFood(*playerPosList,mainGameMechsRef);
    //     mainGameMechsRef->incrementScore();
    // } else {
    //     playerPosList->insertHead(head);
    //     playerPosList->removeTail();
    // }

    
}

// void Player::checkSelfCollision() 
// {
//     bool died = false;
//     for(int i = 1; i < playerPosList->getSize(); i++) {
//         if(playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y) {
//             died = true;
//             mainGameMechsRef->setExitTrue();
//             mainGameMechsRef->setLoseFlag();
//             break;
//         }
//     }
// } 
// More methods to be added