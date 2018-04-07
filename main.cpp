#include <SFML/Graphics.hpp>
#include <time.h>
#include "Pojo.h"
using namespace sf;

int Weight=30, Height=20;
int size=20;
int w = size*Weight;
int h = size*Height;

int dir,num=4;

struct Snake
{ int x,y;}  snake[100];


class snakeControl{
public:
    void control() {
        if (snake[0].x > Weight) snake[0].x = 0;
        if (snake[0].x < 0) snake[0].x = Weight;
        if (snake[0].y > Height) snake[0].y = 0;
        if (snake[0].y < 0) snake[0].y = Height;

        for (int i = 1; i < num; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) num = i;
        }
    }
    void keyboardControl(){

        if (dir==0) snake[0].y+=1;
        if (dir==1) snake[0].x-=1;
        if (dir==2) snake[0].x+=1;
        if (dir==3) snake[0].y-=1;
    }
};

class Rules : snakeControl{
private:
    int fruitsX;
    int fruitsY;
    int difficultyLevel = 3;
public:
    int getDifficultyLevel() const {
        return difficultyLevel;
    }

    void setDifficultyLevel(int difficultyLevel) {
        Rules::difficultyLevel = difficultyLevel;
    }

    int getFruitsX() const {
        return fruitsX;
    }

    void setFruitsX(int fruitsX) {
        Rules::fruitsX = fruitsX;
    }

    int getFruitsY() const {
        return fruitsY;
    }

    void setFruitsY(int fruitsY) {
        Rules::fruitsY = fruitsY;
    }

    Rules(){
        fruitsX = getFruitsX();
        fruitsY = getFruitsY();
    }


    void Tick() {
        for (int i=num;i>0;--i) {
            snake[i].x=snake[i-1].x;
            snake[i].y=snake[i-1].y;
        }

        keyboardControl();
        randomizeFruits();
        control();

    }

    void randomizeFruits(){
        if ((snake[0].x == getFruitsX()) && (snake[0].y == getFruitsY())) {
            num++;
            setFruitsX(rand() % Weight);
            setFruitsY(rand() % Height);
        }
    }
};

class GreenApple : Rules{
private:
    GreenApple(){
        randomizeFruits();
    }
};

int main()
{
    srand(time(0));
    Rules rules;
    Rules greenApple;
    Rules redApple;

    RenderWindow window(VideoMode(1280, 720), "Snake Game!");

    Texture gameTableTexture;
    Texture snakeTexture;
    Texture borderMap;
    Texture redAppleTexture;
    Texture greenAppleTexture;
    gameTableTexture.loadFromFile("../Images/map.png");
    snakeTexture.loadFromFile("../images/green.png");
    borderMap.loadFromFile("../Images/map.png");
    redAppleTexture.loadFromFile("../Images/red.png");
    greenAppleTexture.loadFromFile("../Images/green.png");


    Sprite gameBackground(gameTableTexture);
    Sprite snakeSprite(snakeTexture);
    Sprite gameBorderSprite(gameBorderSprite);
    Sprite redAppleSprite(redAppleTexture);
    Sprite greenAppleSprite(greenAppleSprite);

    Clock clock;
    float timer=0, delay=0.1;

    rules.setFruitsX(10);
    rules.setFruitsY(10);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;
        if (Keyboard::isKeyPressed(Keyboard::Right))  dir=2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;
                                                                                //Скорость игры, таймер
        if (timer>delay){
            timer=0;
            rules.Tick();
        }
                                                                            //Отрисовка
        window.clear(Color(93, 131, 255));

        for (int i=0; i<Weight + 1; i++)
            for (int j=0; j<Height + 1; j++) {
                gameBackground.setPosition(i*size,j*size);
                gameBackground.setTextureRect(IntRect(0, 0, 24, 24));
                window.draw(gameBackground);
            }

        for (int i=0;i<num;i++) {
            snakeSprite.setPosition(snake[i].x*size, snake[i].y*size);
            snakeSprite.setTextureRect(IntRect(0, 0, 16, 16));
            window.draw(snakeSprite);
        }

            redAppleSprite.setPosition(rules.getFruitsX() * size, rules.getFruitsY() * size);
            window.draw(redAppleSprite);




            window.display();
    }

    return 0;
}