#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %19s %d %d/%d/%d %99s %s %lf %9s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) == 11;
}
void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    char *option;
    option = malloc(2);
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%s", option);
    if (strcmp(option, "1") != 0 && strcmp(option, "0") != 0)
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
    else if (strcmp(option, "1") == 0)
    {
        system("clear");
        mainMenu(u);
    }
    else if (strcmp(option, "0") == 0)
    {
        system("clear");
        exit(1);
    }
    free(option);
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
newAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");
    char *day;
    char *month;
    char *year;
    day = malloc(3);
    month = malloc(3);
    year = malloc(5);

    printf("\nEnter today's date(dd/mm/yyyy):");
    scanf("%s", day);
    scanf("%s", month);
    scanf("%s", year);
    printf("day: %s\nmonth: %s\nyear: %s\n", day, month, year);
    if (isDigit(day) == 0 || isDigit(month) == 0 || isDigit(year) == 0)
    {
        printf("Insert a valjknnid date!\n");
        waiting();
        goto newAccount;
    }
    r.deposit.month = atoi(month);
    r.deposit.day = atoi(day);
    r.deposit.year = atoi(year);
    free(day);
    free(month);
    free(year);
    printf("date: %d/%d/%d\n", r.deposit.month, r.deposit.day, r.deposit.year);
    if (r.deposit.month > 12 || r.deposit.month < 1 || r.deposit.day > 31 || r.deposit.day < 1 || r.deposit.year < 2020)
    {
        printf("Insert a valid date!\n");
        waiting();
        goto newAccount;
    }
accountNumber:
    printf("\nEnter the account number:");
    char *accountNumber;
    accountNumber = malloc(11);
    scanf("%s", accountNumber);
    if (isDigit(accountNumber) == 0)
    {
        printf("Insert a valid account number!");
        waiting();
        goto accountNumber;
    }
    r.accountNbr = atoi(accountNumber);
    free(accountNumber);
    if (r.accountNbr < 1000000000 || r.accountNbr > 9999999999)
    {
        printf("Insert a valid account number!");
        waiting();
        goto accountNumber;
    }
    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto accountNumber;
        }
    }
accountCountry:
    printf("\nEnter the country:");
    scanf("%s", r.country);
    if (isDigit(r.country) != 0)
    {
        printf("Insert a valid country!");
        waiting();
        goto accountCountry;
    }
accountPhone:
    printf("\nEnter the phone number:");
    char *phone;
    phone = malloc(11);
    scanf("%s", phone);
    if (isDigit(phone) == 0 || strlen(phone) != 10 || phone[0] != '0')
    {
        printf("Insert a valid phone number!");
        waiting();
        goto accountPhone;
    }
    strcpy(r.phone, phone);
// free(phone);
accountAmount:
    char *amount;
    amount = malloc(11);
    printf("\nEnter amount to deposit: $");
    scanf("%s", amount);
    char **slice;
    slice = malloc(2 * sizeof(char *));
    for (int i = 0; i < 2; i++)
    {
        slice[i] = malloc(10);
    }
    split(amount, slice);
    for (int i = 0; i < 2; i++)
    {
        if (isDigit(slice[i]) == 0)
        {
            printf("Insert a valid amount!");
            waiting();
            goto accountAmount;
        }
        free(slice[i]);
    }
    r.amount = atof(amount);
    free(amount);
AccountType:
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    char *accountType;
    accountType = malloc(11);
    scanf("%s", accountType);
    printf("%s ----- %s \n", r.phone, r.accountType);
    if (strcmp(accountType, "saving") != 0 && strcmp(accountType, "current") != 0 && strcmp(accountType, "fixed01") != 0 && strcmp(accountType, "fixed02") != 0 && strcmp(accountType, "fixed03") != 0)
    {
        printf("Insert a valid account type!\n");
        waiting();
        goto AccountType;
    }
    strcpy(r.accountType, accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            // printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
            //        r.accountNbr,
            //        r.deposit.day,
            //        r.deposit.month,
            //        r.deposit.year,
            //        r.country,
            //        r.phone,
            //        r.amount,
            //        r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void waiting()
{
    char spinner[] = {'|', '/', '-', '\\'};
    printf("\n");
    int counter = 0;
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            printf("\r%c waiting...", spinner[i]);
            fflush(stdout);
            usleep(100000);
        }
        counter++;
        if (counter == 5)
        {
            break;
        }
    }
}

int isDigit(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

void split(char *str, char **slice)
{
    char *str1;
    str1 = malloc(11);
    bool isfloat;
    int index = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '.' && !isfloat)
        {
            index = 0;
            slice[0] = str1;
            printf("%s", str1);
            str1 = malloc(11);
            isfloat = true;
            continue;
        }
        else if (!isfloat)
        {
            str1[index] = str[i];
        }
        else
        {
            str1[index] = str[i];
        }
        index++;
    }
    if (!isfloat)
    {
        slice[0] = "0";
    }
    printf("%s", str1);
    slice[1] = str1;
    printf("slice[0]: %s\n", slice[0]);
    printf("slice[1]: %s\n", slice[1]);
    // free(str1);
}