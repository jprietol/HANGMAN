#include "control.h"
#include "./words.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WINNER 1
#define LOOSER 0

pthread_mutex_t lock;
pthread_cond_t cv1;
pthread_cond_t cv2;

static inline void checkLetters(info_game * tmpInfo);

void * control_game(void* vargp)
{
    info_game * currentInfo = (info_game *) vargp;
    Linked_list * words = create_linked_list_word();

    unsigned int seed = time(0);
    char const clear_buffer[15] = {'\0',};
    int rd_num = rand_r(&seed) % (words->size_bank() - 1 + 1) + 1;
    char achbuffer [15];
    memcpy(achbuffer , words -> select_word(rd_num) , 15);

    pthread_mutex_lock(& lock);
    memcpy(currentInfo->word , achbuffer , sizeof(achbuffer));
    memcpy(currentInfo->achbuffer , clear_buffer , sizeof(currentInfo->achbuffer));
    memcpy(currentInfo->good_letter , clear_buffer , sizeof(currentInfo->good_letter));
    memcpy(currentInfo->bad_letter , clear_buffer , sizeof(currentInfo->bad_letter));
    currentInfo->index_good = 0;
    currentInfo->index_bad = 0;
    currentInfo->result = 0;
    pthread_mutex_unlock(& lock);

    info_game  localInfo;
    while (1)
    {
        //memset(localInfo , 0 , sizeof(*localInfo));
        pthread_mutex_lock(& lock);
        while(currentInfo->achbuffer[0] == '\0')
        {
           pthread_cond_wait(&cv1,&lock);
           memcpy(&localInfo , currentInfo , sizeof(*currentInfo));
        }

        checkLetters(&localInfo);
        memcpy(localInfo.achbuffer , clear_buffer, sizeof(localInfo.achbuffer));

        
        memcpy( currentInfo ,&localInfo , sizeof(*currentInfo));
        pthread_cond_signal(&cv2);
        pthread_mutex_unlock(& lock);
        
    }

    //Colocar destructor del word
    
}

void checkLetters(info_game * tmpInfo)
{
    dword count = 0 , index;
    bool correct = false;
    while (tmpInfo->achbuffer[count] != '\0')
    {
        index = 0;
        correct = false;
        while (tmpInfo->word [index] != '\0')
        {
            if (tmpInfo->achbuffer[count] == tmpInfo->word [index])
            {
                tmpInfo->good_letter[index] = tmpInfo->achbuffer[count];
                correct = true;
            }

            index ++;
        }

        if (!correct)
        {
            tmpInfo->index_bad++;
        }
        count ++;
    }
    

}

void init_info_game(info_game ** info_self)
{
    * info_self = (info_game * ) malloc (sizeof(info_game));
}