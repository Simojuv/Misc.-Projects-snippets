/*
*File: errorUtils.h
*Author: Simo Oskar Juvanen
*Date Created: 13.04.2020
*Date modified: 13.04.2020
*
*Description: Header file for error handling utilities.
*/
#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H


/*  
*   enum errorType - an enumeration of different error types found in the code.
*   Used to pass different arguments to the error handling function. 
*/
typedef enum errorType{NOARGS,INPUTPATH,INPUTPARAMETER,DIRECTORY,MALLOC,EXIFDATAREAD,EXIFENTRYNEWMODEL,EXIFENTRYNEWDATE,TOGGLEERRORDETAIL,SHOWERRORS,SHOWHELP} errorType;

/*  
*   handleError - a function to handle errors, prints different error messages
*   errorType error - error that needs handling - of type enum errorType.
*   char* specifier - char* to specify additional information about current error.
*   return type - void
*/
void handleError(errorType error, char* specifier);

#endif