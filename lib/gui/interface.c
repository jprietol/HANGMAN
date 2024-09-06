#include "interface.h"
#include <string.h>
#define MAX_OPTIONS 4

dword gui_start_game()
{

    printf("#################\n");
    printf("##   HANGMAN   ##\n");
    printf("#################\n\n");

    printf("1. Start the game.\n2. Watch the words.\n3.Credits.\n 4.exit.\n");
    printf("\nPlease, select a option:");

    short nOption = 1 ;
    while (1)
    {
        scanf("%hd", &nOption);
        TPrintDebug("Option in while= %d" , nOption);

        if (nOption <= 0 || nOption >= MAX_OPTIONS){ 
            printf("incorrect option. Please select again:");
        }
        else
        {
            TPrintDebug("Is correct the number");
            break;
        }    
    }

    return (dword) nOption;
}

void show_words()
{
    Linked_list * tmpWords = create_linked_list_word();
    dword tmpsize = 0 , index = 0;
    char * achbuffer;
    char option = '\0';
    char newWord[15] = {'\0',};

    while (1)
    {   
        system("clear");
        printf ("WORDS LIST\n");
        memset(newWord ,'\0',sizeof(newWord));

        tmpsize = tmpWords -> size_bank();
        for (size_t i = 0; i < tmpsize; i++)
        {
            achbuffer = tmpWords -> select_word(i + 1);
            printf("%ld. %s\t\t\t" , i + 1, achbuffer);
            if ((i + 1) % 4 == 0)
            {
                printf("\n");
            }  
        }

        printf("\n\n\na. Add. b. Delete. c. Exit and save.");
        printf("\nSelect one option:");
        scanf("%s" , &option);

        if (option == 'a')
        {
            printf("\nWrite the new word :");
            scanf("%s" , newWord);
            tmpWords->add_words(newWord);
            continue;
        }
        else if (option == 'b')
        { 
            printf("\nSelect the index from the word :");
            scanf("%hu" , & index);
            tmpWords -> delete_word(index);
            continue;
        }
        else if(option == 'c')
        {
            char answer;
            system("clear");
            printf("Do you want to save the changes? [y/n]");
            scanf("%s" , &answer);
            if(answer == 'n')
            {
                tmpWords->delete_linked_list();
                free(tmpWords);
                break;
            }
            else if (answer == 'y')
            {
                tmpWords -> save_changes();
                tmpWords -> delete_linked_list();
                free(tmpWords);
                break;
            }
            else
            {
                printf("Invalid option");
            }
        }
        else
        {
            printf("Error in the option selected ...");
        }

    }
}