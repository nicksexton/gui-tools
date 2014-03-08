/* TODO:
   fix parsing to use sscanf or similar to assign numeric variables 
   fix data processing so that it doesn't mindlessly print out 10 fields
   fix parsing so that space or comma can also be used as a delimiter */


#define MAX_FIELDS 10
#define MAX_LINE_LENGTH 512

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




  char input_line [MAX_LINE_LENGTH];
  char *ptr, *ptr_eol; // current position, end of line
  //  char *ptr_comment;
  char fields [MAX_FIELDS][51];
  char *comment_marker = "#";


  int n, f;

  for (f = 0; f < MAX_FIELDS; f++) {
    strcpy(fields[f], "");
  }


  while (1) {
        
    fgets(input_line, sizeof input_line, config_file);
    ptr = input_line;

    // check if line contains a comment, position end of line pointer at the comment
    ptr_eol = strstr(input_line, comment_marker);
    if (ptr_eol == NULL)
      ptr_eol = ptr + strlen(input_line);
    
    
    f = 0;
    while (ptr < ptr_eol) {
      sscanf (ptr, "%50[^\t\n]%n", fields[f], &n);
      ptr += n;
      if ((*ptr != '\t') && (*ptr != '\n')) break; // no delimiter, end of file reached?
      // need to handle condition here where \t is followed by a \n 
      

      ptr += 1; // skip the delimiter
      while ((*ptr == '\t') || (*ptr == '\n')) {
	ptr += 1; 
	f++;
      }
      f ++;
    }

    if (f > 0) { // was any data extracted?
      // if so, process the data
      for (f = 0; f < MAX_FIELDS; f++) {
	printf ("%s\n", fields[f]);
      }
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
