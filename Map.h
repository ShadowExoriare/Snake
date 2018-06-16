//
// Created by black on 14.06.2018.
//

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H


class Map {
private:
    int weight = 10;
    int height = 10;
    int size = 64;

public:
    int getWeight() const;

    void setWeight(int weight);

    int getHeight() const;

    void setHeight(int height);

    int getSize() const;

    void setSize(int size);

    int genFruitX();

    int genFruitY();

};


#endif //SNAKE_MAP_H
