#include <stdbool.h>
#define CREDENTIALS_FILE_PATH "/home/patrik/Projects/password-manager/credentials.txt"


void add_credentials(credentials_t credentials);
credentials_t *load_credentials_from_file(size_t *cred_len);
void free_credentials_array(credentials_t *credentials, size_t len);
bool load_specific_credentials(char *service_name, credentials_t *credentials);
