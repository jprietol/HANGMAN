#ifndef ERROR_LOGS_H
#define ERROR_LOGS_H

#include <stdio.h>
#include <unistd.h>
#include "../common/common.h"

#ifdef DEBUG

    #define __FUNCTION_NAME__   __func__
    #define TPrintDebug(fmt , ...)\
    fprintf(stderr, "%s | %s | File : %s | Func : %s | Line : %d | " fmt " |\n",__DATE__, __TIME__ , __FILE__ , __func__ , __LINE__ ,##__VA_ARGS__)

#else
    #define TPrintDebug(sterror , ...)
#endif

void startLogs();


#endif