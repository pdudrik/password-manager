#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include "parser.h"
#include "file.h"


void add_credentials(credentials_t credentials) {
	FILE *file = fopen(CREDENTIALS_FILE_PATH, "a+");

	if (file == NULL) {
		printf("error during openning the file\n");
		return;
	}
	char data[50];
	strcpy(data, credentials.service);
	strcat(data, "-");
	strcat(data, credentials.username);
	strcat(data, "-");
	strcat(data, credentials.password);
	strcat(data, "\n");
	fputs(data, file);
	fclose(file);
}


credentials_t *load_credentials_from_file(size_t *cred_len) {
	FILE *file = fopen(CREDENTIALS_FILE_PATH, "r");

	if (file == NULL) {
		printf("File does not exists\n");
		fclose(file);
		return NULL;
	}

	int c = fgetc(file);
	if (isspace((unsigned char) c)) {
		printf("File is empty\n");
		fclose(file);
		return NULL;
	}
	ungetc(c, file);

	credentials_t *credentials = (credentials_t *) malloc(sizeof(credentials_t));
	//(*cred_len)++;
	char row[100];
	while (fgets(row, sizeof(row), file)) {
		printf("ROW: %s\n", row);
		if (feof(file)) {
			printf("ROW IS empty\n");
		}
		(*cred_len)++;
		credentials = realloc(credentials, ((*cred_len)) * sizeof(credentials_t));
		credentials[(*cred_len)-1] = parse_row_data(row);
	}
	fclose(file);
	
	return credentials;
}


