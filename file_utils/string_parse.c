/* TODO:
   fix parsing to use sscanf or similar to assign numeric variables 
   fix data processing so that it doesn't mindlessly print out 10 fields
   fix parsing so that space or comma can also be used as a delimiter */


#define MAX_FIELDS 10
#define FIELD_SIZE 51
// MAX_LINE_LENGTH should be MAX_FIELDS * FIELD_SIZE
#define MAX_LINE_LENGTH 512

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*
void pdp_file_parse_line (*char input_line) {
  // this function is program specific


}
*/

int pdp_file_parse_new_line (FILE *input_file, 
			     int max_fields, 
			     int field_size, 
			     char extracted_fields[max_fields][field_size]) {
  // dimensions - extracted_fields[max_fields][field_size]
  // parses input file, segments it, filters it for comments etc
  // returns number of fields successfully extracted
  // returns 0 if line is empty,
  // returns -1 if EOF
  // returns -2 if error

  // clears contents of char array


  char input_line [MAX_LINE_LENGTH];
  char *ptr, *ptr_eol; // current position, end of line
  char *comment_marker_hash = "#"; // everything after hash to end of line 
                                   // interpreted as comment

  int n, f;

  // clear the array
  for (f = 0; f < max_fields; f++) {
    strcpy(extracted_fields[f], "");
  }

  fgets(input_line, sizeof input_line, input_file);
  
  ptr = input_line;

    if (feof(input_file)) {
      printf ("end of file reached, all is good\n");
      return -1;
    }
  
    if (ferror (input_file)) {
      printf ("a file read error occurred, exiting\n");
      return -2;
   } 


    // check if line contains a comment, position end of line pointer at the comment
    ptr_eol = strstr(input_line, comment_marker_hash);
    if (ptr_eol == NULL)
      ptr_eol = ptr + strlen(input_line);
    
    
    f = 0;
    while (ptr < ptr_eol) {
      sscanf (ptr, "%50[^\t\n]%n", extracted_fields[f], &n);
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
    return f;
}


int main () {


  FILE *config_file;
  int fields_extracted;

  config_file = fopen("gtk_config_file.conf", "r");
  if (config_file == NULL) {
    printf ("error! gtk_config_file.conf not opened!\n");
    return 1;
  }

  char fields [MAX_FIELDS][FIELD_SIZE];

  bool more_lines = true;
  while (more_lines) {

    fields_extracted = pdp_file_parse_new_line (config_file, 
						MAX_FIELDS, 
						FIELD_SIZE, 
						fields);

    switch (fields_extracted) {
    case -2: {
      printf ("File read error, exiting!\n");
      exit(EXIT_FAILURE);
    }
  
    case -1: {
      printf ("End of file reached, no more lines to get\n");
      more_lines = false;
      break;
    }

    default: {
      // process the data
      if (fields_extracted > 0) { // was any data extracted?
	// if so, process the data
	int f;
	for (f = 0; f < fields_extracted; f++) {
	  printf ("%s\n", fields[f]);
	}
	// else do nothing
      }
    }
    }

  }

  return 0;

}
