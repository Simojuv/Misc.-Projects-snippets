#pragma once
#include <iostream>
#include <vector>


using Scene = std::vector<std::string>;

struct Coordinates
{
    unsigned long X;
    unsigned long Y;
};

struct GameState
{
    Scene scene;
    bool isLose;
    bool isPlaying;
};

enum Direction { Up, Left, Right, Down, None};
enum State { Win, Lose, OutOfBounds,EmptyCell };

Scene CreateScene(unsigned int numberOfObstacles, unsigned int height, unsigned int width);
Scene GenerateField(unsigned int numberOfObstacles, unsigned int height, unsigned int width);
Scene PlacePlayer(Scene& field);
Scene PlaceExit(Scene& field);
bool CheckWinPath(const Scene& scene,Scene visited, Coordinates currentPlayerLocation);


Coordinates GetCoordinates(const Scene& scene,char searchChar);
bool BoundsCheck(const Scene& scene,Coordinates coord);
Coordinates UpdateCoordinates(Coordinates& givenCoord, Direction direction);
State WinLoseCondition(const Scene& scene, Direction direction);
Scene UpdateScene(Scene& scene, Direction direction);
GameState Play(Scene& scene, Direction direction);

void Print2DVector(const Scene& field);
Direction getKey();
void ResetCursor();
void Loop(unsigned int numberOfObstacles, unsigned int height, unsigned int width);
