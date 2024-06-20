#include "header.h"
#include "view.h"

int view(int argc, char *argv[], mp3file *mpFile)
{

  if (strcmp(argv[1], "-v") == 0 && argc == 3) // for viewing
  {
    if (strstr(argv[2], ".mp3")) // for .mp3 extension
    {

      strcpy(mpFile->file_name, argv[2]); // copying mp3 name

      mpFile->file_fptr = fopen(mpFile->file_name, "r"); // opening file

      if (mpFile->file_fptr != NULL) // if file is opened
      {
        // checking it is ID3
        char check[4];
        for (int i = 0; i < 3; i++)
        {
          check[i] = fgetc(mpFile->file_fptr);
        }
        check[4] = '\0'; // last null character

        // printf("chek is %s\n",check);

        if (strcmp(check, "ID3") == 0)
        {
          printf("ID3 success\n");

          char buffer[2];
          fread(buffer, 1, 2,mpFile->file_fptr);
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

  /*skipping header*/
  fseek(mpFile->file_fptr, 10, SEEK_SET);
  // printf("pos is %d\n",ftell(mpFile->file_fptr));
  printf("\n----------------------- WELCOME TO VIEW LOG ---------------------\n");
  printf("-----------------------------------------------------------------\n");
  printf("File Name: %s   |     Version : 2 \n", mpFile->file_name);
  printf("-----------------------------------------------------------------\n-----------------------------------------------------------------\n");

  while (1)
  {
    char buffer[4];
    fread(buffer, 1, 4, mpFile->file_fptr);
    char flag = 0;

    if (strcmp(buffer, "TIT2") == 0)
      printf("Title of Song       :\t");
    else if (strcmp(buffer, "TPE1") == 0)
      printf("Artist Name         :\t");
    else if (strcmp(buffer, "TALB") == 0)
      printf("Album Name          : \t");
    else if (strcmp(buffer, "TYER") == 0)
      printf("Year of realease    :\t");
    else if (strcmp(buffer, "TCON") == 0)
      printf("Content Type        :\t");
    else if (strcmp(buffer, "COMM") == 0)
      printf("Comment             :\t");
    else if (buffer[0] != 'T')
      break;
    else
      flag = 1;

    /*reading size*/
    fread(buffer, 1, 4, mpFile->file_fptr);
    int size = ((hexa_to_decimal(buffer)) - 1);

    /*stroing data*/
    char data[size];
    fseek(mpFile->file_fptr, 3, SEEK_CUR); // skipping flag fields
    fread(data, 1, size, mpFile->file_fptr);

    int i = 0;
    if (flag != 1)
    {
      while (data[i] != '\0')
      {
        if (data[i] >= 0 && data[i] < 128)
          printf("%c", data[i]);
        i++;
      }
    }
    printf("\n-----------------------------------------------------------------\n");
  }
}
int hexa_to_decimal(char *ch)
{
  int num = 0, shift = 24;
  for (int i = 0; i < 4; i++)
  {
    num = num | (ch[i] << shift);
    shift -= 8;
  }
  return num;
}