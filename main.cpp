#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include "map.h"
#include "view.h"
using namespace sf;

CircleShape shape(50);

struct pos{
    int x;
    int y;
};

class PlayerSnake{
private:
    float x = 0;
    float y = 0;

public:
   float w, h, dx, dy, speed;
    int dir = 0;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    int playerScore;

    PlayerSnake(String F, int X, int Y, float W, float H){
        File = F;
        w = W;
        h = H;
        image.loadFromFile("../Images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(190, 0, w, h));
        playerScore = 0;
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
        mapRules();
    }

    float getPlayerCoordinateX(){
        return x;
    }
    float getPlayerCoordinateY(){
        return y;
    }

    void mapRules(){
        for(int i = y / 32; i < (y + h) / 32; i++){
            for(int j = x / 32; j < (x + w) / 32; j++){
                if(TileMap[i][j] == '0'){
                    if(dy > 0){
                        y = i * 32 - h;
                    }
                    if(dy < 0){
                        y = i * 32 + 32;
                    }
                    if(dx > 0){
                        x = j * 32 - w;
                    }
                    if(dx < 0){
                        x = j * 32 + 32;
                    }
                }
                if(TileMap[i][j] == 's'){
                    TileMap[i][j] = ' ';
                    playerScore++;
                }
            }
        }
    }

};

int main(){
    RenderWindow window(VideoMode(640, 480), "Snake");
    view.reset(FloatRect(0, 0, 640, 480));

    Clock clock;
    PlayerSnake player("snake.png", 200, 200, 65, 65);

    Font font;
    font.loadFromFile("../Images/CyrilicOld.TTF");
    Text text(" ", font, 20);
    text.setColor(Color::Green);
    text.setStyle(Text::Bold);

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
            player.sprite.setTextureRect(IntRect(190, 64, 65, 64));
        }
        if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))){
            player.dir = 0;
            player.speed = 0.1;
            player.sprite.setTextureRect(IntRect(260, 0, 70, 64));
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))){
            player.dir = 2;
            player.speed = 0.1;
            player.sprite.setTextureRect(IntRect(260, 65, 65, 65));
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))){
            player.dir = 3;
            player.speed = 0.1;
            player.sprite.setTextureRect(IntRect(190, 0, 65, 65));
        }
        getPlayerCoordinateView(player.getPlayerCoordinateX(), player.getPlayerCoordinateY());

        player.update(time);

        window.setView(view);
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
        std::ostringstream playerScoreString;
        playerScoreString << player.playerScore;
        text.setString("Player score:" + playerScoreString.str());
        text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
        window.draw(text);

        window.draw(player.sprite);
        window.display();

    }

    return 0;
}