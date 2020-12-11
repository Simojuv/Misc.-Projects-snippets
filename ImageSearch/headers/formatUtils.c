#include "formatUtils.h"
#include "errorUtils.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Escape sequence macros - used to display
// different colors of text in the console.
#define KYEL  "\x1B[33m"
#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"

void print(JPEGList *imgList)
{
    struct JPEGList *oTemp = imgList;
    struct formatParameters *param = getFormatParameters(imgList);
    // printing column headers
    if(oTemp){
    printf("%-*s    %10s     Camera model\n",param->maxFileNameWidth,"File Name","Date taken");
    }
    else fprintf(stderr,"No specified JPEG files found\nUse parameter -detailed for error information\n");
    while(oTemp != NULL)
    {
        printf("%-*s    ",param->maxFileNameWidth,oTemp->fileName);
        if(oTemp->origDate) 
        {
            if(oTemp->origDate->year) printf("%d ",oTemp->origDate->year);
            if(oTemp->origDate->month) printf("%2d ",oTemp->origDate->month);
            if(oTemp->origDate->day) printf("%2d     ",oTemp->origDate->day);
        }
        else printf("not found      ");
        if(oTemp->cameraModel)printf("%-*s",param->maxModelNameWidth,oTemp->cameraModel);
        else printf("not found");
        printf("\n");
        oTemp = oTemp->pNext;
    }
    free(param);
}

formatParameters *getFormatParameters(JPEGList* imgList)
{

    formatParameters *param = (formatParameters*)malloc(sizeof(formatParameters));
    if(!param) handleError(MALLOC,NULL);
    // param->maxFileNameWidth and param->maxModelNameWidth - 
    // variable to correspondingly hold the maximum length of file name and camera model name.
    // Used to cleanly format the print output.
    param->maxFileNameWidth = 0;
    param->maxModelNameWidth = 0;

    struct JPEGList *oTemp = imgList;
    while(oTemp != NULL)
    {
        if(oTemp->fileName)
        {
            if(strlen(oTemp->fileName) > param->maxFileNameWidth)
             param->maxFileNameWidth = strlen(oTemp->fileName);
        }
        if(oTemp->cameraModel)
        {
            if(strlen(oTemp->cameraModel) > param->maxModelNameWidth) 
             param->maxModelNameWidth = strlen(oTemp->cameraModel);
        }
        oTemp = oTemp->pNext;
    }

    return param;
}