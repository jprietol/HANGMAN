#ifndef INTERFACE_GUI_H
#define INTERFACE_GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../common/common.h"
#include "../errors/debug.h"
#include "../logic/words.h"
#include "../logic/control.h"

dword gui_start_game();
void show_words();

void * interface_game( void * varg);


#endif