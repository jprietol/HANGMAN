#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include <malloc.h>
#include <pthread.h>
#include "../common/common.h"
#include "../errors/debug.h"

typedef struct info 
{   
    char bad_letter [5];
    char good_letter [15];
    char achbuffer[15];
    char word[15];

    dword index_good : 8;
    dword index_bad : 7;
    dword result : 1;

} info_game;


void * control_game(void* vargp);
void init_info_game(info_game ** info_self);

extern pthread_mutex_t lock;
extern pthread_cond_t cv1;
extern pthread_cond_t cv2;

#endif