#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>



#include "Game.h"

struct BadBoard{
public:
    void displayComunicat(string comunicat){
        cout<<comunicat<<endl;
    }
};

using namespace std;

void riskFunction(int tmpPointX,int tmpPointY,int row,int column);

int main() {
    srand( time( NULL ) );

    int row,column;
    cout<<"--------------------------Playing in life-----------------------"<<endl;
    cout<<"Podaj liczbe wierszy: "<<endl;
    cin>>row;
    cout<<"Podaj licze kolumn: "<<endl;
    cin>>column;

    unique_ptr<Game> gameOfLife(new Game(row,column));

    int ifAccepted;
    cout<<"Czy chcesz samemu wybrac punkty startowe [1] lub [0]"<<endl;
    cin>>ifAccepted;

    bool pointsToInit[row*column];
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            pointsToInit[i*row+j]=false;
        }
        cout<<endl;
    }


    if(ifAccepted==1){
        int numberOfPoints;
        int tmpPointX;
        int tmpPointY;

        cout<<"Ile chcesz dodac punktow?"<<endl;
        cin>>numberOfPoints;

        for(int i=0;i<numberOfPoints;i++){
            try {
                cout << "Podaj wsp X" << endl;
                cin >> tmpPointX;
                cout << "Podaj wsp Y" << endl;
                cin >> tmpPointY;
                riskFunction(tmpPointX,tmpPointY,row,column);
                pointsToInit[(tmpPointX-1)*row + (tmpPointY-1)]=true;
            }catch(BadBoard error){
                error.displayComunicat("Podano liczbe z poza przedialu");
            }

        }
    }else{
        int numberOfPoints=(row*column)/6;
    for(int i=0; i < numberOfPoints; i++){
            int positionPoint =( rand() % (row*column) ) + 0;
            cout<<"position: "<<positionPoint<<endl;
            pointsToInit[positionPoint] = true;
        }
    }

    gameOfLife.get()->initialize(pointsToInit);
    gameOfLife.get()->show();

    cout<<"Rozpoczynam gre"<<endl;
    for(int i=0;i<10;i++){
        gameOfLife.get()->doOneStepInGame();
        cout<<"------------------------------------------------------------------------------"<<endl;
        gameOfLife.get()->show();
    }

    return 0;
}

void riskFunction(int tmpPointX,int tmpPointY,int row,int column){
    if(tmpPointX<1 || tmpPointX >row || tmpPointY<1 || tmpPointY>column){
        BadBoard kapsula;
        throw kapsula;
    }
}