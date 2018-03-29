#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <SFML/Graphics.hpp>


using namespace std;

class Menu{
public:
    void setParameters(){
    }
};Menu menu;

using namespace std;
class GameDraw{
private:
    int x = 0;
    int y = 0;

public:
    void mapDraw() {
    }
};GameDraw gameDraw;

class gameCycle{
public:
    void configureGame(){
        menu.setParameters();
    }

    void snakeGameCycle() {
            sf::RenderWindow window(sf::VideoMode(200, 200), "Lesson 1. kychka-pc.ru");
        }
};gameCycle game;


int main(){
    game.configureGame();
    game.snakeGameCycle();

    getch();
    return 0;
}