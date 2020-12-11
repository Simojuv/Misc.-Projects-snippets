#ifndef MY_STRUCTURES_H
#define MY_STRUCTURES_H

/*
*   struct captureDate -    a simple structure to hold
*                           the date values in integer form. 
*/
typedef struct captureDate
{
    int day;
    int month;
    int year;
}captureDate;


/*
*   JPEGList - a structure to hold the data for every
*   image that matched with the search criteria.
*   
*   char* fileName -    file name;.
*   char* filePath -    path to the file.
*                       *can be both relative or absolute.
*
*   char* cameraModel -     camera model from the exif metadata.
*
*   captureDate *origDate - original capture date from
*                           the exif metadata.
*
*   struct JPEGList *pNext -    pointer to the next element
*                               in the linked list.
*/
typedef struct JPEGList
 {
    char* fileName;
    char* filePath;
    char* cameraModel;
    captureDate *origDate;
    struct JPEGList *pNext;
 }JPEGList;


/*
*   struct EXIFInfo -   a structure to hold only 
*                       the required exif data.
*
*   char* model -   camera model name.
*
*   captureDate *dateInfo -     original capture date.
*/

typedef struct EXIFInfo
{
    char* model;
    captureDate *dateInfo;
}EXIFInfo;

/*
*   struct inputParameters - a structure to hold all the input variables.
*
*   char* inputFolderPath - search folder path.
*                           *can be both relative or absolute.
*
*   char* inputFileName - input file name.
*
*   struct captureDate *inputDate - input capture date.
*
*   char* inputCameraModel - input camera model.
*/

typedef struct inputParameters
{
    char* inputFolderPath;
    char* inputFileName;
    struct captureDate *inputDate;
    char* inputCameraModel;
}inputParameters;


/*
*   struct formatParameters -   a simple structure to hold values for 
*                               ease of formating.
*
*   int maxFileNameWidth - maximum file name length in search matches.
*   
*   int maxModelNameWidth - maxiumum camera model name length in search matches.
*/
typedef struct formatParameters
{
    int maxFileNameWidth;
    int maxModelNameWidth;
}formatParameters;

#endif