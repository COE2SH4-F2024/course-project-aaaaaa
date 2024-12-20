#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* food)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; // begins at stop position
    mainFood = food;
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
    switch(input) { // as long as the player is NOT moving in the opposite direction, it can turn 
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
    if (mainGameMechsRef->getLoseFlagStatus()) { // stops the game if lose flag becomes true (if you lost)
        myDir = STOP;
        return;
    }
    int board_x = mainGameMechsRef->getBoardSizeX();
    int board_y = mainGameMechsRef->getBoardSizeY();

    int x = playerPosList->getHeadElement().pos->x;
    int y = playerPosList->getHeadElement().pos->y;
    switch(myDir) { // changing coordinates of the snake head depending on which direction it is moving
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
    

    if(x >= board_x -1) { // wraparound logic
        x = 1;
    } else if(x <= 0) {
        x = board_x -1;
    }
    if(y >= board_y -1) {
        y = 1;
    } else if(y <= 0) {
        y = board_y -1;
    }

    bool foodEaten = false;
    checkSelfCollision(x, y); // checks the new x and y position to see if a part of the snake body already exists at those coordinates
    if(foodEaten == false) {
        playerPosList->insertHead(objPos(x, y, '*'));
        playerPosList->removeTail();
    }

    if(x == mainFood->getFoodPos().pos->x && y == mainFood->getFoodPos().pos->y) { // checks if food is eaten; does not remove tail if it is
        foodEaten = true;
        playerPosList->insertHead(objPos(x, y, '*'));
        mainFood->generateFood(*playerPosList, mainGameMechsRef);
        mainGameMechsRef->incrementScore();
    }       
    
}

void Player::checkSelfCollision(int x, int y) 
{
    for(int i = 1; i < playerPosList->getSize(); i++) {
        if(x == playerPosList->getElement(i).getObjPos().pos->x && y == playerPosList->getElement(i).getObjPos().pos->y) {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
            break;
        }
    }
} 
// More methods to be added