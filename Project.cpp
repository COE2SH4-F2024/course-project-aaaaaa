#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000


Player* snake;
GameMechs* gamemechs;
Food* food;

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
    food = new Food(gamemechs->getBoardSizeX(), gamemechs->getBoardSizeY(), gamemechs);
    //exitFlag = false;
    food->generateFood(snake->getPlayerPos());
}

void GetInput(void)
{
    gamemechs->collectAsyncInput(); 
}

void RunLogic(void)
{

    snake->updatePlayerDir(); // Update the player direction based on input
    snake->movePlayer();
    char input = gamemechs->getInput();
    // moved logic to player.cpp
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    int board_x = gamemechs->getBoardSizeX();
    int board_y = gamemechs->getBoardSizeY();
    int player_x = snake->getPlayerPos().pos->x;
    int player_y = snake->getPlayerPos().pos->y;
    int food_x = food->getFoodPos().pos->x;
    int food_y = food->getFoodPos().pos->y;
    for(int y = 0; y < board_y; y++) {
        for(int x = 0; x < board_x; x++) {
            if(x == 0 || x == board_x - 1 || y == 0 || y == board_y - 1) {
                MacUILib_printf("#");
            } else if(x == player_x && y == player_y) {
                MacUILib_printf("*");
            } else if(x == food_x && y == food_y) {
                MacUILib_printf("o");
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
    delete food;

    MacUILib_uninit();

}
