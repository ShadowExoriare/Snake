#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "map.h"
using namespace sf;

CircleShape shape(50);

struct pos{
    int x;
    int y;
};

class PlayerSnake{
public:
   float x, y, w, h, dx, dy, speed;
    int dir = 0;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    PlayerSnake(String F, int X, int Y, float W, float H){
        File = F;
        w = W;
        h = H;
        image.loadFromFile("../Images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    void update(float time){
        switch (dir){
            case 0: dx = speed; dy = 0;
                break;
            case 1: dx = -speed; dy = 0;
                break;
            case 2: dx = 0; dy = speed;
                break;
            case 3: dx = 0; dy = -speed;
                break;
        }
        x+= dx*time;
        y+= dy*time;

        sprite.setPosition(x, y);
    }

};

int main(){
    RenderWindow window(VideoMode(640, 480), "Snake");
    Clock clock;
    PlayerSnake player("snake.png", 250, 250, 60, 60);

    Image mapimage;
    mapimage.loadFromFile("../Images/map.png");
    Texture map;
    map.loadFromImage(mapimage);
    Sprite mapsprite;
    mapsprite.setTexture(map);

    while(window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }

        if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))){
            player.dir = 1;
            player.speed = 0.1;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))){
            player.dir = 0;
            player.speed = 0.1;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))){
            player.dir = 2;
            player.speed = 0.1;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))){
            player.dir = 3;
            player.speed = 0.1;
        }
        player.update(time);

        window.clear(Color(102, 153, 255));

        for(int i = 0; i < HEIGHT_MAP; i++){
            for(int j = 0; j < WIDTH_MAP; j++){
                if(TileMap[i][j] == ' ') mapsprite.setTextureRect(IntRect(0, 0, 32, 32));
                if(TileMap[i][j] == 's') mapsprite.setTextureRect(IntRect(32, 0, 32, 32));
                if(TileMap[i][j] == '0') mapsprite.setTextureRect(IntRect(64, 0, 32, 32));

                mapsprite.setPosition(j * 32, i * 32);

                window.draw(mapsprite);
            }
        }
        window.draw(player.sprite);
        window.display();

    }

    return 0;
}