#include "header.h"
#include "edit.h"

int edit(int argc, char *argv[], mp3file *m3file)
{
  printf("Entered edit\n");
  char option[3];
  /*validation part*/
  if (strcmp(argv[1], "-e") == 0 && argc == 4) // forediting
  {
    if (strstr(argv[3], ".mp3")) // for .mp3 extension
    {
      strcpy(option,argv[2]);
      //printf("option is %s",option);
      
      strcpy(m3file->file_name, argv[3]); // copying mp3 name

      m3file->file_fptr = fopen(m3file->file_name, "r+"); // opening file

      if (m3file->file_fptr != NULL) // if file is opened
      {
        // checking it is ID3
        char check[4];
        for (int i = 0; i < 3; i++)
        {
          check[i] = fgetc(m3file->file_fptr);
        }
        check[4] = '\0'; // last null character

        // printf("chek is %s\n",check);

        if (strcmp(check, "ID3") == 0)
        {
          printf("ID3 success\n");

          char buffer[2];
          fread(buffer, 1, 2, m3file->file_fptr);
          if (buffer[0] == 3 && buffer[1] == 0)
          {
            printf("mp3 is Version 2\n");
          }
        }
        else
        {
          printf("ID3 is not success");
          return FAILURE;
        }
      }
      else
      {
        printf("file is not opened\n");
      }
    }
    else // mp3 extension not found
    {
      printf("mp3 not found\n");
      return FAILURE;
    }
  }

  /*editing*/
  fseek( m3file->file_fptr, 10, SEEK_SET);
}