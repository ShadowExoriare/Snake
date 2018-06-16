//
// Created by black on 14.06.2018.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "Map.h"
#include "Fruit.h"
#include "GameRules.h"

struct SnakePart{
    int x;
    int y;

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);
};

class Snake {
public:

    int length = 1;

    SnakePart snakePart[100];

    int getLength() const;

    void setLength(int length);

    const SnakePart *getSnakePart() const;

    void lengthPlus(Snake snake);

    void tick(Snake snake, GameRules *rules);

    void snakeLogic(Map map, Snake snake);


};


#endif //SNAKE_SNAKE_H
