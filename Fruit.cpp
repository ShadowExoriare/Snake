//
// Created by black on 16.06.2018.
//

#include "Fruit.h"

void Fruit::setRandCoord(){
    int tempRandX = rand() % 10 * 64;
    int tempRandY = rand() % 10 * 64;
    fruitSprite.setPosition(tempRandX, tempRandY);
    setObjectX(tempRandX);
    setObjectY(tempRandY);
}

Fruit::~Fruit() {

}

int Fruit::getObjectX() const {
    return objectX;
}

void Fruit::setObjectX(int objectX) {
    Fruit::objectX = objectX;
}

int Fruit::getObjectY() const {
    return objectY;
}

void Fruit::setObjectY(int objectY) {
    Fruit::objectY = objectY;
}

bool Fruit::isCorrupt() const {
    return corrupt;
}

void Fruit::setCorrupt(bool corrupt) {
    Fruit::corrupt = corrupt;
}

const Sprite &Fruit::getFruitSprite() const {
    return fruitSprite;
}

void Fruit::setFruitSprite(const Sprite &fruitSprite) {
    Fruit::fruitSprite = fruitSprite;
}

int Fruit::getEnding() const {
    return ending;
}

void Fruit::setEnding(int ending) {
    Fruit::ending = ending;
}

