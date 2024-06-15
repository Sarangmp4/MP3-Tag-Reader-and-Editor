#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//macros
#define SUCCESS 0
#define FAILURE -1

typedef struct file
{
   char *file_name;
   FILE *file_fptr;

}mp3file;

typedef enum op
{
view_v=1,
edit_v=2,
help_v=3
}operation;






int validation(int argc, char *argv[],mp3file *mfile);

#endif