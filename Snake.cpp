//
// Created by black on 14.06.2018.
//

#include <iostream>
#include "Snake.h"
#include "Map.h"

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
        this->snakePart[0].setX(0);
    }
    if (snake.snakePart[0].x < 0){
        this->snakePart[0].setX(map.getWeight());
    }
    if (snake.snakePart[0].y > map.getHeight()) {
        this->snakePart[0].setY(0);
    }
    if (snake.snakePart[0].y < 0) {
        this->snakePart[0].setY(map.getHeight());
    }
}

void Snake::tick(Snake snake) {
    for (int i=snake.getLength(); i>0; --i) {
        this->snakePart[i].x=snake.snakePart[i-1].x;
        this->snakePart[i].y=snake.snakePart[i-1].y;
    }

    for (int i = 1; i < length; i++) {
        if(snake.snakePart[0].getX() == snake.snakePart[i].getX() && snake.snakePart[0].getY() == snake.snakePart[i].getY()){
            length = i;
        }
    }
}

int Snake::getDir() const {
    return dir;
}

void Snake::setDir(int dir) {
    Snake::dir = dir;
}

void SnakePart::setX(int x) {
    SnakePart::x = x;
}

void SnakePart::setY(int y) {
    SnakePart::y = y;
}

int SnakePart::getX() const {
    return x;
}

int SnakePart::getY() const {
    return y;
}
