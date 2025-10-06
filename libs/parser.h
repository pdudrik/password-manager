#ifndef PARSER_H_
#define PARSER_H_

#include "command.h"

/*
typedef enum CommandType {
	ADD,
    SHOW_LIST,
    SHOW_SPECIFIC_SERVICE,
    DELETE
} command_type_t;


typedef struct Command {
	command_type_t command_type;
	char *value;
} command_t;
*/

typedef struct Crendentials {
	char *service;
	char *username;
	char *password;
} credentials_t;


typedef enum ArgType {
	NOT_DEFINED,
	ADD_TYPE,
	SHOW_LIST_TYPE,
	SHOW_SPECIFIC_SERVICE_TYPE,
	DELETE_TYPE,
	USERNAME_TYPE,
	SERVICE_TYPE,
	PASSWORD_TYPE
} arg_type_t;


typedef struct Arg {
	arg_type_t param_key;
	char *value;
} arg_t;



/*
typedef enum ParamType {
	NOT_DEFINED,
	SERVICE,
	USERNAME,
	PASSWORD
} param_type_t;
*/



/*
typedef struct arg {
	param_type_t param_type;
	char* value;
} arg_t;
*/

arg_t *parse_input(int argc, char** argv, int* args_len);
void free_args(arg_t *args);
void print_parsed_input(arg_t *args, int len);
credentials_t parse_row_data(char* row);
char **parse_string(char *row, char *delim, size_t *size); 

#endif
