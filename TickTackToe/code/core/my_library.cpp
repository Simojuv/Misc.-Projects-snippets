#include "my_library.h"
#include <windows.h>
#include <conio.h>

Scene GenerateField(unsigned int height, unsigned int width)
{
    unsigned int yHeight = height*3 + height-1;
    unsigned int xWidth = width*3 + width-1;
    Scene myField (yHeight,std::string(xWidth,' '));

    for(unsigned int i = 1; i<=yHeight;i++)
    {
        if(i%4 == 0) myField.at(i-1) = std::string(xWidth,'-');
        else
        {
            for(unsigned int j = 3; j <xWidth; j = j+4)
            {
                myField.at(i-1).at(j) = '|';
            }
        }
    }
    return myField;
}
GameState PlaceSymbolToField(GameState& state, char symbol)
{
    if(IsEmpty(state.scene, state.currentPos)) state.scene.at(state.currentPos.Y).at(state.currentPos.X) = symbol;
    return state;
}
GameState DeleteCurrentSymbol(GameState& state)
{
    state.scene.at(state.currentPos.Y).at(state.currentPos.X) = ' ';
    return state;
}
bool IsEmpty(const Scene& field, Coordinates location)
{
    if(field.at(location.Y).at(location.X) == ' ' || field.at(location.Y).at(location.X) == '_') return true;
    else return false;
}
Coordinates UpdateCoordinates(Coordinates& coord,Direction direction)
{
    switch(direction){
    case(Up): coord.Y = coord.Y-4; break;
    case(Left): coord.X = coord.X-4; break;
    case(Down): coord.Y = coord.Y+4; break;
    case(Right): coord.X = coord.X+4; break;
    case(UpLeft): coord.Y = coord.Y-4; coord.X = coord.X-4; break;
    case(UpRight): coord.Y = coord.Y-4; coord.X = coord.X+4; break;
    case(DownLeft): coord.Y = coord.Y+4; coord.X = coord.X-4; break;
    case(DownRight): coord.Y = coord.Y+4; coord.X = coord.X+4; break;
    case(None): break;
    case(Place): break;
    }
    return coord;
}

GameState MoveMarker(GameState& state, Direction direction)
{
    Coordinates startPos = state.currentPos;
    if(IsEmpty(state.scene,state.currentPos)) state = DeleteCurrentSymbol(state);
    else
    {
        state.currentPos.Y +=1;
        state = DeleteCurrentSymbol(state);
        state.currentPos.Y -=1;
    }

    state.currentPos = UpdateCoordinates(state.currentPos, direction);
    if(!BoundsCheck(state.scene,state.currentPos)) state.currentPos = startPos;

    if(IsEmpty(state.scene,state.currentPos)) state = PlaceSymbolToField(state,'_');
    else
    {
        state.currentPos.Y +=1;
        state = PlaceSymbolToField(state,'_');
        state.currentPos.Y -=1;
    }
    return state;
}

Coordinates MoveCursorToNextPlace(const Scene& scene, Coordinates& position)
{
    Coordinates startPos = position;
    position = UpdateCoordinates(position,Right);
    if(!BoundsCheck(scene,position))
    {
        position.X = 1;
        position = UpdateCoordinates(position,Down);
        if(!BoundsCheck(scene,position)) return startPos;
    }
    return position;
}

GameState CheckStrikeAtPos(GameState& state, unsigned int winLength)
{
    Coordinates startPos = state.currentPos;
    unsigned int tempCount = 0;
    char symbol = state.CurrentSymbol;
    for(int dir = Up; dir != None; dir++)
    {
       Direction tempDir = static_cast<Direction>(dir);
       while(BoundsCheck(state.scene,state.currentPos))
       {
           if(state.scene.at(state.currentPos.Y).at(state.currentPos.X) == symbol) tempCount +=1;
           else if (state.scene.at(state.currentPos.Y).at(state.currentPos.X) != symbol ) break;
           if(tempCount == winLength)
           {
               state.win = true;
               state.playing = false;
               return state;
           }
           state.currentPos = UpdateCoordinates(state.currentPos,tempDir);
       }
       state.currentPos = startPos;
       tempCount = 0;
    }
    return state;
}

GameState CheckStrikeAtAllPos(GameState& state,unsigned int winLength)
{
    Coordinates startPosition = state.currentPos;
    Coordinates tempPosition = {1,1};
    unsigned int countTie = 1;
    unsigned long long height = (state.scene.size()+1) / 4;
    unsigned long long width = (state.scene.at(0).size()+1)/4;
    for(unsigned int i = 1; i < height*width; i++)
    {
        state.currentPos = tempPosition;
        if(!IsEmpty(state.scene, tempPosition))
        {
            state = CheckStrikeAtPos(state,winLength);
            countTie +=1;
        }
        if(state.win) return state;
        tempPosition = MoveCursorToNextPlace(state.scene,tempPosition);
    }
    if(countTie == height*width)
    {
        state.tie = true;
        state.playing = false;
    }
    state.currentPos = startPosition;
    return state;
}

GameState CheckState(GameState& state,Direction direction, unsigned int winLength)
{
    if (direction == Place)
    {
        state = PlaceSymbolToField(state,state.CurrentSymbol);
        state = CheckStrikeAtAllPos(state,winLength);
        if(state.playing)
        {
            if(state.CurrentSymbol == 'X') state.CurrentSymbol = 'O';
            else if(state.CurrentSymbol == 'O') state.CurrentSymbol = 'X';
        }
    }
    else if(direction == Up) state = MoveMarker(state,Up);
    else if(direction == Left) state = MoveMarker(state,Left);
    else if(direction == Right) state = MoveMarker(state,Right);
    else if(direction == Down) state = MoveMarker(state,Down);

    return state;
}
bool BoundsCheck(const Scene& scene, Coordinates location)
{
    if(location.Y >= scene.size() || location.X >= scene.at(0).size()) return false;
    else return true;
}


Direction GetKey()
{
    int key = _getch();
    if(key == 224)
    {
        int temp = _getch();
        switch(temp){
        case(72): return Up;
        case(75): return Left;
        case(77): return Right;
        case(80): return Down;
        }
    }
    else if (key == 32) return Place;
    return None;
}
void ResetCursor()
{
    COORD startCoord = {0,0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console,startCoord);
};

void SetCursorPos(GameState& state)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    short xCoord = static_cast<short>(state.scene.at(0).size() + 2);
    COORD textCoord = {xCoord,2};

    SetConsoleCursorPosition(console,textCoord);
}
void SetConsole(const Scene& field)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console,&csbi);
    GetConsoleCursorInfo(console,&cursorInfo);
    cursorInfo.bVisible = false;

    SMALL_RECT rect = csbi.srWindow;
    COORD newSize;

    newSize.X = csbi.dwSize.X;
    newSize.Y = static_cast<short>(field.size())+1;
    rect.Bottom = static_cast<short>(newSize.Y-1);

    SetConsoleCursorInfo(console,&cursorInfo);
    SetConsoleScreenBufferSize(console,newSize);
    SetConsoleWindowInfo(console,TRUE,&rect);

}
void Print2DVector(const Scene& field)
{
    for (auto line: field) std::cout << line << "\n";
    ResetCursor();
}
