#ifndef WORDS_LIB_H
#define WORDS_LIB_H

#include "../common/common.h"
#include <malloc.h>


//Add words.
//Delete words.
//Show words.
//Save changes
#define MAX_SIZE_WORD 15
typedef struct Node Words;

typedef struct linked
{
    Words * head;
    void (* add_words) (char *);
    void (* delete_word) (const dword);
    void (* show_words) (void);
    void (* save_changes)(void);
    char * (* select_word)(const int numberNode);
    void ( * delete_linked_list)( void );
    dword ( * size_bank)( void );

}Linked_list;

Linked_list * create_linked_list_word();


#endif