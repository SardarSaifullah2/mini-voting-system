#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Start();
void AdminMenu();
void Register();
void Login();
void AdminDashBoard();

struct User
{
    char name[50];
    char password[50];
};

int main()
{
    Start();
    return 0;
}

void Start()
{
    int choice;
    while (1)
    {
        printf("\n1. Amdin Panel \n 2. Voter Panel \n 3. Exit \n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Admin Panel\n");
            AdminMenu();
            break;
        case 2:
            printf("Voter Panel\n");
            break;
        case 3:
            printf("Exit\n");
            return;
            break;
        default:
            printf("Invalid Choice\n");
        }
    }
}

void AdminMenu()
{
    int choice;
    while (1)
    {
        printf("\n1. Register \n 2. Login \n 3. Exit \n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Register\n");
            Register();
            break;
        case 2:
            printf("Login\n");
            Login();
            break;
        case 3:
            printf("Exit\n");
            exit(0);
            break;
        default:
            printf("Invalid Choice\n");
        }
    }
}
void Register()
{
    char name[50], password[50];
    int lenght;
    struct User user;
    printf("Enter Your Username : ");
    scanf("%s", user.name);
    lenght = strlen(user.name);
    if (lenght < 5)
    {
        printf("Username must be greater than 5 characters");
        return;
    }
    printf("Enter Your Password :");
    scanf("%s", user.password);

    lenght = strlen(user.password);
    if (lenght < 5)
    {
        printf("Password must be greater than 5 characters");
        return;
    }
    FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project/admin.txt", "a");
    if (file == NULL)
    {
        printf("File not found");
        return;
    }
    fprintf(file, "%s %s\n", user.name, user.password);
    fclose(file);
    printf(" User created Successfully");
}

void Login()
{
    struct User user;
    FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project/admin.txt", "r");

    printf("Enter Your Username : ");
    scanf("%s", user.name);
    char name[50], password[50];
    int found = 0;

    if (file == NULL)
    {
        printf("File not found");
        return;
    }

    printf("Enter Your Password : ");
    scanf("%s", user.password);

    while (fscanf(file, "%s %s", name, password) != EOF)
    {
        if (strcmp(name, user.name) == 0 && strcmp(password, user.password) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("Login Successful\n");
        AdminDashBoard();
    }
    else
    {
        printf("Invalid Username or Password\n");
    }
}

void AdminDashBoard()
{
    int choice;
    while (1)
    {
        printf("\n1. Create Election\n2. Delete Election\n3. Delete Illegal Votes\n4. View Election Result\n5. View Previous Election Results\n6. BlackList Voter\n7. Exit\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Create ELection\n");
            break;
        case 2:
            printf("Delete Election\n");
            break;
        case 3:
            printf("Delete Illegal Votes\n");
            break;
        case 4:
            printf("View Election Result\n");
            break;
        case 5:
            printf("View Previous Election\n");
            break;
        case 6:
            printf("BlackList\n");
            break;
        case 7:
            printf("Exit\n");
            exit(0);
            break;
        default:
            printf("Invalid Choice\n");
        }
    }
}