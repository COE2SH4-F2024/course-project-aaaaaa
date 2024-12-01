#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000


Player* snake;
GameMechs* gamemechs;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gamemechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gamemechs = new GameMechs();
    snake = new Player(gamemechs);
    //exitFlag = false;
}

void GetInput(void)
{
   char input = MacUILib_getChar();
    gamemechs->setInput(input); 
}

void RunLogic(void)
{

    
    char input = gamemechs->getInput();


    
    switch (input) {
        // Game Exit
        case 'q': 
            gamemechs->setExitTrue();
            break;
        // Game lost
        case 'l': 
            gamemechs->setLoseFlag();
            break;
        // Debug key for ending game
        case 'p':
            gamemechs->setLoseFlag();
            break;
        // Increment score with debug key
        case 'o':
            gamemechs->incrementScore();
            break;
        default:
            
            break;
}
if (!gamemechs->getLoseFlagStatus()) {
        gamemechs->incrementScore(); // Increment score for a valid action
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    int board_x = gamemechs->getBoardSizeX();
    int board_y = gamemechs->getBoardSizeY();
    int player_x = snake->getPlayerPos().pos->x;
    int player_y = snake->getPlayerPos().pos->y;
    for(int y = 0; y < board_y; y++) {
        for(int x = 0; x < board_x; x++) {
            if(x == 0 || x == board_x - 1 || y == 0 || y == board_y - 1) {
                MacUILib_printf("#");
            } else if(x == player_x && y == player_y) {
                MacUILib_printf("*");
            } else {
                MacUILib_printf(" ");
            }
            
        }
        MacUILib_printf("\n");
    }

    
    MacUILib_printf("Score: %d\n", gamemechs->getScore());

    
    if (gamemechs->getLoseFlagStatus()) {
        MacUILib_printf("Game Over! You lost.\n");
    } else if (gamemechs->getExitFlagStatus()) {
        MacUILib_printf("Exited the game\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    delete gamemechs;
    delete snake;  

    MacUILib_uninit();

}
