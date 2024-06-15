#include "header.h"
#include "view.h"


int main(int argc, char *argv[])
{
  mp3file mfile;

  if (validation(argc, argv, &mfile) == SUCCESS)
  {
    printf("Validation is successfull\n");
    view(&mfile);
  }
  else
  {
    printf("validation failed\n");
  }
}

// int check_operation(int argc, char *argv[],)

// validation function
int validation(int argc, char *argv[], mp3file *mfile)
{
  if (argc > 1)
  {
    if (strcmp(argv[1], "-v") == 0 && argc==3) // for viewing
    {
      if (strstr(argv[2], ".mp3")) // for .mp3 extension
      {

        strcpy(mfile->file_name, argv[2]); // copying mp3 name

        mfile->file_fptr = fopen(mfile->file_name, "r"); // opening file

        if (mfile->file_fptr != NULL) // if file is opened
        {
          // checking it is ID3
          char check[4];
          for (int i = 0; i < 3; i++)
          {
            check[i] = fgetc(mfile->file_fptr);
          }
          check[4] = '\0'; // last null character

          // printf("chek is %s\n",check);

          if (strcmp(check, "ID3") == 0)
          {
            printf("ID3 success\n");

            char buffer[2];
            fread(buffer, 1, 2, mfile->file_fptr);
            if (buffer[0] == 3 && buffer[1] == 0)
            {
              printf("mp3 is Version 2\n");
              return SUCCESS;
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
    /*Edit log*/
    else if( (strcmp(argv[1],"-v") == 0 && argc ==4 ))
    {
      
    }
    else if( strcmp(argv[1],"--help")==0  && argc==2)
    {
      printf("----------------------- HELP MENU -----------------------\n");
      printf(" -v  -> to view mp3 file contents\n -e  -> to edit mp3 file contents\n");
      printf("\t2.1  -t -> to edit song title\n\t2.2  -a -> to edit artist name\n\t2.3 -A -> to edit album name\n\t2.4  -y -> to edit year\n\t2.5  -m -> to edit content\n\t2.6  -c -> to edit comment\n ");
    }

  }
  else
  {
    printf("Please pass CLA\n");
  }
}