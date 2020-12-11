#include "errorUtils.h"
#include "inputUtils.h"
#include "myStructures.h"

#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void handleError(errorType error,char* specifier)
{
    // static integers to hold the amount of appearances
    // for specific errors
    static int data_new_from_file_count = 0;
    static int data_get_entry1_count = 0;
    static int data_get_entry2_count = 0;
    //static boolean to toggle more detailed error information
    static bool detailed_errors = false;

    switch(error)
    {
        case(NOARGS): fprintf(stderr,"Type -help for usage\n Searching current folder\n");break;
        case(INPUTPATH): fprintf(stderr,"No folder specified, searching current folder\n"); break;
        case(INPUTPARAMETER): fprintf(stderr,"No parameter '%s' specified\n",specifier); break;
        case(DIRECTORY): 
        {
            if(detailed_errors) fprintf(stderr,"Error %d: %s - %s\n",errno, strerror(errno),specifier); break;
        }
        case(MALLOC): fprintf(stderr,"Error %d: %s\n",errno, strerror(errno)); exit(EXIT_FAILURE);
        // cases with detailed error information, including filepath to error
        case(EXIFDATAREAD):{
            if(detailed_errors)fprintf(stderr,"%s - Error running exif_data_new_from_file(filePath)\n",specifier);
            data_new_from_file_count ++;
            break;
            }
        case(EXIFENTRYNEWMODEL):{
            if(detailed_errors)fprintf(stderr,"%s - Error running exif_data_get_entry(data,EXIF_TAG_MODEL)\n",specifier);
            data_get_entry1_count++;
            break;
            }
        case(EXIFENTRYNEWDATE):{
            data_get_entry2_count++;
            if(detailed_errors)fprintf(stderr,"%s - Error running exif_data_get_entry(data,EXIF_TAG_DATE_TIME_ORIGINAL)\n",specifier); 
            break;
            }
        case(TOGGLEERRORDETAIL):detailed_errors = true; break;
        //regular error detail 
        case(SHOWERRORS):{
            if(data_new_from_file_count) fprintf(stderr,"Failed to get exif data from (%d) file(s)\n",data_new_from_file_count);
            if(data_get_entry1_count) fprintf(stderr,"Failed to get camera model entry from (%d) file(s)\n",data_get_entry1_count);
            if(data_get_entry2_count) fprintf(stderr,"Failed to get capture date entry from (%d) file(s)\n",data_get_entry2_count);
            break;
        }
        case(SHOWHELP):{
            showHelp();
            exit(EXIT_SUCCESS);
            }
    }
}