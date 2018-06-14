//
// Created by black on 14.06.2018.
//

#ifndef SNAKE_GAMERULES_H
#define SNAKE_GAMERULES_H


class GameRules {
    bool gameOver;
    bool happyEnding;
    bool sadlyEnding;
public:
    bool isGameOver() const;

    void setGameOver(bool gameOver);

    bool isHappyEnding() const;

    void setHappyEnding(bool happyEnding);

    bool isSadlyEnding() const;

    void setSadlyEnding(bool sadlyEnding);

};


#endif //SNAKE_GAMERULES_H
