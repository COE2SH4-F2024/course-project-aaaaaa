#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

class Food
{
    private:
        objPos foodPos;
        int boardsize_x;
        int boardsize_y;
    public:
        Food(int board_x, int board_y, GameMechs* gameMechRef);
        ~Food();

        void generateFood(const objPos& blockOff);
        objPos getFoodPos();

};

#endif