#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;
RenderWindow window(VideoMode(1280, 720), "Snake Game!");

int Weight=10, Height=10;
int size=64;
int w = size*Weight;
int h = size*Height;

int dir,num=4;

struct Snake {
    int x,y;
}  snake[100];


class snakeLogic{
public:
    void control() {
        if (snake[0].x > Weight) snake[0].x = 0;
        if (snake[0].x < 0) snake[0].x = Weight;
        if (snake[0].y > Height) snake[0].y = 0;
        if (snake[0].y < 0) snake[0].y = Height;

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
public:
    Fruits() {
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
        }
    }
};

int main()
{
    srand(time(0));
    snakeLogic logic;
    Fruits whiteApple;
    Fruits greenApple;

    Texture gameTableTexture;
    Texture snakeHeadTexture;
    Texture redAppleTexture;
    Texture greenAppleTexture;
    Texture snakePartsTexture;

    gameTableTexture.loadFromFile("../Images/background.jpg");
    snakeHeadTexture.loadFromFile("../images/snake.png");
    snakePartsTexture.loadFromFile("../Images/snake.png");
    redAppleTexture.loadFromFile("../Images/appleRed.png");
    greenAppleTexture.loadFromFile("../Images/appleGreen.png");


    Sprite gameBackground(gameTableTexture);
    Sprite snakeHeadSprite(snakeHeadTexture);
    Sprite snakePartsSprite(snakePartsTexture);
    Sprite redAppleSprite(redAppleTexture);
    Sprite greenAppleSprite(greenAppleTexture);

    snakeHeadSprite.setTextureRect(IntRect(250, 0, 64, 64));


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
            if (e.type == Event::Closed)
                window.close();
        }
                                                                            // Наши нажатия на клавиши
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            dir = 1;
            snakeHeadSprite.setTextureRect(IntRect(190, 64, 64, 64));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            dir=2;
            snakeHeadSprite.setTextureRect(IntRect(258, 0, 64, 64));
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            dir = 3;
            snakeHeadSprite.setTextureRect(IntRect(190, 0, 64, 64));
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)){
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

                gameBackground.setTextureRect(IntRect(0, 0, 740, 720));
                window.draw(gameBackground);

        for (int i=0;i<num;i++) {
            snakeHeadSprite.setPosition(snake[0].x*size, snake[0].y*size);
            snakePartsSprite.setPosition(snake[i].x*size, snake[i].y*size);
            if(i == 0) {
                window.draw(snakeHeadSprite);
            } else {
                snakePartsSprite.setTextureRect(IntRect(60, 0, 64, 64));
                window.draw(snakePartsSprite);
            }
        }


            whiteApple.spawnFruits(redAppleSprite);
            greenApple.spawnFruits(greenAppleSprite);




            window.display();
    }

    return 0;
}