#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag; // delete this
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

    while(exitFlag == false)  
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
    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
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
