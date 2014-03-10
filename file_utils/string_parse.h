#ifndef string_parse_h
#define string_parse_h

#include <stdbool.h>

typedef struct generic_parameter {
  int id;
  char name[FIELD_SIZE];
  int data_int_1, data_int_2, data_int_3;
  double data_double_1, data_double_2, data_double_3;
  char data_text_1[FIELD_SIZE], data_text_2[FIELD_SIZE];
} GenericParameter;

typedef struct generic_parameter_set {

  GenericParameter parameter_1;
  GenericParameter parameter_2;
  GenericParameter parameter_3;
  GenericParameter parameter_4;
  GenericParameter parameter_5;

} GenericParameterSet;


void init_generic_parameter (GenericParameter * param);

void init_generic_parameter_set (GenericParameterSet *param_set);

void print_generic_parameter (GenericParameter * param);


void print_generic_parameter_set (GenericParameterSet * param);



bool pdp_file_parse_segmented_line (int max_fields, 
				    int field_size, 
				    char extracted_fields[max_fields][field_size],
				    GenericParameterSet * destination);
  // this function is program specific
  // contains switch statement instructing program how to parse extracted fields
  // (eg assign to parameters)
  // for a non-example program, break these out to separate functions
  // and put the whole thing in a separate import translator file



int pdp_file_segment_new_line (FILE *input_file, 
			       int max_fields, 
			       int field_size, 
			       char extracted_fields[max_fields][field_size]);
  // dimensions - extracted_fields[max_fields][field_size]
  // parses input file, segments it, filters it for comments etc
  // returns number of fields successfully extracted
  // returns 0 if line is empty,
  // returns -1 if EOF
  // returns -2 if error

int parse_file (FILE *config_file, GenericParameterSet *my_params);
  // example code to test string_parse functions 
  // change GenericParameterSet type to a program-specific struct containing parameters



#endif


