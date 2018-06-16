//
// Created by black on 15.06.2018.
//

#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <sstream>
#include "SnakeLogic.h"
using namespace sf;


    int score = 0;
    int dir = 0;
    RenderWindow window(VideoMode(1280, 720), "Snake Game!");
    Font font;
    Text scoreText("", font, 50);
    Text totalScore("Total score: ", font, 50);
    Text levelInfo("", font, 30);
    Text badEnding("", font, 30);

void SnakeLogic::objectInitialization() {

    gameTableTexture.loadFromFile("./Resources/Images/background.png");
    snakeHeadTexture.loadFromFile("./Resources/images/snake.png");
    snakePartsTexture.loadFromFile("./Resources/Images/snakePart.png");
    redAppleTexture.loadFromFile("./Resources/Images/appleRed.png");
    greenAppleTexture.loadFromFile("./Resources/Images/appleGreen.png");
    grayAppleTexture.loadFromFile("./Resources/Images/appleGray.png");
    menuScroll.loadFromFile("./Resources/Images/gameScroll.png");
    strawberryTexture.loadFromFile("./Resources/Images/strawberry.png");
    pearTexture.loadFromFile("./Resources/Images/pear.png");
    gameOverTexture.loadFromFile("./Resources/Images/gameOver.png");
    font.loadFromFile("./Resources/Fonts/CyrilicOld.TTF");

    gameBackground.setTexture(gameTableTexture);
    snakeHeadSprite.setTexture(snakeHeadTexture);
    snakePartsSprite.setTexture(snakePartsTexture);
    grayAppleSprite.setTexture(grayAppleTexture);
    greenAppleSprite.setTexture(greenAppleTexture);
    redAppleSprite.setTexture(redAppleTexture);
    menuScrollSprite.setTexture(menuScroll);
    strawberrySprite.setTexture(strawberryTexture);
    pearSprite.setTexture(pearTexture);
    gameOverSprite.setTexture(gameOverTexture);

    redApple->fruitSprite.setTexture(redAppleTexture);
    greenApple->fruitSprite.setTexture(greenAppleTexture);
    grayApple->fruitSprite.setTexture(grayAppleTexture);
    strawberry->fruitSprite.setTexture(strawberryTexture);
    strawberry->setEnding(1);
    pear->fruitSprite.setTexture(pearTexture);
    pear->setEnding(2);


    snakeHeadSprite.setTextureRect(IntRect(260, 65, 64, 64));
}

void SnakeLogic::keyboardPressing() {
    if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) {
        dir = 1;
        snakeHeadSprite.setTextureRect(IntRect(190, 64, 64, 64));
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1){
        dir=2;
        snakeHeadSprite.setTextureRect(IntRect(258, 0, 64, 64));
    }
    if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0) {
        dir = 3;
        snakeHeadSprite.setTextureRect(IntRect(190, 0, 64, 64));
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3){
        dir=0;
        snakeHeadSprite.setTextureRect(IntRect(260, 65, 64, 64));
    }
}

void SnakeLogic::dirWatcher() {
    if (dir == 0) snake.snakePart[0].y += 1;
    if (dir == 1) snake.snakePart[0].x -= 1;
    if (dir == 2) snake.snakePart[0].x += 1;
    if (dir == 3) snake.snakePart[0].y -= 1;
}

void SnakeLogic::drawer() {
    window.clear(Color(93, 131, 255));
    gameBackground.setTextureRect(IntRect(0, 0, 1280, 740));
    window.draw(gameBackground);
    snakeDrawer();
    menuScrollSprite.setPosition(700, -20);
    window.draw(menuScrollSprite);
    scoreText.setPosition(800, 150);
    levelInfo.setPosition(800, 200);
    std::ostringstream totalScore;
    totalScore << score;
    scoreText.setString("Total score : " + totalScore.str());
    fruitCycle();
    window.draw(scoreText);

    window.display();

}

void SnakeLogic::snakeDrawer() {
    for (int i=0;i < snake.getLength();i++) {
        snakeHeadSprite.setPosition(snake.snakePart[0].x*map.getSize(), snake.snakePart[0].y*map.getSize());
        snakePartsSprite.setPosition(snake.snakePart[i].x*map.getSize(), snake.snakePart[i].y*map.getSize());
        if(i == 0) {
            window.draw(snakeHeadSprite);
        } else {
            snakePartsSprite.setTextureRect(IntRect(0, 0, 61, 64));
            window.draw(snakePartsSprite);
        }
    }
}

void SnakeLogic::gameCycle() {
    Clock clock;
    float timer=0, delay=0.1;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        if (timer>delay){
            timer=0;
            snake.tick(snake, rules);
            snake.snakeLogic(map, snake);
            dirWatcher();
        }

        if(rules->isGameOver()) {
            gameOver();
        }

        if(rules->isSadlyEnding() || rules->isHappyEnding()){
            gameEnding();
        }

        window.clear(Color(93, 131, 255));
        keyboardPressing();
        drawer();
    }
}

void SnakeLogic::gameMenu(){
        bool isMenu = true;
        Texture gameStartTexture;
        Texture gameSettingsTexture;
        Texture gameFriendsTexture;
        Texture gameQuitTexture;
        Texture gameMenuBackgroundTexture;

        gameQuitTexture.loadFromFile("./Resources/Images/quitGameButton.png");
        gameFriendsTexture.loadFromFile("./Resources/Images/friendsGameButton.png");
        gameSettingsTexture.loadFromFile("./Resources/Images/settingsGameButton.png");
        gameStartTexture.loadFromFile("./Resources/Images/startGameButton.png");
        gameMenuBackgroundTexture.loadFromFile("./Resources/Images/gameMenuBackground.jpg");

        Sprite startGameButton;
        Sprite settingsGameButton;
        Sprite friendsGameButton;
        Sprite gameQuitButton;
        Sprite gameMenuBackgroundSprite;

        startGameButton.setTexture(gameStartTexture);
        startGameButton.setPosition(200, 0);
        settingsGameButton.setTexture(gameSettingsTexture);
        settingsGameButton.setPosition(200, 200);
        friendsGameButton.setTexture(gameFriendsTexture);
        friendsGameButton.setPosition(200, 400);
        gameQuitButton.setTexture(gameQuitTexture);
        gameQuitButton.setPosition(200, 600);

        gameMenuBackgroundSprite.setTexture(gameMenuBackgroundTexture);
        gameMenuBackgroundSprite.setTextureRect(IntRect(300, 300, 1280, 720));


        Event e;

        while (isMenu) {
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                    break;
                }
            }
            window.draw(gameMenuBackgroundSprite);
            window.draw(startGameButton);
            window.draw(settingsGameButton);
            window.draw(friendsGameButton);
            window.draw(gameQuitButton);

            if (IntRect(200, 0, 515, 200).contains(Mouse::getPosition(window))) {
                startGameButton.setColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    isMenu = false;
                    score = 0;
                    snake.length = 1;
                    snake.snakePart[0].x = 0;
                    snake.snakePart[0].y = 0;
                    rules->setGameOver(false);
                }
            } else {
                startGameButton.setColor(Color::White);
            }
            if (IntRect(200, 200, 515, 200).contains(Mouse::getPosition(window))) {
                settingsGameButton.setColor(Color::Green);
            } else {
                settingsGameButton.setColor(Color::White);
            }
            if (IntRect(200, 400, 515, 200).contains(Mouse::getPosition(window))) {
                friendsGameButton.setColor(Color::Green);
            } else {
                friendsGameButton.setColor(Color::White);
            }
            if (IntRect(200, 600, 515, 200).contains(Mouse::getPosition(window))) {
                gameQuitButton.setColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    window.close();
                }
            } else {
                gameQuitButton.setColor(Color::White);
            }


            window.display();
        }
}

void SnakeLogic::fruitCycle() {
    window.draw(redApple->fruitSprite);
    window.draw(greenApple->fruitSprite);
    window.draw(grayApple->fruitSprite);

    switch(score){
        case 400 ... 500: window.draw(strawberry->fruitSprite); eatFruit(strawberry); break;
        case 501 ... 1000: window.draw(pear->fruitSprite); eatFruit(pear); break;
    }

    eatFruit(redApple);
    eatFruit(grayApple);
    eatFruit(greenApple);
}

void SnakeLogic::eatFruit(Fruit *fruit) {
    if (snake.snakePart[0].x * map.getSize() == fruit->getObjectX() &&
        snake.snakePart[0].y * map.getSize() == fruit->getObjectY()) {
        switch(fruit->getEnding()){
            case 1: rules->setSadlyEnding(true); gameEnding(); break;
            case 2: rules->setHappyEnding(true); gameEnding(); break;
            case 0: break;
            default:break;
        }
        if(fruit->isCorrupt()){
            score -= rand() % 10;
            if(score < 0){
                score = 0;
            }
        } else {
            score += rand() % 10;
        }
        fruit->setRandCoord();
        snake.lengthPlus(snake);
    }
}

void SnakeLogic::gameOver(){

    window.clear();

    while(rules->isGameOver()){
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            gameMenu();
        }

        window.draw(gameBackground);
        window.draw(gameOverSprite);
        window.draw(scoreText);


        window.display();
    }
}

void SnakeLogic::gameEnding() {
        Font font;
        Text goodEnding("", font, 30);
        Texture gameMenuBackgroundTexture;
        gameMenuBackgroundTexture.loadFromFile("./Resources/Images/gameMenuBackground.jpg");
        Sprite gameMenuBackgroundSprite;
        gameMenuBackgroundSprite.setTexture(gameMenuBackgroundTexture);
        gameMenuBackgroundSprite.setTextureRect(IntRect(300, 300, 1280, 720));
        goodEnding.setString("Snake will survived, you take 2 ending!");
        Texture winTexture;
        winTexture.loadFromFile("./Resources/Images/win.png");
        Sprite winSprite;
        winSprite.setTexture(winTexture);
        winSprite.setPosition(320, 200);

        while (rules->isHappyEnding()) {
            window.draw(gameMenuBackgroundSprite);
            window.draw(goodEnding);
            window.draw(winSprite);


            window.display();
            window.clear(Color(255, 110, 50));

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                rules->setHappyEnding(false);
                rules->setSadlyEnding(false);
                gameMenu();
            }

            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                }
            }
        }
        gameMenuBackgroundTexture.loadFromFile("./Resources/Images/gameMenuBackground.jpg");
        poisonTexture.loadFromFile("./Resources/Images/poison.png");
        Sprite poisonSprite(poisonTexture);
        gameMenuBackgroundSprite.setTexture(gameMenuBackgroundTexture);
        gameMenuBackgroundSprite.setTextureRect(IntRect(300, 300, 1280, 720));
        poisonSprite.setPosition(320, 200);

        badEnding.setString("This fruit will be on poisoned, and snake die ;(");

        while (rules->isSadlyEnding()) {
            window.draw(gameMenuBackgroundSprite);
            window.draw(poisonSprite);
            window.draw(badEnding);

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                rules->setHappyEnding(false);
                rules->setSadlyEnding(false);
                gameMenu();
            }

            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                }
            }

            window.display();
            window.clear(Color(255, 110, 50));
        }
}

const Map &SnakeLogic::getMap() const {
    return map;
}

void SnakeLogic::setMap(const Map &map) {
    SnakeLogic::map = map;
}

const Snake &SnakeLogic::getSnake() const {
    return snake;
}

void SnakeLogic::setSnake(const Snake &snake) {
    SnakeLogic::snake = snake;
}

SnakeLogic::~SnakeLogic() {

}
