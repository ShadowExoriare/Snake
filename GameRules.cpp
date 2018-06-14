//
// Created by black on 14.06.2018.
//

#include "GameRules.h"

bool GameRules::isGameOver() const {
    return gameOver;
}

void GameRules::setGameOver(bool gameOver) {
    GameRules::gameOver = gameOver;
}

bool GameRules::isHappyEnding() const {
    return happyEnding;
}

void GameRules::setHappyEnding(bool happyEnding) {
    GameRules::happyEnding = happyEnding;
}

bool GameRules::isSadlyEnding() const {
    return sadlyEnding;
}

void GameRules::setSadlyEnding(bool sadlyEnding) {
    GameRules::sadlyEnding = sadlyEnding;
}
