#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_PASSWORD_LENGTH 128
#define CHARSET_UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define CHARSET_LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define CHARSET_NUMBERS "0123456789"
#define CHARSET_SPECIAL "!@#$%^&*()_+-={}:<>?[]|"

typedef enum {
    WEAK,
    MEDIUM,
    STRONG
} password_strength_t;

typedef struct {
    int length;
    int use_uppercase;
    int use_lowercase;
    int use_numbers;
    int use_special;
} password_criteria_t;

void generate_password(password_criteria_t criteria, char *password) {
    char *charset = malloc(strlen(CHARSET_UPPERCASE) + strlen(CHARSET_LOWERCASE) + strlen(CHARSET_NUMBERS) + strlen(CHARSET_SPECIAL) + 1);
    strcpy(charset, "");

    if (criteria.use_uppercase) strcat(charset, CHARSET_UPPERCASE);
    if (criteria.use_lowercase) strcat(charset, CHARSET_LOWERCASE);
    if (criteria.use_numbers) strcat(charset, CHARSET_NUMBERS);
    if (criteria.use_special) strcat(charset, CHARSET_SPECIAL);

    for (int i = 0; i < criteria.length; i++) {
        int idx = rand() % strlen(charset);
        password[i] = charset[idx];
    }
    password[criteria.length] = '\0';

    free(charset);
}

password_strength_t estimate_password_strength(char *password) {
    int uppercase_count = 0;
    int lowercase_count = 0;
    int number_count = 0;
    int special_count = 0;

    for (int i = 0; i < strlen(password); i++) {
        char c = password[i];
        if (c >= 'A' && c <= 'Z') uppercase_count++;
        else if (c >= 'a' && c <= 'z') lowercase_count++;
        else if (c >= '0' && c <= '9') number_count++;
        else special_count++;
    }

    int entropy = 0;
    if (uppercase_count > 0) entropy += log2(strlen(CHARSET_UPPERCASE));
    if (lowercase_count > 0) entropy += log2(strlen(CHARSET_LOWERCASE));
    if (number_count > 0) entropy += log2(strlen(CHARSET_NUMBERS));
    if (special_count > 0) entropy += log2(strlen(CHARSET_SPECIAL));

    entropy *= strlen(password);

    if (entropy < 30) return WEAK;
    else if (entropy < 60) return MEDIUM;
    else return STRONG;
}

int main() {
    srand(time(NULL));

    password_criteria_t criteria;
    int num_passwords;

    printf("Enter password length (max %d): ", MAX_PASSWORD_LENGTH);
    scanf("%d", &criteria.length);
    if (criteria.length < 1 || criteria.length > MAX_PASSWORD_LENGTH) {
        printf("Invalid password length. Must be between 1 and %d.\n", MAX_PASSWORD_LENGTH);
        return 1;
    }

    printf("Include uppercase letters? (y/n): ");
    char uppercase_response;
    scanf(" %c", &uppercase_response);
    criteria.use_uppercase = (uppercase_response == 'y');

    printf("Include lowercase letters? (y/n): ");
    char lowercase_response;
    scanf(" %c", &lowercase_response);
    criteria.use_lowercase = (lowercase_response == 'y');

    printf("Include numbers? (y/n): ");
    char numbers_response;
    scanf(" %c", &numbers_response);
    criteria.use_numbers = (numbers_response == 'y');

    printf("Include special characters? (y/n): ");
    char special_response;
    scanf(" %c", &special_response);
    criteria.use_special = (special_response == 'y');

    printf("How many passwords to generate? ");
    scanf("%d", &num_passwords);

    FILE *password_file = fopen("passwords.txt", "w");
    if (password_file == NULL) {
        printf("Error creating password file.\n");
        return 1;
    }

    for (int i = 0; i < num_passwords; i++) {
        char password[MAX_PASSWORD_LENGTH + 1];
        generate_password(criteria, password);

        password_strength_t strength = estimate_password_strength(password);
        char *strength_str;
        switch (strength) {
            case WEAK:
                strength_str = "Weak";
                break;
            case MEDIUM:
                strength_str = "Medium";
                break;
            case STRONG:
                strength_str = "Strong";
                break;
        }

        printf("Password %d: %s (%s)\n", i + 1, password, strength_str);
        fprintf(password_file, "Password %d: %s\n", i + 1, password);
    }

    fclose(password_file);
    return 0;
}
