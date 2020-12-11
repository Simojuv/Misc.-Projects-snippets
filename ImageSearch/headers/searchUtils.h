#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H

#include "myStructures.h"
#include <dirent.h>
#include <stdbool.h>

// enumeration to choose between file path and folder path
typedef enum choosePath{FILEPATH,FOLDERPATH} choosePath;

/*
*   DIR* openFolder(const char* folderPath) - a function to open directories.
*   
*   const char* folderPath - path to target directory.
*
*   return type -   DIR*
*                   pointer to a DIR structure.
*                   NULL if cannot open target directory.
*/
DIR* openFolder(const char* folderPath);

/*
*   getNewPath(const char* folderPath,char* newFolder,choosePath path) - a function
*   to concatenate a new folder or file path.
*
*   const char* folderPath -    current folder path.
*
*   char* newFolder -   path of the next folder or to the currentl inspected file.
*
*   return type - char*
*/
char* getNewPath(const char* folderPath,char* newFolder,choosePath path);


/*
*   filterString(const char* str1, const char* str2) - a string comparison function
*   with asterisk * wildcard support.
*
*   const char* str1 and str2 -     strings to compare
*
*   return type -   bool
*                   true if strings are equal with * support
*                   false if strings are different
*/
bool filterString(const char* str1, const char* str2);

/*
*   compareDate(captureDate* date1, captureDate* date2) - function to compare 
*   two captureDate structures between each other.
*
*   captureDate* date1 and date2 -  captureDate structures to be compared
*
*   return type -   bool
*                   true if dates are exactly matched
*                   false if dates don't match
*/
bool compareDate(captureDate* date1, captureDate* date2);

/*
*   filterCurrentFile(inputParameters* input, const char* fileName,EXIFInfo *exifInfo) - 
*   a function to filter files against input data.
*
*   inputParameters* input -    search input parameters.
*
*   const char* fileName -  current file to be filtered.
*
*   EXIFInfo *exifInfo -    exif data recieved from the file (fileName).
*
*   return type -   bool
*                   true if the file data matches input criteria
*                   false if the file data does not match input criteria
*/
bool filterCurrentFile(inputParameters* input, const char* fileName,EXIFInfo *exifInfo);

/*
*   searchFolder(JPEGList *imgList,char* folderPath,inputParameters* input) -
*   a function that searches given folder for all jpeg files. The main program
*   functionality is in this function
*   
*   JPEGList *imgList -     the JPEGList structure to be filled with matching image data.
*
*   char* folderPath -  folder to be searched.
*
*   inputParameters* input -    search input parameters.
*
*   return type -       JPEGList*
*                       pointer to the linked list JPEGList structure that
*                       contains all of the required JPEG image data
*/
JPEGList* searchFolder(JPEGList *imgList,char* folderPath,inputParameters* input);
/*
*   addImage(JPEGList *imgList, char* fileName,char* filePath,EXIFInfo *exifInfo) -
*   a function to add elements to the JPEGList structure.
*
*   JPEGList *imgList -     current JPEGList structure pointer.
*
*   char* fileName -    new file name to add.
*
*   char* filePath -    new file path to add.
*                       *mainly for debugging purposes and 
*                        detailed error messages
*
*   EXIFInfo *exifInfo - neccesary exif data fields of the file.
*
*   return type -   JPEGList*
*                   pointer to the first element of the updated JPEGList
*/
JPEGList* addImage(JPEGList *imgList, char* fileName,char* filePath,EXIFInfo *exifInfo);

#endif