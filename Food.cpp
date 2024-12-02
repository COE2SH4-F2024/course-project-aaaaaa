#include "Food.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"

Food::Food(int board_x, int board_y, GameMechs* gameMechRef) 
{
    boardsize_x = board_x;
    boardsize_y = board_y;
}

Food::~Food()
{

}

void Food::generateFood(const objPos& blockOff)
{
    Player* playerRef;
    GameMechs* gameMechRef;

    int rand_x = 0;
    int rand_y = 0;
    bool canGenerate = false;
    while(!canGenerate) {
        rand_x = rand()%boardsize_x+1;
        rand_y = rand()%boardsize_y+1;
        if(blockOff.pos->x == getFoodPos().pos->x && blockOff.pos->y == getFoodPos().pos->y) {
            canGenerate = false;
            break;
        } 
        canGenerate = true;
    }

    foodPos.setObjPos(rand_x, rand_y, 'o');
}

objPos Food::getFoodPos()
{
    return foodPos.getObjPos();
}

