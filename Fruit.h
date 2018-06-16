//
// Created by black on 16.06.2018.
//

#ifndef SNAKE_FRUIT_H
#define SNAKE_FRUIT_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Snake.h"

using namespace sf;

class Fruit {
private:
    int objectX;
    int objectY;
    bool corrupt;
    int ending = 0;

public:
    Sprite fruitSprite;

    Fruit(bool isCorrupt){
        objectX = rand() % 10 * 64;
        objectY = rand() % 10 * 64;
        corrupt = isCorrupt;
        fruitSprite.setPosition(objectX, objectY);
    }
    Fruit(bool isCorrupt, Sprite fruit){
        corrupt = isCorrupt;
        objectX = rand() % 10 * 64;
        objectY = rand() % 10 * 64;
        fruitSprite = fruit;
        fruitSprite.setPosition(objectX, objectY);
    }

    int getObjectX() const;

    void setObjectX(int objectX);

    int getObjectY() const;

    void setObjectY(int objectY);

    bool isCorrupt() const;

    void setCorrupt(bool corrupt);

    const Sprite &getFruitSprite() const;

    void setFruitSprite(const Sprite &fruitSprite);

    virtual ~Fruit();

    void setRandCoord();

    int getEnding() const;

    void setEnding(int ending);

};


#endif //SNAKE_FRUIT_H
