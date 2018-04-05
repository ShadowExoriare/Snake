//
// Created by black on 05.04.2018.
//

#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H

#include <SFML/Graphics.hpp>
using namespace sf;

View view;

View getPlayerCoordinateView(float x, float y){
    float tempX = x;
    float tempY = y;

    if(x < 320) tempX = 320;
    if(y < 240) tempY = 240;
    if(y > 554) tempY = 554;

    view.setCenter(tempX, tempY);

    return view;
}

#endif //SNAKE_VIEW_H
