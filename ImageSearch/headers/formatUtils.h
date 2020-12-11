#ifndef FORMAT_UTILS_H
#define FORMAT_UTILS_H

#include "myStructures.h"

/*  
*   void print(JPEGList *imgList) - a function to print the contents of structure JPEGList,
*                              starting from pointer.
*
*   JPEGList *imgList - a pointer to an element of
*                       the linked list structure JPEGList.
*
*   return type - void
*/
void print(JPEGList *imgList);

/*  
*   formatParameters *getFormatParameters(JPEGList* imgList) - an utility function to help
*   simplify the format for print function.
*
*   JPEGList *imgList - a pointer to an element of
*                       the linked list structure JPEGList.
*
*   return type -   formatParameters*
*                   pointer to structure formatParameters.
*/
formatParameters *getFormatParameters(JPEGList* imgList);

#endif