#include <SFML/Graphics.hpp>
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