#include "Food.h"

Food::Food(int board_x, int board_y, GameMechs* gameMechRef) 
{
    boardsize_x = board_x;
    boardsize_y = board_y;
}

Food::~Food()
{

}

void Food::generateFood(const objPosArrayList& blockOff, GameMechs* gameMechRef)
{
    srand(time(NULL));
    int rand_x = 0;
    int rand_y = 0;
    bool canGenerate = false;
    while(!canGenerate) {
        rand_x = rand()%(boardsize_x-2)+1;
        rand_y = rand()%(boardsize_y-2)+1;
        canGenerate = true;
        for(int i = 0; i < blockOff.getSize(); i++) {
            if(blockOff.getElement(i).pos->x == rand_x && blockOff.getElement(i).pos->y == rand_y) {
                canGenerate = false;
                break;
            } 
        }
    }

    foodPos.setObjPos(rand_x, rand_y, 'o');
} 

objPos Food::getFoodPos()
{
    return foodPos.getObjPos();
}

