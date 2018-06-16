#include <SFML/Graphics.hpp>
#include <iostream>
#include "SnakeLogic.h"
using namespace sf;

SnakeLogic snakeLogic;

int main()
{
    snakeLogic.objectInitialization();
    snakeLogic.gameMenu();
    snakeLogic.gameCycle();

    return 0;
}