#include <iostream>
#include "my_library.h"

int main()
{
    unsigned int winLength = 3;
    Coordinates startingPosition = {5,5};
    Scene myField = GenerateField(5,5);
    GameState currentState = {myField,startingPosition,'X',false,false,true};
    currentState = PlaceSymbolToField(currentState,'_');

    SetConsole(currentState.scene);
    Print2DVector(currentState.scene);
    while(currentState.playing)
    {
        Direction dir = GetKey();
        if(dir !=None)
        {
            currentState = CheckState(currentState,dir,winLength);
            Print2DVector(currentState.scene);
        }
    }
    SetCursorPos(currentState);
    if(currentState.tie) std::cout << "Its a tie!   ";
    else if(currentState.win && currentState.CurrentSymbol == 'O') std::cout << "'O' Wins!  ";
    else std::cout << "'X' Wins!    ";
}
