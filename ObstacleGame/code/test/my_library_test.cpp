#include "my_library.h"

#include <gtest/gtest.h>
using Scene = std::vector<std::string>;

unsigned int GetNumberOfObstacles(Scene& myScene)
{
    unsigned int obstacles = 0;
    for(auto row: myScene) obstacles += count(row.begin(),row.end(),'T');
    return obstacles;
}
unsigned int GetNumberOfEmptyCells(Scene& myScene)
{
    unsigned int empty = 0;
    for(auto row: myScene) empty += count(row.begin(),row.end(),'.');
    return empty;
}
bool IsOnePlayerInScene(Scene& myScene)
{
    int player = 0;
    for(auto row: myScene) player += count(row.begin(),row.end(),'G');
    if(player == 1) return true;
    else return false;
}
bool IsOneExitInScene(Scene& myScene)
{
    int exit = 0;
    for(auto row: myScene) exit += count(row.begin(),row.end(),'X');
    if(exit == 1) return true;
    else return false;
}
TEST(MyLibrary, givenThreeUnsignedIntegers_callingGenerateField_mustReturnFieldWithGivenHeightWidthAndNumberOfObstacles) {
    // ARRANGE
    unsigned int inputNumberOfObstacles = 50;
    unsigned int inputHeight = 20;
    unsigned int inputWidth = 20;
    unsigned int emptyCells = inputWidth*inputHeight-inputNumberOfObstacles;

    // ACT
    Scene result = GenerateField(inputNumberOfObstacles,inputHeight,inputWidth);

    // ASSERT
    ASSERT_EQ(result.size(), 20);
    ASSERT_EQ(result.at(0).size(),20);
    ASSERT_EQ(GetNumberOfObstacles(result),50);
    ASSERT_EQ(GetNumberOfEmptyCells(result),emptyCells);
}

TEST(MyLibrary, givenVectorOfStrings_callingPlacePlayer_mustReturnVectorOfStringsWithPlayerMarker)
{
    unsigned int inputNumberOfObstacles = 50;
    unsigned int inputHeight = 20;
    unsigned int inputWidth = 20;
    unsigned int emptyCells = inputWidth*inputHeight-inputNumberOfObstacles-1;

    Scene generatedScene = GenerateField(inputNumberOfObstacles,inputHeight,inputWidth);
    generatedScene = PlacePlayer(generatedScene);

    ASSERT_EQ(GetNumberOfObstacles(generatedScene),50);
    ASSERT_EQ(GetNumberOfEmptyCells(generatedScene),emptyCells);
    ASSERT_TRUE(IsOnePlayerInScene(generatedScene));

}

TEST(MyLibrary,givenVectorOfStrings_CallingPlaceExit_MustReturnVectorOfStringsWithExitMarker)
{
    unsigned int inputNumberOfObstacles = 50;
    unsigned int inputHeight = 20;
    unsigned int inputWidth = 20;
    unsigned int emptyCells = inputWidth*inputHeight-inputNumberOfObstacles-1;

    Scene generatedScene = GenerateField(inputNumberOfObstacles,inputHeight,inputWidth);
    generatedScene = PlaceExit(generatedScene);

    ASSERT_EQ(GetNumberOfObstacles(generatedScene),inputNumberOfObstacles);
    ASSERT_EQ(GetNumberOfEmptyCells(generatedScene),emptyCells);
    ASSERT_TRUE(IsOneExitInScene(generatedScene));
}

TEST(MyLibrary,givenVectorOfStringsAndEnum_callingWinLoseCondition_mustReturnEmptyCellIfNextToEmptyCellInDirection)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T...GT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };

    Direction inputDirectionLeft = Left;

    int result1Left = WinLoseCondition(inputScene1,inputDirectionLeft);

    ASSERT_EQ(result1Left,EmptyCell);
}
TEST(MyLibrary,givenVectorOfStringsAndEnum_callingWinLoseCondition_mustReturnWinIfNextToExitInDirection)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T...GT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };

    Direction inputDirectionLeft = Down;

    int result1Left = WinLoseCondition(inputScene1,inputDirectionLeft);

    ASSERT_EQ(result1Left,Win);
}
TEST(MyLibrary,givenVectorOfStringsAndEnum_callingWinLoseCondition_mustReturnLoseIfNextToObstacleInDirection)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T...GT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };

    Direction inputDirectionLeft = Right;

    int result1Left = WinLoseCondition(inputScene1,inputDirectionLeft);

    ASSERT_EQ(result1Left,Lose);
}
TEST(MyLibrary,givenVectorOfStringsAndEnum_callingWinLoseCondition_mustReturnOutOfBoundsIfOutOfBoundsInDirection)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T...GT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };

    Direction inputDirectionLeft = Up;

    int result1Left = WinLoseCondition(inputScene1,inputDirectionLeft);

    ASSERT_EQ(result1Left,OutOfBounds);
}

TEST(MyLibrary,givenVectorOfStringsAndEnum_callingUpdateScene_MustReturnVectorOfstringsWithUpdatedPlayerMarkerLocation)
{
    Scene currentScene = {
        {"TT....T.T..T.T..GTT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Scene expectedLeft = {
        {"TT....T.T..T.T.G.TT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Scene expectedUp = {
        {"TT....T.T..T.T..GTT."},
        {".T.T...T..T....T.X.."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };

    Direction inputDirectionUp = Up;
    Direction inputDirectionLeft = Left;

    Scene moveLeft = UpdateScene(currentScene,inputDirectionLeft);
    Scene moveUp = UpdateScene(currentScene, inputDirectionUp);

    ASSERT_EQ(moveLeft,expectedLeft);
    ASSERT_EQ(moveUp,expectedUp);
}

TEST(MyLibrary,givenVectorOfStringsAndDirection_callingPlay_mustReturnCurrentScene)
{
    Scene currentScene = {
        {"TT....T.T..T.T..GTT."},
        {".T.T...T..T....TX..."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Direction inputDirection = Up;

    GameState result = Play(currentScene,inputDirection);

    ASSERT_EQ(result.scene,currentScene);
}

TEST(MyLibrary,givenVectorOfStringsAndDirection_callingPlay_mustReturnIsPlayingFalseAndIsLoseTrue)
{
    Scene currentScene = {
        {"TT....T.T..T.T..GTT."},
        {".T.T...T..T....TX..."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Direction inputDirection = Right;

    GameState result = Play(currentScene,inputDirection);

    ASSERT_FALSE(result.isPlaying);
    ASSERT_TRUE(result.isLose);
}
TEST(MyLibrary,givenVectorOfStringsAndDirection_callingPlay_mustReturnIsPlayingFalseAndIsLoseFalse)
{
    Scene currentScene = {
        {"TT....T.T..T.T..GTT."},
        {".T.T...T..T....TX..."},
        {"....T...T........T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Direction inputDirection = Down;

    GameState result = Play(currentScene,inputDirection);

    ASSERT_FALSE(result.isPlaying);
    ASSERT_FALSE(result.isLose);
}

TEST(MyLibrary, givenVectorOfStringsAndChar_callingGetCoordinates_mustReturnCoordinatesofChar)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T..GTT."},
        {".T.T...T..T....T...."},
        {"....T...TX.......T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Coordinates expectedG = {16,0};
    Coordinates expectedK = {0,0};

    Coordinates resultG = GetCoordinates(inputScene1,'G');
    Coordinates resultK = GetCoordinates(inputScene1,'K');

    ASSERT_EQ(expectedG.X, resultG.X);
    ASSERT_EQ(expectedG.Y, resultG.Y);

    ASSERT_EQ(expectedK.X,resultK.X);
    ASSERT_EQ(expectedK.Y, resultK.Y);
}
TEST(MyLibrary, givenCoordinatesAndDirection_callingUpdateCoordinate_mustReturnCoordinatesUpdatedWithDirection)
{
    Coordinates inputCoordinates1 = {10,2};
    Coordinates inputCoordinates2 = {1,1};
    Direction inputDirection1 = Up;
    Direction inputDirection2 = Left;
    Coordinates expected1 = {10,1};
    Coordinates expected2 = {0,1};

    Coordinates result1 = UpdateCoordinates(inputCoordinates1,inputDirection1);
    Coordinates result2 = UpdateCoordinates(inputCoordinates2,inputDirection2);

    ASSERT_EQ(expected1.X,result1.X);
    ASSERT_EQ(expected1.Y,result1.Y);
    ASSERT_EQ(expected2.X,result2.X);
    ASSERT_EQ(expected2.Y,result2.Y);
}
TEST(MyLibrary, givenVectorOfStringsAndCoordinates_callingBoundsCheck_mustReturnTrueIfCoordinatesAreInBoundsOfVector)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T....T."},
        {".T.T...T..T....T...."},
        {"....T...TXG......T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };
    Coordinates inputCoordinates1 = {1,25};
    Coordinates inputCoordinates2 = {18,0};

    bool result1 = BoundsCheck(inputScene1,inputCoordinates1);
    bool result2 = BoundsCheck(inputScene1,inputCoordinates2);

    ASSERT_FALSE(result1);
    ASSERT_TRUE(result2);
}
TEST(MyLibrary, givenVectorOfstrings_callingCheckWinPath_mustReturnTrueIfPathFromPlayerToExitExists)
{
    Scene inputScene1 = {
        {"TT....T.T..T.T..G.T."},
        {".T.T...T..T....T...."},
        {"....T...TX.......T.."},
        {"..T....T..T....T...."},
        {".....T......T......."},
    };

    Scene inputScene2 = {
        {"TT....T.T..T.T....T."},
        {".T.T.G.T..T....T...."},
        {"....T...TX.......T.."},
        {"..T...TT..T....T...."},
        {".....T......T......."},
    };
    Scene visited1 = {
        {"                    "},
        {"                    "},
        {"                    "},
        {"                    "},
        {"                    "},
    };
    Scene visited2 = {
        {"                    "},
        {"                    "},
        {"                    "},
        {"                    "},
        {"                    "},
    };

    Coordinates playerLocation1 = GetCoordinates(inputScene1,'G');
    Coordinates playerLocation2 = GetCoordinates(inputScene2,'G');

    bool path1 = CheckWinPath(inputScene1,visited1,playerLocation1);
    bool path2 = CheckWinPath(inputScene2,visited2,playerLocation2);

    ASSERT_TRUE(path1);
    ASSERT_FALSE(path2);
}
