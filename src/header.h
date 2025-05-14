#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[20];
    char country[100];
    char phone[10];
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// exit function
void checkExit(char exitNumber[1]);

// waiting function
void waiting();

// authentication functions
void registerUser();
bool checkUsername(char username[50]);
void toLower(char *str);
bool checkPassword(char password[50], char username[50]);
bool checkLogin(char username[50], char password[50]);
void saveUserToFile(FILE *ptr, struct User u);
void loginMenu();
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void initMenu(struct User *u);
void checkAllAccounts(struct User u);
int isDigit(char *str);
void split(char *str, char **slice);
