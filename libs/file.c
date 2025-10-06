#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
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
		size_t row_len = 0;
		char **row_data = parse_string(row, "-", &row_len);

		credentials[(*cred_len)-1].service = strdup(row_data[0]);
		credentials[(*cred_len)-1].username = strdup(row_data[1]);
		credentials[(*cred_len)-1].password = strdup(row_data[2]);
		
		for (int i=0; i<row_len; i++) {
			free(row_data[i]);
		}
		free(row_data);
		
	}
	fclose(file);
	
	return credentials;
}


void free_credentials_array(credentials_t *credentials, size_t len) {
	for (int i=0; i<len; i++) {
		free(credentials[i].service);
		free(credentials[i].username);
		free(credentials[i].password);
	}
	free(credentials);
}


bool load_specific_credentials(char *service_name, credentials_t *credentials) {
	FILE *file = fopen(CREDENTIALS_FILE_PATH, "r");
	bool match = false;

	if (file == NULL) {
		printf("File does not exists\n");
		fclose(file);
		return match;
	}

	int c = fgetc(file);
	if (isspace((unsigned char) c)) {
		printf("File is empty\n");
		fclose(file);
		return match;
	}
	ungetc(c, file);
	
	char row[100];
	while (!match) {
		char *temp = fgets(row, sizeof(row), file);
		if (feof(file)) {
			printf("ROW IS empty\n");
			fclose(file);
			return match;
		}
		
		size_t size = 0;
		char **row_data = parse_string(row, "-", &size);
		if (!strcmp(row_data[0], service_name)) {
			credentials->service = strdup(row_data[0]);
			credentials->username = strdup(row_data[1]);
			credentials->password = strdup(row_data[2]);
			match = true;
		}
	
		for (int i=0; i<size; i++) {
			free(row_data[i]);
		}
		free(row_data);
	
	}
	fclose(file);
	

	return match;
}


bool delete_specific_credentials(char *target_row) {
	FILE *origin, *temp_file;
	origin = fopen(CREDENTIALS_FILE_PATH, "r");

	if (origin == NULL) {
		printf("File does not exists\n");
		//fclose(origin);
		return false;
	}

	int c = fgetc(origin);
	if (isspace((unsigned char) c)) {
		printf("File is empty\n");
		fclose(origin);
		return false;
	}
	ungetc(c, origin);
	
	temp_file = fopen(CREDENTIALS_TEMP_FILE_PATH, "w");

	if (temp_file == NULL) {
		printf("File does not exists\n");
		fclose(origin);
		return false;
	}


	size_t origin_file_size = 0;
//	char **origin_file_data;
	char row[100];
	while (fgets(row, sizeof(row), origin)) {
		origin_file_size++;
//		origin_file_data = realloc(origin_file_data,
//								   origin_file_size * sizeof(char *));
//		origin_file_data[origin_file_size-1] = strdup(row);
		
		// exclude specified credentials
		if (strcmp(row, target_row)) {
			fputs(row, temp_file);
		}
	}

	fclose(origin);
	fclose(temp_file);
	
	// stdlib.h functions
	remove(CREDENTIALS_FILE_PATH);	
	rename(CREDENTIALS_TEMP_FILE_PATH, CREDENTIALS_FILE_PATH);
	return true;
}













