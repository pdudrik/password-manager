#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "command.h"


arg_t* parse_input(int argc, char** argv, int* args_len) {
	if (argc == 1) {
		return NULL;
	}

	arg_t *args = (arg_t *) malloc(sizeof(arg_t));
	
	for (int i=1; i<argc; i=i+2) {
		arg_t new_arg;
		// check for  params -p, -u or -s
		if (argv[i][0] == '-' || strlen(argv[i]) == 2) {		
			 
			char param = argv[i][1];
			printf("Comparing param = %c\n", param);
			switch (param) {
				case 'u':
					new_arg.param_key = USERNAME_TYPE;
					break;

				case 'p':
					new_arg.param_key = PASSWORD_TYPE;
					break;

				case 's':
					new_arg.param_key = SERVICE_TYPE;
					break;
			
				default:
					fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
					return NULL;
					break;
			}
	
			if (argv[i+1] == NULL) {
				printf("Error: Missing argument for %c\n", param);
				return NULL;
			}
		}

		else {
			if (!strcmp("show", argv[i]) && !strcmp("list", argv[i+1])) {
				new_arg.param_key = SHOW_LIST_TYPE;
			}
			else if (!strcmp("show", argv[i])) {
				new_arg.param_key = SHOW_SPECIFIC_SERVICE_TYPE;
			}
			else {
				fprintf(stderr, "Unknown error during comparison: %s and %s\n", argv[i], argv[i+1]);
				return NULL;
			}
		}
		
			
		new_arg.value = argv[i+1];
		(*args_len)++;

		args = (arg_t *) realloc(args, (sizeof(arg_t ) * (*args_len)));
		args[*args_len-1] = new_arg;	
	}
	return args;
}


void free_args(arg_t *args) {
	free(args);
}


void print_parsed_input(arg_t *args, int len) {
	for (int i=0; i<len; i++) {

		switch (args[i].param_key) {
			case ADD_TYPE:
				printf("param_key=%s, value=%s\n", "ADD", args[i].value);
				break;

			case SHOW_LIST_TYPE:
				printf("param_key=%s, value=%s\n", "SHOW LIST", args[i].value);
				break;

			case SHOW_SPECIFIC_SERVICE_TYPE:
				printf("param_key=%s, value=%s\n", "SHOW SPECIFIC SERVICE", args[i].value);
				break;

			case DELETE_TYPE:
				printf("param_key=%s, value=%s\n", "DELETE", args[i].value);
				break;

			case USERNAME_TYPE:
				printf("param_key=%s, value=%s\n", "USERNAME", args[i].value);
				break;

			case PASSWORD_TYPE:
				printf("param_key=%s, value=%s\n", "PASSWORD", args[i].value);
				break;

			case SERVICE_TYPE:
				printf("param_key=%s, value=%s\n", "SERVICE", args[i].value);
				break;		
		
		}
	}

}


credentials_t parse_row_data(char* row) {
	credentials_t credentials;
	
	/*
	char *token = strtok(row, "-");
	while(token != NULL) {
		printf("%s ", token);
		token = strtok(NULL, "-");
	}
	printf("\n");
	*/
	
	char* token = strtok(row, "-");
	printf("SPLITED SERVICE: %s\n", token);
	credentials.service = strdup(token);
	printf("struct.service: %s\n", credentials.service);
	//memcpy(credentials.service, token, strlen(token));
	//strcpy(credentials.service, token);
	
	token = strtok(NULL, "-");
	printf("SPLITED USERNAME: %s\n", token);
	credentials.username = strdup(token);
	//strcpy(credentials.username, token);
	
	token = strtok(NULL, "-");
	printf("SPLITED PASSWORD: %s\n", token);
	credentials.password = strdup(token);
	//strcpy(credentials.password, token);
	


	return credentials;
}
