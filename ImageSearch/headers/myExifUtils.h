#ifndef MY_EXIF_UTILS_H
#define MY_EXIF_UTILS_H

#include "myStructures.h"


/*
*   EXIFInfo *getExifInfo(const char* filePath) -   a function to read and parse neccesary
*   EXIF information from files to the corresponding structure.
*   
*   const char* filePath - path to the file to be read.
*
*   return type -   EXIFInfo* 
*                   pointer to a structure EXIFInfo
*/
EXIFInfo *getExifInfo(const char* filePath);

#endif