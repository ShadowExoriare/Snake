
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>

using namespace std;
int gameOver = true;

enum motion{
    STOP = 0, UP, DOWN, LEFT, RIGHT
};

int width = 20;
int height = 20;
int x = width / 2;
int y = height / 2;
int fruitX = rand() % width;
int fruitY = rand() % height;
int snakeSteps = 0;
int gameScore = 0;

class gameFruits{
public:
    void greenApple(){
        cout << "g" << endl;
    }
    void orangeApple(){
        cout << "o" << endl;
    }
    void poisonApple(){
        cout << "p" << endl;
    }
    void blockApple(){
        cout << "x" << endl;
    }

};

class settings{
public:

    motion move;
    void inputKeys(){
        if(_kbhit()){
            switch (getch()){
                case 'a':
                    move = LEFT;
                    break;
                case 'd':
                    move = RIGHT;
                    break;
                case 'w':
                    move = UP;
                    break;
                case 's':
                    move = DOWN;
                    break;
                case 'x': gameOver = true;

            }
        }
    }

};

class gameMenu{
private:
    void printLimiter(){
        cout << "=============================" << endl;
    }
public:
    void printMenu() {
        int choice;
        printLimiter();
        cout << "1: New Game" << endl;
        cout << "2: Show last result" << endl;
        cout << "3: Exit game" << endl;
        printLimiter();
        cin >> choice;
        playerChoice(choice);
    }
    void playerChoice(int choice) {
        switch(choice){
            case 1: gameOver = false; break;
            case 2: cout << "vasya ti ne prav";
            case 3: return; break;
            default:return;
        }
    }
};

class Draw : settings {
public:

    void drawGame() {
        system("cls");
        for (int i = 0; i < width + 1; i++) {
            cout << "#";
        }
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width) {
                    cout << "#";
                }
                if(i == y && j == x) {
                    snakeHead();
                }
                else if(i == fruitY && j == fruitX){
                    gameFruits fruits;
                    fruits.greenApple();
                }
                drawSpace();
            }
            cout << endl;
        }

        for (int i = 0; i < width + 1; i++) {
            cout << "#";
        }
        cout << endl;

        cout << "/n" << snakeSteps;
        cout << gameScore;

    }

    void snakeHead() {
        cout << "0";
    }

    void drawSpace(){
        cout << " ";
    }

    void inputControl(){
    }

};

class Logical : settings {
public:
    void buttonInput() {
        inputKeys();
        switch (move) {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
        }

        if(move){
            snakeSteps++;
        }
    }
};

    class gameCycle : Logical {
    public:
        Draw drawGame;

        void game() {
            while (!gameOver) {
                drawGame.drawGame();
                buttonInput();
            }
        }

    };

    int main() {
        setlocale(LC_ALL, "Russian");
        gameMenu menu;
        gameCycle gameCycle;

        menu.printMenu();
        gameCycle.game();
        return 0;
    }