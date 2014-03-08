#define FIELDS 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {


  FILE *config_file;

  config_file = fopen("gtk_config_file.conf", "r");
  if (config_file == NULL) {
    printf ("error! gtk_config_file.conf not opened!\n");
    return 1;
  }




  char input_line [512];
  char *ptr;
  char fields [10][51];
  int n, f;

  for (f = 0; f < FIELDS; f++) {
    strcpy(fields[f], "");
  }


  while (1) {
        
    fgets(input_line, 255, config_file);


    ptr = input_line;
    for (f = 0; f < FIELDS; f ++) {
      sscanf (ptr, "%50[^\t\n]%n", fields[f], &n);
      ptr += n;
      if ((*ptr != '\t') && (*ptr != '\n')) break; // no delimiter, end of file reached?
      // need to handle condition here where \t is followed by a \n 
      
      ptr += 1; // skip the delimiter
      while ((*ptr == '\t') || (*ptr == '\n')) {
	ptr += 1; 
	f++;
      }
    }


    // now print the data
    for (f = 0; f < FIELDS; f++) {
      printf ("%s\n", fields[f]);
    }

    // handle break conditions

    if (feof(config_file)) {
      //  printf ("end of file reached, all is good\n");
      break;
    }

  
    if (ferror (config_file)) {
      printf ("a file read error occurred, exiting\n");
      exit (EXIT_FAILURE);
      
    }
  }



  return 0;

}
