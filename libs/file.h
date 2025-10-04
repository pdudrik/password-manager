#define CREDENTIALS_FILE_PATH "/home/patrik/Projects/password-manager/credentials.txt"


void add_credentials(credentials_t credentials);
credentials_t *load_credentials_from_file(size_t *cred_len);

