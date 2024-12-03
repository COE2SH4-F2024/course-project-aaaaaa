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
    food = new Food(gamemechs->getBoardSizeX(), gamemechs->getBoardSizeY(), gamemechs);
    snake = new Player(gamemechs, food);
    food->generateFood(*snake->getPlayerPos(), gamemechs);
}

void GetInput(void)
{
    gamemechs->collectAsyncInput(); 
}

void RunLogic(void)
{

    snake->updatePlayerDir(); // Update the player direction based on input
    snake->movePlayer();
    // moved debugging logic to player.cpp
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  
    MacUILib_printf("Score: %d\n", gamemechs->getScore()); 
    int board_x = gamemechs->getBoardSizeX();
    int board_y = gamemechs->getBoardSizeY();
    int food_x = food->getFoodPos().pos->x;
    int food_y = food->getFoodPos().pos->y;
    objPosArrayList* playerpos = snake->getPlayerPos(); // to get the position of each element of the snake

    char variable;
    for(int y = 0; y < board_y; y++) {
        for(int x = 0; x < board_x; x++) {
            if(x == 0 || x == board_x -1 || y == 0 || y == board_y -1) {
                MacUILib_printf("#"); // if on edge, add # for game board
            } else if(x == food_x && y == food_y) {
                MacUILib_printf("o"); // if food generates there, add a 'o'
            } else {
                bool isplayer = false;
                for(int i = 0; i < playerpos->getSize(); i++) { // checking if player is taking up that space in the game board
                    objPos player_pos = playerpos->getElement(i);
                    if(y == player_pos.pos->y && x == player_pos.pos->x) {
                        MacUILib_printf("%c", player_pos.getSymbol());
                        isplayer = true; 
                        break;
                    }
                }
                if(!isplayer) { // printing a space if there is not a player
                    MacUILib_printf(" "); 
                }
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
    if (gamemechs->getLoseFlagStatus()) {
        MacUILib_printf("Game Over! You lost.\n");
    } else if (gamemechs->getExitFlagStatus()) {
        MacUILib_printf("Exited the game\n");
    } 
    MacUILib_printf("Final Score: %d", gamemechs->getScore());
    delete gamemechs;
    delete snake;  
    delete food;

    MacUILib_uninit();

}
