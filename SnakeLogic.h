//
// Created by black on 15.06.2018.
//

#ifndef SNAKE_SNAKELOGIC_H
#define SNAKE_SNAKELOGIC_H


#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Snake.h"
#include "Fruit.h"
#include "GameRules.h"


using namespace sf;
class SnakeLogic {
public:
    Map map;
    Snake snake;
    void objectInitialization();
    void keyboardPressing();
    void dirWatcher();
    void drawer();
    void snakeDrawer();
    void gameCycle();
    void gameMenu();
    void gameEnding();
    void fruitCycle();
    void snakeLogic();
    void eatFruit(Fruit *fruit);
    void gameOver();

    Texture gameTableTexture;
    Texture snakeHeadTexture;
    Texture redAppleTexture;
    Texture grayAppleTexture;
    Texture greenAppleTexture;
    Texture snakePartsTexture;
    Texture menuScroll;
    Texture strawberryTexture;
    Texture pearTexture;
    Texture gameOverTexture;



    Sprite gameBackground;
    Sprite snakeHeadSprite;
    Sprite snakePartsSprite;
    Sprite grayAppleSprite;
    Sprite greenAppleSprite;
    Sprite redAppleSprite;
    Sprite menuScrollSprite;
    Sprite strawberrySprite;
    Sprite pearSprite;
    Sprite gameOverSprite;
    Texture poisonTexture;


    Fruit *redApple = new Fruit(false);
    Fruit *greenApple = new Fruit(false);
    Fruit *grayApple = new Fruit(true);
    Fruit *strawberry = new Fruit(true);
    Fruit *pear = new Fruit(false);
    GameRules *rules = new GameRules();

    const Map &getMap() const;

    void setMap(const Map &map);

    const Snake &getSnake() const;

    void setSnake(const Snake &snake);

    virtual ~SnakeLogic();

};


#endif //SNAKE_SNAKELOGIC_H
