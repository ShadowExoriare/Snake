//
// Created by black on 14.06.2018.
//



#include <iostream>
#include "Snake.h"
#include "GameRules.h"

void Snake::lengthPlus(Snake snake){
    setLength(snake.getLength() + 1);
}

int Snake::getLength() const {
    return length;
}

void Snake::setLength(int length) {
    Snake::length = length;
}

const SnakePart *Snake::getSnakePart() const {
    return snakePart;
}

void Snake::snakeLogic(Map map, Snake snake) {
    if (snake.snakePart[0].x > map.getWeight()) {
        snakePart[0].setX(-1);
    }
    if (snake.snakePart[0].x < 0){
        snakePart[0].setX(map.getWeight() + 1);
    }
    if (snake.snakePart[0].y > map.getHeight() + 1) {
        snakePart[0].setY(-1);
    }
    if (snake.snakePart[0].y < 0) {
        snakePart[0].setY(map.getHeight() + 1);
    }
}

void Snake::tick(Snake snake, GameRules *rules) {
    for (int i=snake.length; i>0; --i) {
        this->snakePart[i].x=snake.snakePart[i-1].x;
        this->snakePart[i].y=snake.snakePart[i-1].y;
    }

    for (int i = 1; i < length; i++) {
        if(snake.snakePart[0].getX() == snake.snakePart[i].getX() && snake.snakePart[0].getY() == snake.snakePart[i].getY()){
            if(length > i){
                rules->setGameOver(true);
            }
            length = i;
        }
    }
}

int SnakePart::getX() const {
    return x;
}

void SnakePart::setX(int x) {
    SnakePart::x = x;
}

int SnakePart::getY() const {
    return y;
}

void SnakePart::setY(int y) {
    SnakePart::y = y;
}
