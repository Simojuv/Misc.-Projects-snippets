#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include "myStructures.h"


/* 
*   inputParameters* inputParameters_New() - a function to give inputParameters a default value.

*   return type -   inputParameters*
*                   pointer to structure inputParameters
*/
inputParameters* inputParameters_New();

/*
*   inputParameters* handleInputParameters(inputParameters *input, int argc, char* argv[]); -
*   a function to handle the input parameters given to the program.
*   
*   inputParameters *input -    pointer to an inputParameters structure, presumably
*                               with defaulted values using inputParameters_New().
*
*   int argc - number of input variables.
*
*   char* argv[] -  an argument vector that contains the input variables in textual 
*                   representation.
*
*   return type -   inputParameters*
*                   pointer to structure inputParameters
*/
inputParameters* handleInputParameters(inputParameters *input, int argc, char* argv[]);

/*
*   inputParameters* setFolderPath(inputParameters* input, char* inputPath) - 
*   a function to set the correct input folder path value.
*
*   char* inputPath - text representation of the parameter value given.
*
*   return type -   inputParameters*
*                   pointer to structure inputParameters
*/
inputParameters* setFolderPath(inputParameters* input, char* inputPath);

/*
*   inputParameters* setfileName(inputParameters* input, char* inputPath) - 
*   a function to set the correct input file name value.
*
*   char* inputPath - text representation of the parameter value given.
*
*   return type -   inputParameters*
*                   pointer to structure inputParameters
*/
inputParameters* setFileName(inputParameters* input, char* inputPath);

/*
*   inputParameters* setfileName(inputParameters* input, char* inputPath) - 
*   a function to set the correct input camera model value.
*
*   char* inputPath - text representation of the parameter value given.
*
*   return type -   inputParameters*
*                   pointer to structure inputParameters
*/
inputParameters* setCameraModel(inputParameters* input, char* inputPath);

/*
*   inputParameters* setfileName(inputParameters* input, char* inputPath) - 
*   a function to set the correct input capture date value.
*
*   char* inputPath - text representation of the parameter value given.
*
*   return type -   inputParameters*
*                   pointer to structure inputParameters
*/
inputParameters* setCaptureDate(inputParameters* input, char* inputPath);

/*
*   void showHelp() - a function to display help in regards to the usage of the program.
*
*   return type - void
*/
void showHelp();

#endif