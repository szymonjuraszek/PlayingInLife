//
// Created by szymo on 3/10/2019.
//
#include <iostream>

#include "Game.h"

using namespace std;

Game::Game() : column(10), row(10) {
    cout<<"Stworzylem plansze o rozmiarze: "<<row<<"x"<<column<<endl;
    board = make_unique<bool[]>(row*column);
    tmpBoard = make_unique<bool[]>(row*column);

}

Game::Game(int row,int column) : column(column), row(row) {
    cout<<"Stworzylem plansze o rozmiarze: "<<row<<"x"<<column<<endl;
    board = make_unique<bool[]>(row*column);
    tmpBoard = make_unique<bool[]>(row*column);
}

void Game::show() {
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            cout<<board[i*row+j]<<" ";
        }
        cout<<endl;
    }
}

void Game::initialize(bool points[]) {
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(points[i*row+j]==true) {
                board[i * row + j] = true;
            }
        }

    }
}

void Game::doOneStepInGame() {
    int indexTableX;
    int indexTableY;
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            int howManyNeighbours=0;
            int x,y;


            // oblicza liczbę sąsiadów komórki [x,y]
            for(x = -1; x < 2; x++)
                for(y = -1; y < 2; y++)
                {
                    indexTableX = i + x;
                    indexTableY = j + y;
                    if(indexTableX<0 || indexTableX>=row || indexTableY<0 || indexTableY>=column){

                    }else {
                        if(((x != 0) || (y != 0)) &&(board.get()[(j + y)+row*(i + x)]==true) ){
                            howManyNeighbours++;
                        }
                    }
                }

            // sprawdza reguły przeżycia komórki lub narodzin nowej
            if(board.get()[i*row+j] == true)    // gdy komórka żywa
            {
                if ((howManyNeighbours == 2) || (howManyNeighbours == 3)) {
                    tmpBoard.get()[i*row+j] = true;
                } else {
                    tmpBoard.get()[i*row+j] = false;
                }
            }
            else  // gdy komórka martwa
            {
                if(howManyNeighbours == 3) {
                    tmpBoard.get()[i*row+j] = true;
                }
                else {
                    tmpBoard.get()[i*row+j] = false;
                }
            }

        }
    }

    // przenosimy *buf do *map
    for(int i = 0; i < row; i++){
        for(int j=0;j<column;j++){
            board.get()[i*row+j]= tmpBoard.get()[i*row+j];
        }
    }


}

// wylicza współrzędną x w obrębie pola gry
int Game::X(int x)
{
    if(x == row) x =  0;
    if(x <  0) x = row-1;
    return x;
}

// wylicza współrzędną y w obrębie pola gry
int Game::Y(int y)
{
    if(y == column) y =  0;
    if(y <  0) y = column-1;
    return y;
}

