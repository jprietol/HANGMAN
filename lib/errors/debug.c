#include "debug.h"

#define  LOGS_FILE "./logs_ln/debug.0.log"

static void createLogsFile();
static void createCompress();

void startLogs()
{
    //checar que no exita un archivo 0, crear los respectivos comprimidos de logs anteriores y borrar los logs despues de los 10, el umbral debe ser de 100B.
    int result = access(LOGS_FILE ,  F_OK );
    
    if (result == -1){createLogsFile();}
    else if(result == 0)
    {
        createCompress();
    }
    
    
    TPrintDebug("Valor de result : %d" , result);
    
}

void createLogsFile()
{
    FILE * fp = NULL;
    fp = fopen(LOGS_FILE , "a" );
    fclose(fp);
}

void createCompress()
{
    FILE * fp = NULL;
    fp = fopen(LOGS_FILE , "r" );
    if (fp = NULL)
    {
        TPrintDebug ("Error in open the file");
        return;
    }
    
    int result = 0;
    result = fseek(fp, 0L , SEEK_END);
    if (result == 0)
    {
        TPrintDebug ("Error in seek log file");
        return;
    }

    long size = 0;
    size = ftell(fp);

    fseek(fp , 0L , SEEK_SET);
    fclose(fp);

    TPrintDebug("Size of log file = %ld", size);

    //TODO: terminar la creacion de logs
    if (size >= 100) // 100Bytes
    {
        //create new .zip
    }
    else
    {
        //continue
    }

    
    
    
    



}