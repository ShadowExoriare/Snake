//
// Created by black on 14.06.2018.
//

#include "Map.h"

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
