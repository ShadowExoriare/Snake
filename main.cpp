#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include "Snake.h"
#include "Map.h"
#include <list>
#include <string>
using namespace sf;
RenderWindow window(VideoMode(1280, 720), "Snake Game!");

int score = 0;
Font font;
bool gameEndingBad;
bool gameEndingGood;

int dir;

Snake snake;
Map map;

int randScore() {
    return rand() % 10;
}


void keyboardControl(){

    if (dir==0) snake.snakePart[0].y+=1;
    if (dir==1) snake.snakePart[0].x-=1;
    if (dir==2) snake.snakePart[0].x+=1;
    if (dir==3) snake.snakePart[0].y-=1;
}

class Fruits{
private:
    int objectX;
    int objectY;
    std::string fruitType;
public:
    Fruits(std::string fruit) {
        fruitType = fruit;
        objectX = rand() % map.getWeight() * map.getSize();
        objectY = rand() % map.getHeight() * map.getSize();
    }

    int getObjectX() const {
        return objectX;
    }

    void setObjectX(int objectX) {
        Fruits::objectX = objectX;
    }

    int getObjectY() const {
        return objectY;
    }

    void setObjectY(int objectY) {
        Fruits::objectY = objectY;
    }

    void setFruitType(const std::string &fruitType) {
        Fruits::fruitType = fruitType;
    }

    const std::string &getFruitType() const {
        return fruitType;
    }

    void spawnFruits(Sprite objectSprite) {
        objectSprite.setPosition(getObjectX(), getObjectY());
        window.draw(objectSprite);
        eatFruits();
    }

    void eatFruits() {
        if (snake.snakePart[0].x * map.getSize() == getObjectX() && snake.snakePart[0].y * map.getSize() == getObjectY()) {
            snake.lengthPlus(snake);
            setObjectX(rand() % map.getWeight() * map.getSize());
            setObjectY(rand() % map.getHeight() * map.getSize());
            if(getFruitType() == "bad") {
                playerPunish();
            }

            if(getFruitType() == "good"){
                playerReward();
            }

            if(getFruitType() == "badEnding"){
                gameEndingBad = true;
            }
            if(getFruitType() == "goodEnding"){
                gameEndingGood = true;
            }
        }
    }


    void playerPunish() {
        score -= randScore() * 5;
        if(score < 0) {
            score = 0;
        }
    }

    void playerReward(){
        score += randScore();
    }
};

    void menu() {
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
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                isMenu = false;
            }
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
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
            window.clear(Color(255, 110, 50));
        }
    }



void goodEnding() {
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

    while(gameEndingGood) {
        window.draw(gameMenuBackgroundSprite);
        window.draw(goodEnding);
        window.draw(winSprite);


        window.display();
        window.clear(Color(255, 110, 50));

        if(Keyboard::isKeyPressed(Keyboard::Space)){
            gameEndingGood = false;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
    }
}

void badEnding() {
    Text badEnding("", font, 30);
    Texture gameMenuBackgroundTexture;
    Texture poisonTexture;
    gameMenuBackgroundTexture.loadFromFile("./Resources/Images/gameMenuBackground.jpg");
    poisonTexture.loadFromFile("./Resources/Images/poison.png");
    Sprite gameMenuBackgroundSprite;
    Sprite poisonSprite(poisonTexture);
    gameMenuBackgroundSprite.setTexture(gameMenuBackgroundTexture);
    gameMenuBackgroundSprite.setTextureRect(IntRect(300, 300, 1280, 720));
    poisonSprite.setPosition(320, 200);

    badEnding.setString("This fruit will be on poisoned, and snake die ;(");

    while(gameEndingBad) {

        window.draw(gameMenuBackgroundSprite);
        window.draw(poisonSprite);
        window.draw(badEnding);

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            gameEndingBad = false;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    font.loadFromFile("./Resources/Fonts/CyrilicOld.TTF");
    srand(time(0));
    menu();
    Text scoreText("", font, 50);
    Text levelInfo("", font, 30);
    Fruits redApple("good");
    Fruits greenApple("good");
    Fruits grayApple("bad");
    Fruits strawberry("badEnding");
    Fruits pear("goodEnding");

    Texture gameTableTexture;
    Texture snakeHeadTexture;
    Texture redAppleTexture;
    Texture grayAppleTexture;
    Texture greenAppleTexture;
    Texture snakePartsTexture;
    Texture menuScroll;
    Texture strawberryTexture;
    Texture pearTexture;

    gameTableTexture.loadFromFile("./Resources/Images/background.png");
    snakeHeadTexture.loadFromFile("./Resources/images/snake.png");
    snakePartsTexture.loadFromFile("./Resources/Images/snakePart.png");
    redAppleTexture.loadFromFile("./Resources/Images/appleRed.png");
    greenAppleTexture.loadFromFile("./Resources/Images/appleGreen.png");
    grayAppleTexture.loadFromFile("./Resources/Images/appleGray.png");
    menuScroll.loadFromFile("./Resources/Images/gameScroll.png");
    strawberryTexture.loadFromFile("./Resources/Images/strawberry.png");
    pearTexture.loadFromFile("./Resources/Images/pear.png");


    Sprite gameBackground(gameTableTexture);
    Sprite snakeHeadSprite(snakeHeadTexture);
    Sprite snakePartsSprite(snakePartsTexture);
    Sprite redAppleSprite(redAppleTexture);
    Sprite grayAppleSprite(grayAppleTexture);
    Sprite greenAppleSprite(greenAppleTexture);
    Sprite menuScrollSprite(menuScroll);
    Sprite strawberrySprite(strawberryTexture);
    Sprite pearSprite(pearTexture);

    snakeHeadSprite.setTextureRect(IntRect(260, 65, 64, 64));


    bool showTextLevel = false;
    Clock clock;
    float timer=0, delay=0.1;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

                                                                            // На случай, если захотим выйти
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
                                                                            // Наши нажатия на клавиши
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
                                                                                //Скорость игры, таймер, делаем перемещение змейки плавным
        if (timer>delay){
            timer=0;
            snake.tick(snake);
            snake.snakeLogic(map, snake);
            keyboardControl();
        }
                                                                            //Отрисовка
        window.clear(Color(93, 131, 255));

                gameBackground.setTextureRect(IntRect(0, 0, 1280, 740));
                window.draw(gameBackground);

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


        redApple.spawnFruits(redAppleSprite);
        greenApple.spawnFruits(greenAppleSprite);
        grayApple.spawnFruits(grayAppleSprite);

        if(score >= 400 && snake.getLength() > 10) {
            strawberry.spawnFruits(strawberrySprite);
        }

        if(score >= 500 && snake.getLength() > 15){
            pear.spawnFruits(pearSprite);
        }

        if(gameEndingGood){
            goodEnding();
            break;
        }
        if(gameEndingBad){
            badEnding();
            break;
        }


            menuScrollSprite.setPosition(700, -20);

            scoreText.setPosition(800, 150);
            levelInfo.setPosition(800, 200);

            std::ostringstream totalScore;
            totalScore << score;


            scoreText.setString("Total score : " + totalScore.str());

            window.draw(menuScrollSprite);

            window.draw(scoreText);
            window.draw(levelInfo);

        window.display();
    }

    return 0;
}