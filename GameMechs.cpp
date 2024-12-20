#include "GameMechs.h"
#include "MacUILib.h"


GameMechs::GameMechs()

{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}


GameMechs::~GameMechs()
{
    // no destructor needed, nothing new is made
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
void GameMechs::collectAsyncInput() {
    if (MacUILib_hasChar() != 0) {
        input = MacUILib_getChar();
    }

    if (input == '\e') { //if esc key is pressed
        setExitTrue();
    }
}

char GameMechs::getInput() const
{
    
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    ++score;   
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}


// More methods should be added here