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

    //incializamos variables de la estrcutura.

    Words_bank -> add_words = &insert_Nodes;
    Words_bank -> delete_word = &delete_Nodes;
    Words_bank -> save_changes = &save_changes_in_file;
    Words_bank -> show_words = &print_words;
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
        //Delete the '\n' ENter in the words.
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
    //Memory leak error
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
        //Pabra muy grande para el espacio de memoria
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
        //Error, el numero usado no es valido
        return;
    }
    
    if (index > tmpsize)
    {
        //error, no se puede encontrar dicho numero
        return;
    }

    for (size_t i = 1; i < index; i++)
    {
        prev = cur;
        cur = cur -> next;
    }
    
    if (cur == NULL)
    {
        //error, no se encontró el numero especificado.
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
        //TODO : error
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

void print_words( void )
{
    //TODO : Agregar logica para visualizar de modo debug las palabaras guardadas.
}

char * select_node( int numberNode )
{
    if (numberNode <= 0)
    {
        //TODO: insertar,print error
        return "Default";
    }
    
    dword size = size_bank_words();
    if (numberNode > size)
    {
        //TODO: insertar,print error.
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