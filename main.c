#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "command.h"
#include "file.h"


void fill_credentials(credentials_t *credentials, arg_t* args);


int main(int argc, char **argv) {
	for (int i=0; i<argc; i++) {
		printf("argv[%d]= %s\n", i, argv[i]);
	}
	printf("\n");

	int args_len = 0;
	
	
	arg_t* args = parse_input(argc, argv, &args_len);
	if (args == NULL) {
		fprintf(stderr, "Error: No args were parsed\n");
		return 0;
	}

	print_parsed_input(args, args_len);
	//credentials_t credentials;

	switch (args[0].param_key) {
		/*
		case USERNAME_TYPE:
		case PASSWORD_TYPE:
		case SERVICE_TYPE:
			credentials_t credentials;
			fill_credentials(&credentials, args);
			add_credentials(credentials);
			printf("Credentials for \"%s\" were added sucessfully!\n",
					credentials.service);
			break;
		*/
		/*
		case ADD_TYPE:
			add_credentials(credentials);
			break;
		*/

		case DELETE_TYPE:
			// delete specific credentials
			break;

		case SHOW_LIST_TYPE:
			// print all credential services
			size_t cred_len = 0;
			credentials_t *credentials = load_credentials_from_file(&cred_len);
			printf("Credentials (service):\n");
			if (credentials == NULL) {
				printf("- no credentials\n");
			}

			for (size_t i=0; i<cred_len; i++) {
				printf("- %s\n", credentials[i].service);
			}
			printf("\n");
			free_credentials_array(credentials, cred_len);
			break;

		case SHOW_SPECIFIC_SERVICE_TYPE:
			// show specific credentials by service
			credentials_t target;
			bool loaded_credentials = load_specific_credentials(args[0].value, &target);	
			if (loaded_credentials == false) {
				printf("Credentials for service \"%s\" were not found!\n",
						args[0].value);
				break;
			}
			
			printf("FOUND MATCH!\nService: %s\nUsername: %s\nPassword: %s\n",
					target.service, target.username, target.password);
			
			free(target.service);
			free(target.username);	
			free(target.password);
			break;
	}
	


//	printf("service= %s, username=%s, password=%s\n",
//		   credentials.service, credentials.username, credentials.password);
	
	free_args(args);

	return 0;
}



void fill_credentials(credentials_t *credentials, arg_t *args) {
	for (int i=0; i<3; i++) {
		switch (args[i].param_key) {
			case USERNAME_TYPE:
				credentials->username = args[i].value;
				break;

			case PASSWORD_TYPE:
				credentials->password = args[i].value;
				break;

			case SERVICE_TYPE:
				credentials->service = args[i].value;
				break;
		}
	}
}

