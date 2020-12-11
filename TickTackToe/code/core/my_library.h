#pragma once

#include <iostream>
#include <vector>
using Scene = std::vector<std::string>;

enum Direction {Up, Left, Down, Right,UpLeft,UpRight,DownLeft,DownRight,None,Place};
struct Coordinates{
    unsigned long X;
    unsigned long Y;
};
struct GameState
{
    Scene scene;
    Coordinates currentPos;
    char CurrentSymbol;
    bool win;
    bool tie;
    bool playing;
};

Scene GenerateField(unsigned int height, unsigned int width);
GameState PlaceSymbolToField(GameState& state, char symbol);
GameState DeleteCurrentSymbol(GameState& state);
bool IsEmpty(const Scene& field, Coordinates location);
Coordinates UpdateCoordinates(Coordinates& coord,Direction direction);
GameState MoveMarker(GameState& state, Direction direction);
Coordinates MoveCursorToNextPlace(const Scene& scene, Coordinates& position);
GameState CheckStrikeAtPos(GameState& state, unsigned int winLength);
GameState CheckStrikeAtAllPos(GameState& state,unsigned int winLength);
GameState CheckState(GameState& state,Direction direction, unsigned int winLength);
bool BoundsCheck(const Scene& scene, Coordinates location);


Direction GetKey();
void ResetCursor();
void SetConsole(const Scene& field);
void ClearConsole();
void Print2DVector(const Scene& field);
void SetCursorPos(GameState& state);
