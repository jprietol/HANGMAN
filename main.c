#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "lib/errors/debug.h"
#include "lib/common/common.h"
#include "lib/gui/interface.h"
#include "lib/logic/options.h"
#include "lib/logic/control.h"

static void opt(int argc, char  **argv);
static void printResult(info_game * currentGame);
static void credits();
info_game * currentGame = NULL;

int main (int argc, char **argv)
{
    TPrintDebug("Start the app in debug");
    opt( argc ,  argv);

    pthread_t pinter_id , plogic_id;

   
    bool flagExec = true;
    while (flagExec)
    {
        system("clear");
        dword nResult = gui_start_game();

        TPrintDebug("Start Hangman version : %s%s",MAJOR_VER,MENOR_VER);

        switch (nResult)
        {
            case 1:

                init_info_game(& currentGame);
                pthread_cond_init(&cv1,NULL);
                pthread_cond_init(&cv2,NULL);
                pthread_mutex_init(& lock , NULL);              
                pthread_create(&pinter_id , NULL , control_game , (void * ) currentGame);
                pthread_create(&plogic_id , NULL , interface_game , (void * ) currentGame);
                flagExec = false;
                break;
            case 2:
                show_words();
                flagExec = true;
                break;
            case 3:
                credits();
                flagExec = true;
            
            default:
                exit(0);
                break;
        }        

    }
    
    pthread_join(plogic_id , NULL);
    pthread_join(pinter_id , NULL);
    pthread_mutex_destroy(&lock);

    printResult(currentGame);

    
    return SUCCESS;
}

void opt(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        if (opt == 'v')
        {
            TPrintDebug( "Get -v arg" );
            printf ("Version : %s%s\n" , MAJOR_VER , MENOR_VER);
        }
        else{TPrintDebug( "It does not get some valid option.");}
        
    }
    
}

void printResult(info_game *currentGame)
{
    system("clear");
    printf("GAME OVER\n\n");
    
    if (currentGame->result)
    {
        printf("You win the game, the word was %s\n" , currentGame->word);
    }
    else
    {
        printf("You loose the game, the word was %s\n" , currentGame->word);
    }
}

void credits()
{
    
    printf("Hi, I am Tashiro\n I have created this program to show you my skills in C/C++. I have experience in embedded systems, linux and so on\n");
    printf("If you are interested, please contact me by: https://www.linkedin.com/in/juan-prieto99?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app");
}