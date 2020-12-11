#include "searchUtils.h"
#include "errorUtils.h"
#include "myExifUtils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

DIR* openFolder(const char* folderPath)
{
    if(folderPath != NULL) 
    {
        DIR *dir = opendir(folderPath);
        if(!dir) 
        {
            handleError(DIRECTORY,(char*)folderPath);
            return NULL;
        }
        else return dir;
    }
    else return NULL;
}

char* getNewPath(const char* folderPath,char* newFolder,choosePath path)
{
    // ignoring folder paths '.' and '..'
    if(path && (strcmp(newFolder,".") == 0 || strcmp(newFolder,"..") == 0))return NULL; 
    int newLength = strlen(folderPath) + strlen(newFolder) + 2;
    char* newPath = (char*)malloc(newLength*sizeof(char));
    snprintf(newPath,newLength,"%s/%s",folderPath,newFolder);
    return newPath;
}



bool filterString(const char* str1, const char* str2)
{
    if(str1 == NULL) return true;
    else 
    {
        if(strlen(str1) == strlen(str2))
        {
            int i;
            for(i = 0; i<strlen(str1);i++)
            {
                // wildcard asterisk support
                if(str1[i] != '*')
                {
                    if(tolower(str1[i]) != tolower(str2[i])) return false;
                }
            }
            return true;
        }
        else return false;
    }
}
bool compareDate(captureDate* date1, captureDate* date2)
{
    if(date1 == NULL) return true;
    else if(date2 == NULL) return false;
    else if((date1->day   == date2->day  ) &&
            (date1->month == date2->month) &&
            (date1->year  == date2->year )) { return true;}
    else return false;
}
bool filterCurrentFile(inputParameters* input, const char* fileName,EXIFInfo *exifInfo)
{
    if(filterString(input->inputFileName,fileName))
    {
        if(exifInfo)
        {
            if(exifInfo->model && exifInfo->dateInfo)
            {
                if(filterString(input->inputCameraModel,exifInfo->model) && compareDate(input->inputDate,exifInfo->dateInfo)) return true;
            }
            else if(!exifInfo->model && exifInfo->dateInfo)
            {
                if(compareDate(input->inputDate,exifInfo->dateInfo)) return true;
            }
            else if(exifInfo->model && !exifInfo->dateInfo)
            {
                if(filterString(input->inputCameraModel,exifInfo->model)) return true;
            }
        }
        else
        {
            if(input->inputDate || input->inputCameraModel) return false; else return true;
        }
    }
    else return false;
}

JPEGList *searchFolder(JPEGList *imgList,char* folderPath,inputParameters* input)
{
    struct dirent *dp;
    DIR *dir = openFolder(folderPath);
    if(!dir) return imgList;
    while((dp = readdir(dir)))
    {
        int len = strlen(dp->d_name);
        // if the file has a .jpg extension it should go to further inspection
        if((len >= 4) && strcmp(&(dp->d_name[len-4]),".jpg") == 0)
        {
            char* filePath = getNewPath(folderPath,dp->d_name,FILEPATH);
            EXIFInfo *fileInfo = getExifInfo(filePath);
            if(filterCurrentFile(input,dp->d_name,fileInfo)){
            imgList = addImage(imgList,dp->d_name,filePath,fileInfo);}
            free(fileInfo);
            free(filePath);
        }
        // if the current pointer points to a folder then get the path to it
        // and search it in the same way
        if(dp->d_type == 4)
        {
            char* newFolderPath = getNewPath(folderPath,dp->d_name,FOLDERPATH);
            imgList = searchFolder(imgList,newFolderPath,input);
            free(newFolderPath);
        }
    }
    closedir(dir);
    return imgList;
}

JPEGList* addImage(JPEGList *imgList, char* fileName,char* filePath,EXIFInfo *exifInfo)
{
    struct JPEGList *newL = (JPEGList*)malloc(sizeof(struct JPEGList));
    if(!newL) handleError(MALLOC,NULL);

    newL->fileName = (char*)malloc((strlen(fileName)+1) * sizeof(char));
    if(!newL->fileName) handleError(MALLOC,NULL);
    strcpy(newL->fileName,fileName);

    newL->filePath = (char*)malloc((strlen(filePath)+1)*sizeof(char));
    if(!newL->filePath) handleError(MALLOC,NULL);
    strcpy(newL->filePath,filePath);
    
    newL->cameraModel = NULL;
    newL->origDate = NULL;

    if(exifInfo)
    {
        if(exifInfo->model) newL->cameraModel = exifInfo->model;
        if(exifInfo->dateInfo) newL->origDate = exifInfo->dateInfo;
    }
    newL->pNext = imgList;
    imgList = newL;
    return imgList;

}