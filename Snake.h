//
// Created by black on 14.06.2018.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "Map.h"

struct SnakePart{
    int x;
    int y;


    void setX(int x);

    void setY(int y);

    int getX() const;

    int getY() const;
};

class Snake {
private:
    int dir = 1;
public:

    int length = 6;

    SnakePart snakePart[100];

    int getLength() const;

    void setLength(int length);

    int getDir() const;

    void setDir(int dir);

    const SnakePart *getSnakePart() const;

    void lengthPlus(Snake snake);

    void tick(Snake snake);

    void snakeLogic(Map map, Snake snake);


};


#endif //SNAKE_SNAKE_H
