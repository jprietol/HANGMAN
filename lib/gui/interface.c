#include "interface.h"
#include <string.h>
#define MAX_OPTIONS 4
#define MATRIX_CONVERTION 3

static inline void printDisplay( info_game * localInfo);
static inline void printWrongLetters ( info_game * localInfo );
static inline void printCorrectLetters( info_game const * localInfo);
static size_t getSizeWord( char const * word);

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

void * interface_game( void * varg)
{
    info_game * currentInfo = (info_game * ) varg;
    info_game localInfo;
    char localBuffer [15] = {'\0'};

    sleep(1);
    while (1)
    {
        pthread_mutex_lock(& lock);
        while (currentInfo->achbuffer[0] != '\0')
        {
            pthread_cond_wait(&cv2,&lock);
            memcpy(&localInfo , currentInfo , sizeof(*currentInfo));
        }

        if (localInfo.word[0] != '\0')
        {
            if (finish_game(&localInfo))
            {
                break;
            }
        }
        
        system("clear");
        printf("HANGMAN GAME \n\n");

        printWrongLetters(&localInfo);
        printDisplay(&localInfo);
        printCorrectLetters(&localInfo);
        char localBuffer [15];
        printf("\n\nPlease, write the letters:");
        scanf("%s", localBuffer);

        memcpy(currentInfo->achbuffer , localBuffer , 15);
        pthread_cond_signal(&cv1);
        pthread_mutex_unlock(& lock);

        
    }
    pthread_exit(NULL);
}

void printDisplay( info_game * localInfo)
{
    const char hangmanDraw[] = 
    {' ' , 'O' , ' ' ,
     '/' , '|' , '\\',
     '/' , ' ' , '\\'
    };

    dword index = 0;

    if (localInfo->index_bad  == 1){ index = localInfo->index_bad * MATRIX_CONVERTION;}
    else if (localInfo->index_bad == 5){index = 9;}
    else if (localInfo->index_bad == 4){index = 6;}
    else if(localInfo->index_bad == 0){index = 0;}
    else{index = localInfo->index_bad + 2;}
    
    for (size_t i = 0; i < index; i++)
    {
        if ((i + 1) % MATRIX_CONVERTION == 0){printf("%c\n" , hangmanDraw[i]);}
        else{printf("%c" , hangmanDraw[i]);} 
    }  
}

void printWrongLetters ( info_game * localInfo )
{
    printf("\n");
    printf("Wrong letters: ");
    dword count = localInfo->index_bad;
    for (size_t i = 0; i < count; i++)
    {
        printf("%c  ", localInfo->bad_letter[i]);
    }
    printf("\n");
    
}

void printCorrectLetters( info_game const * localInfo)
{
    size_t size_word = getSizeWord(localInfo->word);
    printf("\nCorrect letters : ");
    for (size_t i = 0; i < size_word; i++)
    {
        if (localInfo->good_letter[i] == '\0')
        {
            printf(" __ ");
        }
        else
        {
            printf(" %c " , localInfo->good_letter[i]);
        }
        
    }

    printf("\n"); 
}

size_t getSizeWord( char const * word)
{
    size_t count = 0; 
    while ( word[count] != '\0' )
    {
        count ++;
    }

    return count;    
}