//
// Created by black on 14.06.2018.
//

#include <SFML/Config.hpp>
#include "Map.h"
#include <stdlib.h>

using namespace sf;
int Map::genFruitX(){
    return rand() % getWeight() * getSize();
}

int Map::genFruitY(){
    return rand() % getHeight() * getSize();
}

int Map::getWeight() const {
    return weight;
}

void Map::setWeight(int weight) {
    Map::weight = weight;
}

int Map::getHeight() const {
    return height;
}

void Map::setHeight(int height) {
    Map::height = height;
}

int Map::getSize() const {
    return size;
}

void Map::setSize(int size) {
    Map::size = size;
}

