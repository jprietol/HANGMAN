#ifndef ERROR_LOGS_H
#define ERROR_LOGS_H

#include <stdio.h>
#include <unistd.h>
#include "../common/common.h"

#define DEBUG 1
#ifdef DEBUG
#define  LOGS_FILE "./logs_ln/debug.0.log"

#define __FUNCTION_NAME__   __func__
#define TPrintDebug(fmt , ...)\
{\
    FILE * fp = fopen(LOGS_FILE,"ab");\
    fprintf(fp, "%s | %s | File : %s | Func : %s | Line : %d | " fmt " |\n",__DATE__, __TIME__ , __FILE__ , __func__ , __LINE__ ,##__VA_ARGS__);\
    fclose(fp);\
}
   

#else
    #define TPrintDebug(sterror , ...)
#endif

void startLogs();


#endif