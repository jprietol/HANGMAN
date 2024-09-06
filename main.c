#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "lib/errors/debug.h"
#include "lib/common/common.h"
#include "lib/gui/interface.h"
#include "lib/logic/options.h"

static void opt(int argc, char  **argv);

int main (int argc, char **argv)
{
    TPrintDebug("Start the app in debug");
    opt( argc ,  argv);
    //startLogs();

   
    bool flagExec = true;
    while (flagExec)
    {
        system("clear");
        dword nResult = gui_start_game();

        switch (nResult)
        {
            case 1:

                //TODO : Make game ();
                flagExec = false;
                break;
            case 2:
                show_words();
                flagExec = true;
                break;
            case 3:
                /*credits*/
                flagExec = true;
            
            default:
                exit(0);
                break;
        }        

    }
    
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