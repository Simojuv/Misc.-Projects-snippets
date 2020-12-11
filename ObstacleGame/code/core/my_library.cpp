#include "my_library.h"
#include <algorithm>
#include <windows.h>
#include <conio.h>


Scene CreateScene(unsigned int numberOfObstacles, unsigned int height, unsigned int width)
{
    Scene myScene = GenerateField(numberOfObstacles,height,width);
    myScene = PlacePlayer(myScene);
    myScene = PlaceExit(myScene);

    return myScene;
}
Scene GenerateField(unsigned int numberOfObstacles, unsigned int height, unsigned int width)
{
    std::vector<std::string> myField (height,std::string(width,'.'));
    unsigned int obstaclesPlaced = 0;

    while(obstaclesPlaced < numberOfObstacles)
    {
        unsigned int xCoordinate = static_cast<unsigned int>(rand()) % width;
        unsigned int yCoordinate = static_cast<unsigned int>(rand()) % height;
        if(myField.at(yCoordinate).at(xCoordinate) == '.')
        {
            myField.at(yCoordinate).at(xCoordinate) = 'T';
            obstaclesPlaced += 1;
        }
    }
    return myField;
}
Scene PlacePlayer(Scene& field)
{
    bool playerPlaced = false;
    unsigned long long height = field.size();
    unsigned long long width = field.at(0).size();
    while(!playerPlaced)
    {
        unsigned int xCoordinate = static_cast<unsigned int>(rand()) % width;
        unsigned int yCoordinate = static_cast<unsigned int>(rand()) % height;
        if(field.at(yCoordinate).at(xCoordinate) == '.')
        {
            field.at(yCoordinate).at(xCoordinate) = 'G';
            playerPlaced = true;
        }
    }
    return field;
}
Scene PlaceExit(Scene& field)
{
    bool exitPlaced = false;
    unsigned long long height = field.size();
    unsigned long long width = field.at(0).size();
    while(!exitPlaced)
    {
        unsigned int xCoordinate = static_cast<unsigned int>(rand()) % width;
        unsigned int yCoordinate = static_cast<unsigned int>(rand()) % height;
        if(field.at(yCoordinate).at(xCoordinate) == '.')
        {
            field.at(yCoordinate).at(xCoordinate) = 'X';
            exitPlaced = true;
        }
    }
    return field;
}
Coordinates GetCoordinates(const Scene& scene,char searchChar)
{
    Coordinates position;
    unsigned long index = 0;
    for(unsigned int i = 0; i< scene.size();i++)
    {
        auto find = std::find(scene.at(i).begin(),scene.at(i).end(),searchChar);
        if(find != scene.at(i).end())
        {
            index = static_cast<unsigned long>(std::distance(scene.at(i).begin(),find));
            position.X = index;
            position.Y = i;
            return position;
        }
    }
    position = {0,0};
    return position;
}

Coordinates UpdateCoordinates(Coordinates& givenCoord, Direction direction)
{
    Coordinates newCoord = givenCoord;
    switch(direction){
    case(Up): newCoord.Y = newCoord.Y-1; break;
    case(Left): newCoord.X = newCoord.X-1; break;
    case(Right): newCoord.X = newCoord.X+1; break;
    case(Down): newCoord.Y = newCoord.Y+1; break;
    case(None): break;
    }
    return newCoord;
}
bool BoundsCheck(const Scene& scene, Coordinates coord)
{
    if(coord.Y >= scene.size() || coord.X >= scene.at(0).size()) return false;
    else return true;
}

State WinLoseCondition(const Scene& scene, Direction direction)
{
    Coordinates currentPlayerPosition = GetCoordinates(scene,'G');
    Coordinates newPlayerPosition = UpdateCoordinates(currentPlayerPosition,direction);
    if(!BoundsCheck(scene,newPlayerPosition)) return OutOfBounds;
    Coordinates exitPosition  = GetCoordinates(scene,'X');
    if(newPlayerPosition.X == exitPosition.X && newPlayerPosition.Y == exitPosition.Y) return Win;
    else if(scene.at(newPlayerPosition.Y).at(newPlayerPosition.X) == 'T') return Lose;
    else return EmptyCell;
}

Scene UpdateScene(Scene& scene, Direction direction)
{
    Scene newScene = scene;
    Coordinates currentPlayerPosition = GetCoordinates(scene,'G');
    Coordinates newPlayerPosition = UpdateCoordinates(currentPlayerPosition,direction);
    if(!BoundsCheck(scene,newPlayerPosition)) return scene;
    else
    {
        newScene.at(currentPlayerPosition.Y).at(currentPlayerPosition.X) = '.';
        newScene.at(newPlayerPosition.Y).at(newPlayerPosition.X)= 'G';
    }
    return newScene;
}

GameState Play(Scene& scene, Direction direction)
{
    GameState currentState = {scene, false, true};
    State nextState = WinLoseCondition(scene,direction);
    switch(nextState){
    case(Win):
        currentState.isPlaying = false;
        currentState.isLose = false;
        break;
    case(Lose):
        currentState.isPlaying = false;
        currentState.isLose = true;
        break;
    case(OutOfBounds):
        return currentState;
    case(EmptyCell):
        currentState.scene = UpdateScene(scene,direction);
    }
    return currentState;
}
bool CheckWinPath(const Scene& scene,Scene visited, Coordinates currentPlayerLocation)
{
    visited.at(currentPlayerLocation.Y).at(currentPlayerLocation.X) = '1';
    if (scene.at(currentPlayerLocation.Y).at(currentPlayerLocation.X) == 'X')
    {
        return true;
    }
    else
    {
        for(int dir = Up; dir != None;++dir)
        {
            Direction tempDir = static_cast<Direction>(dir);
            Coordinates newPlayerLocation = UpdateCoordinates(currentPlayerLocation,tempDir);
            if(BoundsCheck(scene,newPlayerLocation) && scene.at(newPlayerLocation.Y).at(newPlayerLocation.X) !='T' && visited.at(newPlayerLocation.Y).at(newPlayerLocation.X) != '1')
            {
                if(CheckWinPath(scene,visited,newPlayerLocation)) return true;
            }
        }
    }
    visited.at(currentPlayerLocation.Y).at(currentPlayerLocation.X) = ' ';
    return false;
}

void Print2DVector(const Scene& field)
{
    for (auto row: field)
    {
        std::cout << row << "\n";
    }
    ResetCursor();
}
Direction getKey()
{
    if(_getch() == 224)
    {
        int temp = _getch();
        switch(temp){
        case(72): return Up;
        case(75): return Left;
        case(77): return Right;
        case(80): return Down;
        }
    }
    return None;
}
void ResetCursor()
{
    COORD startCoord = {0,0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console,startCoord);
}

void SetConsoleCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(console,&cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(console,&cursorInfo);
}

void Loop(unsigned int numberOfObstacles, unsigned int height, unsigned int width)
{
    Direction direction;
    SetConsoleCursor();

    Scene myScene;
    Scene visitedScene (height,std::string(width,' '));
    do{
        std::fill(visitedScene.begin(),visitedScene.end(),std::string(width,' '));
        myScene = CreateScene(numberOfObstacles,height,width);
      }while(!CheckWinPath(myScene,visitedScene,GetCoordinates(myScene,'G')));

    Print2DVector(myScene);
    GameState currentState = {myScene,false,true};
    while(currentState.isPlaying != false)
    {
        direction = getKey();
        if(direction != None)
        {
            currentState = Play(currentState.scene,direction);
            Print2DVector(currentState.scene);
        }
    }
    if(currentState.isLose) std::cout << "You lost!" << std::endl;
    else std::cout << "You Won!"<< std::endl;
}
