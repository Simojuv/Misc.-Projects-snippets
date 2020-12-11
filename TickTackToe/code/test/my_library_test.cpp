#include "my_library.h"

#include <gtest/gtest.h>

TEST(MyLibrary, givenHeightAndWidth_callingGenerateField_mustReturnGeneratedFieldWithHeightAndWidth)
{
    unsigned int inputHeight = 3;
    unsigned int inputWidth = 3;

    Scene expected =
    {
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };

    Scene result = GenerateField(inputHeight,inputWidth);

    ASSERT_EQ(result,expected);
}

TEST(MyLibrary, givenSceneAndCharacterAndDirection_callingPlaceSymbolToField_mustReturnSceneWithPlacedCharacter)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };
    char inputSymbol = 'X';
    Coordinates inputLocation = {5,5};
    GameState inputState = {inputScene,inputLocation,' ',false,false,true};

    Scene expected =
    {
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   | X |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };
    GameState result = PlaceSymbolToField(inputState,inputSymbol);

    ASSERT_EQ(result.scene,expected);
}

TEST(MyLibrary, givenSceneAndCoordinates_callingDeleteCurrentSymbol_mustReturnSceneWithSymbolOnCurrentCoordinatesDeleted)
{
    Coordinates inputLocation = {5,1};
    Scene inputScene =
    {
        {"   |   |   "},
        {"   | X |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };

    GameState inputState = {inputScene,inputLocation,' ',false,false,true};

    Scene expected =
    {
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };

    GameState result = DeleteCurrentSymbol(inputState);

    ASSERT_EQ(result.scene,expected);
}

TEST(MyLibrary, givenSceneAndCoordinates_callingIsEmpty_mustReturnTrue)
{
    Coordinates inputLocation = {5,1};
    Scene inputScene =
    {
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };

    bool result = IsEmpty(inputScene,inputLocation);

    ASSERT_TRUE(result);
}

TEST(MyLibrary, givenSceneAndCoordinates_callingIsEmpty_mustReturnFalse)
{
    Coordinates inputLocation = {5,1};
    Scene inputScene =
    {
        {"   |   |   "},
        {"   | X |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };

    bool result = IsEmpty(inputScene,inputLocation);

    ASSERT_FALSE(result);
}

TEST(MyLibrary, givenCoordinatesAndDirection_callingUpdateCoordinates_mustReturnUpdatedCoordinates)
{
    Coordinates inputCoordinates = {2,5};
    Direction inputDirection = Up;
    Coordinates expected = {2,1};

    Coordinates result = UpdateCoordinates(inputCoordinates,inputDirection);

    ASSERT_EQ(result.X,expected.X);
    ASSERT_EQ(result.Y,expected.Y);
}
TEST(MyLibrary, givenSceneAndCoordinates_callingBoundsCheck_mustReturnFalse)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {"   | X | O "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   | O |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" O | X |   "},
        {"   |   |   "},
    };
    Coordinates inputCoordinates = {13,5};

    bool result = BoundsCheck(inputScene,inputCoordinates);

    ASSERT_FALSE(result);
}
TEST(MyLibrary, givenSceneAndCoordinates_callingBoundsCheck_mustReturnTrue)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {"   | X | O "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   | O |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" O | X |   "},
        {"   |   |   "},
    };
    Coordinates inputCoordinates = {9,5};

    bool result = BoundsCheck(inputScene,inputCoordinates);

    ASSERT_TRUE(result);
}
TEST(MyLibrary, givenGameStateAndWinLength_callingCheckStrikeAtPos_mustReturnWinTrueTieFalsePlayingFalse)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {"   | X | X "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" X | X | O "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" X | O | O "},
        {"   |   |   "},
    };
    Coordinates inputCoord = {9,1};
    GameState inputState = {inputScene,inputCoord,'X',false, false,true};
    unsigned int winLength = 3;

    GameState result = CheckStrikeAtPos(inputState,winLength);

    ASSERT_TRUE(result.win);
    ASSERT_FALSE(result.tie);
    ASSERT_FALSE(result.playing);
}
TEST(MyLibrary, givenSceneAndWinLength_callingCheckStrikeAtPos_mustReturnWinFalseTieFalsePlayingTrue)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {"   | X | X "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" X | X | O "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" X | O | O "},
        {"   |   |   "},
    };
    Coordinates inputCoord = {5,1};
    GameState inputState = {inputScene,inputCoord,'X',false, false,true};
    unsigned int winLength = 3;

    GameState result = CheckStrikeAtPos(inputState,winLength);

    ASSERT_FALSE(result.win);
    ASSERT_FALSE(result.tie);
    ASSERT_TRUE(result.playing);
}
TEST(MyLibrary, givenGameStateAndDirection_callingMoveMarker_mustReturnSceneWithUpdatedMarkerLocation)
{
    Scene inputScene1 =
    {
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   | _ |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };
    Scene inputScene2 =
    {
        {"   |   |   "},
        {"   | X |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   | _ |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };
    Coordinates inputCoord1 = {5,5};
    Coordinates inputCoord2 = {5,5};
    Direction inputDir = Up;

    GameState inputState1 = {inputScene1,inputCoord1,'X',false,false,true};
    GameState inputState2 = {inputScene2,inputCoord2,'X',false,false,true};

    Scene expected1 =
    {
        {"   |   |   "},
        {"   | _ |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };
    Scene expected2 =
    {
        {"   |   |   "},
        {"   | X |   "},
        {"   | _ |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {"   |   |   "},
        {"   |   |   "},
    };

    GameState result1 = MoveMarker(inputState1,inputDir);
    GameState result2 = MoveMarker(inputState2,inputDir);

    ASSERT_EQ(result1.scene,expected1);
    ASSERT_EQ(result2.scene,expected2);
}

TEST(MyLibrary,givenGameStateAndWinLength_callingCheckStrikeAtAllPos_mustReturnTieTrueWinFalsePlayingFalse)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {" O | X | X "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" X | X | O "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" O | O | X "},
        {"   |   |   "},
    };
    Coordinates inputCoord = {9,1};
    GameState inputState = {inputScene,inputCoord,'X',false, false,true};
    unsigned int winLength = 3;

    GameState result = CheckStrikeAtAllPos(inputState,winLength);

    ASSERT_TRUE(result.tie);
    ASSERT_FALSE(result.win);
    ASSERT_FALSE(result.playing);
}

TEST(MyLibrary,givenGameStateAndWinLength_callingCheckStrikeAtALlPos_mustReturnPlayingTrueWinFalseTieFalse)
{
    Scene inputScene =
    {
        {"   |   |   "},
        {" O | X | X "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" X |   | O "},
        {"   |   |   "},
        {"-----------"},
        {"   |   |   "},
        {" O | O | X "},
        {"   |   |   "},
    };
    Coordinates inputCoord = {9,1};
    GameState inputState = {inputScene,inputCoord,'O',false, false,true};
    unsigned int winLength = 3;

    GameState result = CheckStrikeAtAllPos(inputState,winLength);

    ASSERT_TRUE(result.playing);
    ASSERT_FALSE(result.tie);
    ASSERT_FALSE(result.win);
}
