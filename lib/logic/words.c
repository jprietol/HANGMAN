#include "words.h"
#include <stdbool.h>
#include <string.h>


#define MAX_SIZE_WORD 15
#define PATH_WORDS_BANK "./words_bank.ln/words_bank.txt"
#define ERROR_OPEN_FILE (-1);

static void insert_Nodes( char * Word );
static void delete_Nodes( const dword index );
static void save_changes_in_file( void );
static void print_words( void );
static char * select_node( const int numberNode);
static void delete_linked_list( void );
static dword size_bank_words( void );
static dword initWords( void );

typedef struct Node
{
    char word[MAX_SIZE_WORD];
    Words * next;
}Words;

Linked_list * Words_bank = NULL;

Linked_list * create_linked_list_word()
{
   
    Words_bank = (Linked_list *) malloc(sizeof(Linked_list));

    Words_bank -> add_words = &insert_Nodes;
    Words_bank -> delete_word = &delete_Nodes;
    Words_bank -> save_changes = &save_changes_in_file;
    Words_bank -> select_word = &select_node;
    Words_bank -> delete_linked_list = &delete_linked_list;
    Words_bank -> size_bank = &size_bank_words;

    Words_bank -> head = NULL;
    Words * tmpHead = (Words *) malloc(sizeof(Words));
    tmpHead -> word[0] = '\0';
    tmpHead -> next = NULL;
    Words_bank -> head = tmpHead;

    dword nResult = initWords();
    if(nResult != SUCCESS)
    {
        return NULL;
    }
     
    return Words_bank;
}

dword initWords()
{
    FILE * words_file = NULL;
    char achbuffer[MAX_SIZE_WORD];
    bool firstNode = true;


    words_file = fopen(PATH_WORDS_BANK, "r");

    if (words_file == NULL) 
    {
        return ERROR_OPEN_FILE;
    }

    while (fgets(achbuffer, MAX_SIZE_WORD, words_file) != NULL) 
    {
        //Delete the '\n' Enter in the words.
        for( int i =0 ; i <  MAX_SIZE_WORD; i++)
        {
            if(achbuffer[i] == '\n')
            {
                achbuffer[i] = '\0';
                break;
            }
        }

        if (firstNode) // This is only to add the first word in Head node
        {
            memcpy( Words_bank->head->word , achbuffer ,MAX_SIZE_WORD );
            firstNode = false;
            continue;
        }
        insert_Nodes(achbuffer);
    }

    fclose(words_file);
    return SUCCESS;  
}

void insert_Nodes(char  *  NewWord)
{
    Words * cur = Words_bank -> head;
    if (cur == NULL) {
    TPrintDebug("Error memory leak");
    return;
    }

    int count = 0;
    while (count < MAX_SIZE_WORD - 1)
    {
        if(NewWord[count] == '\0')
        {
            count ++;
            break;
        }
        else if (NewWord[count] == '\n')
        {
            count ++;
            NewWord [count] = '\0';
            break;
        } 

        count ++;
    }


    if (count > MAX_SIZE_WORD - 1)
    {
        TPrintDebug("The word is so big");
        return;
    }
    
    Words * newWord = (Words *) malloc(sizeof(Words));
    memcpy(newWord -> word , NewWord , count);
    newWord -> next = NULL;

    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newWord;
}

void delete_Nodes( const dword index )
{
    Words * cur = Words_bank -> head , * prev;

    dword tmpsize = size_bank_words();

    if (index <= 0)
    {
        TPrintDebug("Error, the number is not valid");
        return;
    }
    
    if (index > tmpsize)
    {
        TPrintDebug("Error, it is not posible find the number");
        return;
    }

    for (size_t i = 1; i < index; i++)
    {
        prev = cur;
        cur = cur -> next;
    }
    
    if (cur == NULL)
    {
        TPrintDebug("Error, the number not found");
        return;
    }

    prev -> next = cur -> next;
    free(cur); 
}

void save_changes_in_file( void )
{
    FILE * fp = NULL;
    fp = fopen(PATH_WORDS_BANK, "wa");

    if (fp == NULL)
    {
        TPrintDebug("Error, it does not open the file");
        return;
    }
    
    char * word;
    dword tmpsize = size_bank_words();
    for (size_t i = 1; i <= tmpsize; i++)
    {
        word = select_node(i);
        
        fprintf(fp ,"%s\n", word );
    }

    fclose(fp); 
}


char * select_node( int numberNode )
{
    if (numberNode <= 0)
    {
        TPrintDebug("Error, is not found the node, sent default word");
        return "Default";
    }
    
    dword size = size_bank_words();
    if (numberNode > size)
    {
        TPrintDebug("The number is not valid, use default word");
        return "Default";
    }
    

    Words * cur = Words_bank -> head;
    for (size_t i = 1; i < numberNode; i++)
    {
        cur = cur -> next;
    }

    return cur -> word;
}

void delete_linked_list( void )
{
    Words * cur = Words_bank -> head , * next;

    while (cur != NULL)
    {
        next = cur -> next;
        free(cur);
        cur = next;
    }
    
}

dword size_bank_words( void )
{
    dword size_bank = 0;
    Words * cur = Words_bank -> head;

    while (cur != NULL )
    {
        size_bank ++;
        cur = cur -> next;
    }

    return size_bank ;
    
}