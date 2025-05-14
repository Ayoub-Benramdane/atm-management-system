#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void registerUser()
{
    system("clear");
    char name[50];
    char password[50];
    char password2[50];
    struct User u;
    FILE *ptr = fopen(USERS, "a+");
    printf("\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Registration:");
    printf("\n\n\t\t\t\tEnter the username: ");
    scanf("%s", name);
    if (checkUsername(name))
    {
        printf("\n\n\t\t\t\tUsername already exists!");
        waiting();
        registerUser();
        fclose(ptr);
    }
    faildPassword:
    printf("\n\n\t\t\t\tEnter the password: ");
    scanf("%s", password);
    char lowerName[50];
    char lowerPassword[50];
    strcpy(lowerName, name);
    strcpy(lowerPassword, password);
    toLower(lowerName);
    toLower(lowerPassword);
    printf("\n\n\t\t\t\tPassword: %s\n %ld", password, strlen(password));
    if (!checkPassword(lowerName, lowerPassword)) {
        waiting();
        goto faildPassword;
        fclose(ptr);
    }
    printf("\n\n\t\t\t\tConfirm password:");
    scanf("%s", password2);
    if (strcmp(password, password2) == 0)
    {
        u.id = rand() % 100000;
        strcpy(u.name, name);
        strcpy(u.password, password);
        saveUserToFile(ptr, u);
        printf("\n\n\t\t\t\tRegistration successful!");
        waiting();
        loginMenu(u.name, u.password);
    }
    else
    {
        printf("\n\n\t\t\t\tWrong password!");
        waiting();
        goto faildPassword;
        fclose(ptr);
    }
}

void loginMenu()
{
    struct User u;
    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login: ");
    scanf("%s", u.name);

    if (!checkUsername(u.name)) {
        printf("\n\n\t\t\t\tUsername does not exist!");
        waiting();
        checker:
        printf("\n\n\t\t\t\tEnter 0 to go back to the main menu or 1 to correct your imput or 2 to exit the program\n\n\t\t\t\tEnter your choice: ");
        char exitNumber[1];
        scanf("%s", exitNumber);
        if (strcmp(exitNumber, "0") != 0 && strcmp(exitNumber, "1") != 0 && strcmp(exitNumber, "2") != 0) {
            printf("\n\n\t\t\t\tInvalid input!");
            waiting();
            goto checker;
        }
        checkExit(exitNumber);
    } else {
        Password:
        printf("\n\n\t\t\t\tEnter the password: ");
        scanf("%s", u.password);
        if (checkLogin(u.name, u.password)) {
            printf("\n\n\t\t\t\tLogin successful!");
            waiting();
            mainMenu(u);
        } else {
            goto Password;
        }
    }
};


bool checkUsername(char username[50]) {
    FILE *ptr;
    struct User userChecker;
    if ((ptr = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(ptr, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, username) == 0)
        {
           return true;
        }
    }
    fclose(ptr);
    return false;
};


bool checkLogin(char username[50], char password[50]) {
    FILE *ptr;
    struct User userChecker;
    if ((ptr = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(ptr, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, username) == 0)
        {
           if (strcmp(userChecker.password, password) != 0) {
            printf("\n\n\t\t\t\tWrong password!");
            waiting();
            return false;
           }
        }
    }
    fclose(ptr);
    return true;
};

bool checkPassword( char username[50],char password[50]) {
    if (strstr(password, username) != 0) {
        printf("\n\n\t\t\t\tPassword can not contain username!\n");
        return false;
    } else if (strlen(password) < 8) {
        printf("\n\n\t\t\t\tPassword must be at least 8 characters long!\n");
        return false;
    } else if (strstr(password, " ") != 0) {
        printf("\n\n\t\t\t\tPassword can not contain spaces!\n");
        return false;
    }
    return true;
}

void saveUserToFile(FILE *ptr, struct User u) {
    int id;
    char name[50];
    char password[50];
    while (fscanf(ptr, "%d %s %s", &u.id, name, password) != EOF)
    {
        id = u.id;
    }
    
    fprintf(ptr, "%d %s %s\n", id+1, u.name, u.password);
    fclose(ptr);
}

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

void toLower(char *str) {
   while (*str)
   {
    *str = tolower(*str);
    str++;
   }
   
}

void checkExit(char exitNumber[1]) {
    struct  User u;
    if (strcmp(exitNumber, "0") == 0) {
        system("clear");
        initMenu(&u);
    } else if (strcmp(exitNumber, "1") == 0) {
        loginMenu();
    } else if (strcmp(exitNumber, "2") == 0) {
        exit(0);
    }
}