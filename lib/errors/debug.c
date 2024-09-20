#include "debug.h"

static void createLogsFile();

void startLogs()
{
    int result = access(LOGS_FILE ,  F_OK );
    
    if (result == -1){createLogsFile();}
    else if(result == 0)
    {
        
    }

}

void createLogsFile()
{
    FILE * fp = NULL;
    fp = fopen(LOGS_FILE , "a" );
    fclose(fp);
}