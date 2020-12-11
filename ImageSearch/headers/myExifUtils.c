#include "myExifUtils.h"
#include "errorUtils.h"

#include <libexif/exif-data.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


EXIFInfo *getExifInfo(const char* filePath)
{
    struct EXIFInfo *info = (EXIFInfo*)malloc(sizeof(struct EXIFInfo));
    if(!info) handleError(MALLOC,NULL);
    
    // Reading new exif data straight from a file and storing
    // it in ExifData
    ExifData *data = exif_data_new_from_file(filePath);
    info->model = NULL;
    info->dateInfo = NULL;
    if(!data)
    {
        handleError(EXIFDATAREAD,(char*)filePath);
        free(info);
        return NULL;
    }
    else
    {
        // Parsing the recieved ExifData for the
        // required information
        ExifEntry *entryModel = exif_data_get_entry(data,EXIF_TAG_MODEL);
        if(!entryModel) 
        {
            handleError(EXIFENTRYNEWMODEL,(char*)filePath);
        }
        else
        {
            char entryData[256];
            // Getting the value from the entry and
            // storing it in a buffer
            exif_entry_get_value(entryModel,entryData,256);
            if(strcmp(entryData,"[None]"))
            {
                info->model = (char*)malloc((strlen(entryData)+1)*(sizeof(char)));
                if(!info->model) handleError(MALLOC,NULL);
                strcpy(info->model,entryData);
            }
        }

        ExifEntry *entryDate = exif_data_get_entry(data,EXIF_TAG_DATE_TIME_ORIGINAL);
        if(!entryDate) 
        {
            handleError(EXIFENTRYNEWDATE,(char*)filePath);
        }
        else
        {
            char entryData[256];
            exif_entry_get_value(entryDate,entryData,256);
            info->dateInfo = (captureDate*)malloc(sizeof(struct captureDate));
            if(!info->dateInfo ) handleError(MALLOC,NULL);
            if(sscanf(entryData,"%d:%d:%d[12]",&info->dateInfo->year,&info->dateInfo->month,&info->dateInfo->day) < 3){
                free(info->dateInfo);
                info->dateInfo = NULL;
            };
        }
    }

    // Freeing the recieved data
    exif_data_unref(data);
    if(!info->model && !info->dateInfo)
    {
        free(info);
        return NULL;
    }
    return info;
}