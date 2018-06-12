#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include "level.h"
#include <list>
#include <string>
using namespace sf;
RenderWindow window(VideoMode(1280, 720), "Snake Game!");

int Weight=10, Height=10;
int size=64;
int score = 0;
Font font;
bool gameEndingBad;
bool gameEndingGood;

int dir,num=4;

struct Snake {
    int x,y;
}  snake[100];


int randScore() {
    return rand() % 10;
}

class snakeLogic{
public:
    void control() {
        if (snake[0].x > Weight) {
            snake[0].x = 0;
        }
        if (snake[0].x < 0){
            snake[0].x = Weight;
        }
        if (snake[0].y > Height) {
            snake[0].y = 0;
        }
        if (snake[0].y < 0) {
            snake[0].y = Height;
        }

        for (int i = 1; i < num; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                num = i;
        }
    }
    void keyboardControl(){

        if (dir==0) snake[0].y+=1;
        if (dir==1) snake[0].x-=1;
        if (dir==2) snake[0].x+=1;
        if (dir==3) snake[0].y-=1;
    }
    void Tick() {
        for (int i=num;i>0;--i) {
            snake[i].x=snake[i-1].x;
            snake[i].y=snake[i-1].y;
        }
        keyboardControl();
        control();
    }
};

class Fruits{
private:
    int objectX;
    int objectY;
    std::string fruitType;
public:
    Fruits(std::string fruit) {
        fruitType = fruit;
        objectX = rand() % Weight * size;
        objectY = rand() % Height * size;
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
        if (snake[0].x * size == getObjectX() && snake[0].y * size == getObjectY()) {
            num++;
            setObjectX(rand() % Weight * size);
            setObjectY(rand() % Height * size);
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
    snakeLogic logic;
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
            logic.Tick();
        }
                                                                            //Отрисовка
        window.clear(Color(93, 131, 255));

                gameBackground.setTextureRect(IntRect(0, 0, 1280, 740));
                window.draw(gameBackground);

        for (int i=0;i<num;i++) {
            snakeHeadSprite.setPosition(snake[0].x*size, snake[0].y*size);
            snakePartsSprite.setPosition(snake[i].x*size, snake[i].y*size);
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

        if(score >= 400 && num > 10) {
            strawberry.spawnFruits(strawberrySprite);
        }

        if(score >= 500 && num > 15){
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

            std::ostringstream currentLevel;
            currentLevel << getCurrentLevel(score);

            std::ostringstream textLevel;
            textLevel << getTextLevel(score);


            scoreText.setString("Total score : " + totalScore.str());

            levelInfo.setString("Level : " + currentLevel.str() + "\n " + " Info: " + textLevel.str() + "\n");

            window.draw(menuScrollSprite);

            window.draw(scoreText);
            window.draw(levelInfo);

        window.display();
    }

    return 0;
}