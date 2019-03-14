//
// Created by szymo on 3/10/2019.
//

#ifndef PLAYING_IN_LIFE_GAME_H
#define PLAYING_IN_LIFE_GAME_H

#include <memory>

using namespace std;


class Game {
private:
    const int row;
    const int column;
    unique_ptr<bool[]> board;
    unique_ptr<bool[]> tmpBoard;

    int X(int x);
    int Y(int y);
public:
    Game();
    Game(int row,int column);
    void show();
    void initialize(bool points[]);
    void doOneStepInGame();
};


#endif //PLAYING_IN_LIFE_GAME_H
