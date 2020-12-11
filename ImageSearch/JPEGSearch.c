/*
*File: JPEGSearch.c
*Author: Simo Oskar Juvanen
*Date Created: 11.04.2020
*Date modified: 13.04.2020
*
*Description: Console line utility that searches for JPEG files in a folder and its subfolders.
*Then displays found files with their Capture Date and Camera Model.
*/

#include "headers/myStructures.h"
#include "headers/errorUtils.h"
#include "headers/formatUtils.h"
#include "headers/inputUtils.h"
#include "headers/myExifUtils.h"
#include "headers/searchUtils.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct JPEGList *myImageList = NULL;
    
    // Getting input parameters
    struct inputParameters *myInputs = inputParameters_New();
    
    // Parsing input parameters
    myInputs = handleInputParameters(myInputs,argc,argv);

    // Executing the search and constructing a linked list of correct matches
    myImageList = searchFolder(myImageList, myInputs->inputFolderPath,myInputs);

    // Printing resulted errors
    handleError(SHOWERRORS,NULL);
    // Printing the result of the search
    print(myImageList);
    exit(0);
}

