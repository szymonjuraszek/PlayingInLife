#include <iostream>
#include <memory>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <string>
#include <queue>


#include "Game.h"

struct BadBoard{
public:
    void displayStatement(string statement){
        cout<<statement<<endl;
    }
};

using namespace std;

void riskFunction(int tmpPointX,int tmpPointY,int row,int column);
queue<int> readStartingDataFromFile();
queue<int> putDataYourself(int row,int column);

int main() {
    srand( time( NULL ) );

    int row,column;
    int answer;
    cout<<"--------------------------Playing in life-----------------------"<<endl;
    cout<<"[1] if you want to read starting data from file or [0] if you want to put data yourself"<<endl;
    cin>>answer;

    queue<int> startingData;
    if(answer==1){
        startingData = readStartingDataFromFile();
        row = startingData.front();
        startingData.pop();
        column = startingData.front();
        startingData.pop();
    }else{
        cout<<"Enter the number of rows: "<<endl;
        cin>>row;
        cout<<"Enter the number of columns: "<<endl;
        cin>>column;
        startingData = putDataYourself(row,column);
    }

    unique_ptr<Game> gameOfLife(new Game(row,column));

    bool pointsToInit[row*column];
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            pointsToInit[i*column+j]=false;

        }

    }


    int indexX,indexY;
    int n = startingData.size();
    for(int i=0;i<n;i=i+2){
        indexX = startingData.front();
        startingData.pop();
        indexY=startingData.front();
        startingData.pop();
        pointsToInit[(indexX-1)*column + (indexY-1)]=true;
    }



    gameOfLife.get()->initialize(pointsToInit);
    gameOfLife.get()->show();

    cout<<"Starting Game"<<endl;
    for(int i=0;i<20;i++){
        gameOfLife.get()->doOneStepInGame();
        cout<<"------------------------------------------------------------------------------"<<endl;
        gameOfLife.get()->show();
    }

    return 0;
}

/******************************************************************************************************************/

void riskFunction(int tmpPointX,int tmpPointY,int row,int column){
    if(tmpPointX<1 || tmpPointX >row || tmpPointY<1 || tmpPointY>column){
        BadBoard kapsula;
        throw kapsula;
    }
}

queue<int> readStartingDataFromFile(){
    string line;
    fstream file;
    queue < int > startingData;

    file.open("C:\\Users\\szymo\\CLionProjects\\Playing-In-Life\\startingData.txt", ios::in);
    if(file.good() == true)
    {
        while(!file.eof())
        {
            getline(file, line);
            int number = atoi(line.c_str());
            startingData.push(number);
        }
        file.close();
    }

    return startingData;

}

queue<int> putDataYourself(int row,int column){

    queue<int> startingData;
    int ifAccepted;
    cout<<"Do you want to put starting points yourself [1] or [0]"<<endl;
    cin>>ifAccepted;

    if(ifAccepted==1){
        int numberOfPoints;
        int tmpPointX;
        int tmpPointY;

        cout<<"How many point do you want to add?"<<endl;
        cin>>numberOfPoints;

        for(int i=0;i<numberOfPoints;i++){
            try {
                cout << "Give coordinate X" << endl;
                cin >> tmpPointX;
                cout << "Give coordinate Y" << endl;
                cin >> tmpPointY;
                riskFunction(tmpPointX,tmpPointY,row,column);

                startingData.push(tmpPointX);
                startingData.push(tmpPointY);
            }catch(BadBoard error){
                error.displayStatement("Number from outside the range!");
            }

        }
    }else{
        int numberOfPoints=(row*column)/6;
        int positionPointX,positionPointY;
        for(int i=0; i < numberOfPoints; i++){
            positionPointX =( rand() % (row) ) + 1;
            positionPointY =( rand() % (column) ) + 1;
            startingData.push(positionPointX);
            startingData.push(positionPointY);
        }
    }

    return startingData;
}