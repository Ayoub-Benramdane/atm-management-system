#include "header.h"

void mainMenu(struct User u)
{
    char option[100];
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    printf("\n\t\t\tEnter Your Choice: ");
    scanf("%s", option);
    if (strlen(option) > 1)
    {
        printf("Insert a valid operation!\n");
        waiting();
        mainMenu(u);
    }
    switch (*option)
    {
    case '1':
        createNewAcc(u);
        break;
    case '2':
        // student TODO : add your **Update account information** function
        // here
        break;
    case '3':
        // student TODO : add your **Check the details of existing accounts** function
        // here
        break;
    case '4':
        checkAllAccounts(u);
        break;
    case '5':
        // student TODO : add your **Make transaction** function
        // here
        break;
    case '6':
        // student TODO : add your **Remove existing account** function
        // here
        break;
    case '7':
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case '8':
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    char option[100];
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    printf("\n\t\t\tEnter Your Choice: ");
    while (!r)
    {
        scanf("%s", option);
        if (strlen(option) > 1)
        {
            printf("Insert a valid operation!\n");
            waiting();
            initMenu(u);
        }
        switch (*option)
        {
        case '1':
            waiting();
            loginMenu();
            r = 1;
            break;
        case '2':
            waiting();
            registerUser();
            r = 1;
            break;
        case '3':
            waiting();
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
            waiting();
            initMenu(u);
        }
    }
};

int main()
{
    struct User u;

    initMenu(&u);
    return 0;
}
