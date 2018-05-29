//
// Created by black on 29.05.2018.
//
int getCurrentLevel(int score){
    int level = 0;
    switch(score){
        case 0 ... 100: level = 1; break;
        case 101 ... 200: level = 2; break;
        case 201 ... 300: level = 3; break;
        case 301 ... 1000: level = 4; break;
    }
    return level;
}
std::string getTextLevel(int score){
    std::string textLevel = "";

    switch (score){
        case 0 ... 100: textLevel = "Start of the game. \n Collect 100 scores for continue! \n Remember: don't take gray apples! \n"; break;
        case 101 ... 200: textLevel = "Collect 200 apples! \n"; break;
        case 201 ... 300: textLevel = "Hard way to 300 score! \n"; break;
        case 301 ... 1000: textLevel = "Easter level. You need to search easter egg! \n"; break;
        default:break;
    }
    return textLevel;

}

#ifndef SNAKE_LEVEL_H
#define SNAKE_LEVEL_H

#endif //SNAKE_LEVEL_H
