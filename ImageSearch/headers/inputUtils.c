#include "errorUtils.h"
#include "inputUtils.h"
#include "formatUtils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

inputParameters* inputParameters_New()
{
    inputParameters *newP = (inputParameters*)malloc(sizeof(struct inputParameters));
    if(!newP) handleError(MALLOC,NULL);
    newP->inputFolderPath = (char*)malloc(2*sizeof(char));
    if(!newP->inputFolderPath) handleError(MALLOC,NULL);
    strcpy(newP->inputFolderPath,".");
    newP->inputFileName = NULL;
    newP->inputDate = NULL;
    newP->inputCameraModel = NULL;
    return newP;
}
inputParameters* handleInputParameters(inputParameters *input, int argc, char* argv[])
{
    if(argc == 1) handleError(NOARGS,NULL);
    int optind;
    // iterating over all recieved parameters
    for(optind = 1; optind < argc;optind++)
    {
        // if the parameter starts with '-' then we can start considering it valid
        if(argv[optind][0] == '-') 
        {
            char parameter = (char)argv[optind][1];
            if (!strcmp(argv[optind],"-help")) handleError(SHOWHELP,NULL);
            else if (!strcmp(argv[optind],"-detailed")) handleError(TOGGLEERRORDETAIL,NULL);
            else if (parameter == 't') input = setFolderPath(input,argv[optind+1]);
            else if (parameter == 'm') input = setCameraModel(input,argv[optind+1]);
            else if (parameter == 'f') input = setFileName(input,argv[optind+1]);
            else if (parameter == 'd') input = setCaptureDate(input,argv[optind+1]);
        }
    }
    return input;
}

inputParameters* setFolderPath(inputParameters* input, char* inputPath)
{
    if(inputPath == NULL) handleError(INPUTPATH,NULL);
    else if(inputPath[0] == '-') handleError(INPUTPATH,NULL);
    else
    {
        free(input->inputFolderPath);
        input->inputFolderPath = (char*)malloc((strlen(inputPath)+1) * sizeof(char));
        if(!input->inputFolderPath) handleError(MALLOC,NULL);
        strcpy(input->inputFolderPath,inputPath);
    }
    return input;
}
inputParameters* setCameraModel(inputParameters* input, char* inputPath)
{
    if(inputPath == NULL) handleError(INPUTPARAMETER,"camera model");
    else if(inputPath[0] == '-') handleError(INPUTPARAMETER,"camera model");
    else
    {
        input->inputCameraModel = (char*)malloc(strlen(inputPath) * sizeof(char));
        if(!input->inputCameraModel) handleError(MALLOC,NULL);
        strcpy(input->inputCameraModel,inputPath);
    }
    return input;
}
inputParameters* setFileName(inputParameters* input, char* inputPath)
{
    if(inputPath == NULL) handleError(INPUTPARAMETER,"file name");
    else if(inputPath[0] == '-') handleError(INPUTPARAMETER,"file name");
    else
    {
        input->inputFileName = (char*)malloc(strlen(inputPath) * sizeof(char));
        if(!input->inputFileName) handleError(MALLOC,NULL);
        strcpy(input->inputFileName,inputPath);
    }
    return input;
}
inputParameters* setCaptureDate(inputParameters* input, char* inputPath)
{
    if(inputPath == NULL) handleError(INPUTPARAMETER,"capture date");
    else if(inputPath[0] == '-') handleError(INPUTPARAMETER,"capture date");
    else
    {
        input->inputDate = (captureDate*)malloc(sizeof(struct captureDate));
        if(!input->inputDate) handleError(MALLOC,NULL);
        sscanf(inputPath,"%d.%d.%d",&input->inputDate->day,&input->inputDate->month,&input->inputDate->year);
    }
    return input;
    
}

void showHelp()
{
    printf("Usage: program [-t target_dir] [-m cam_model] [-d 'dd.mm.yyyy'] [-f f_name] [-detailed]\n");
    printf("-t target_dir   specify search target directory\n");
    printf("-m cam_model    specify search target camera model\n");
    printf("-d 'dd.mm.yyyy' specify search target capture date\n");
    printf("-f f_name       specify search target file name\n");
    printf("-detailed       show detailed error messages\n");
}