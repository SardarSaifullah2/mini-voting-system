#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Start();
void AdminMenu();
void Register();
void Login();
void AdminDashBoard();
void CreateElection();
int CheckedELection();
int DeleteElection();
void DeleteIllegalVote();
void ViewElectionResult();
void BlackList_Voter();
struct User
{
    char name[50];
    char password[50];
};

struct Candidate
{
    char name[50];
    int vote;
};

struct BlackList_Voter
{
    char name[50];
};

struct Voter
{
    char name[50];
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
        printf("\n 1. Amdin Panel \n 2. Voter Panel \n 3. Exit \n Enter your choice: ");
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
        printf("\n 1. Register \n 2. Login \n 3. Exit \n Enter your choice: ");
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

    printf(" Enter Your Username : ");
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
        printf("Login Successful......\n");
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
        printf("\n 1. Create Election\n 2. Delete Election\n 3. Delete Illegal Votes\n 4. View Election Result\n 5. View Previous Election Results\n 6. BlackList Voter\n 7. Exit\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Create ELection\n");
            if (CheckedELection() == 1)
            {
                CreateElection();
            }
            else
            {
                printf("Election Already Created\n");
            }
            break;
        case 2:
            printf("Delete Election\n");
            if (DeleteElection() == 1)
            {
                printf("Election Deleted Successfully ...\n");
            }
            else
            {
                printf("Election Already Deleted\n");
            }
            break;
        case 3:
            printf("Delete Illegal Votes\n");
            DeleteIllegalVote();
            break;
        case 4:
            printf("View Election Result\n");
            ViewElectionResult();
            break;
        case 5:
            printf("View Previous Election\n");
            break;
        case 6:
            printf("BlackList\n");
            BlackList_Voter();
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

void CreateElection()
{
    int candidate_number;
    char candidate_name[50];

    printf("Enter the number of candidates : ");
    scanf("%d", &candidate_number);

    for (int i = 1; i <= candidate_number; i++)
    {
        FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project/candidate.txt", "a");
        if (file == NULL)
        {
            printf("File not Open");
            // return;
        }
        printf("Enter the name of candidate %d : ", i);
        scanf("%s", candidate_name);
        fprintf(file, "%s %d \n", candidate_name, 0);
        fclose(file);
        // return 1;
    }
    printf("Election Created Successfully........\n");
}

int CheckedELection()
{
    FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project/candidate.txt", "r");
    fseek(file, 0, SEEK_END);

    int fileSize = ftell(file);
    fclose(file);
    if (fileSize == 0)
    {
        return 1;
    }
    return 0;
}

int DeleteElection()
{
    FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project/candidate.txt", "w");
    if (file == NULL)
    {
        printf("File not Open");
        return 0;
    }
    fclose(file);
    return 1;
}

void DeleteIllegalVote()
{
    struct User user[100];
    int name, i = 0, choice, length;
    char names[40];

    FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project\\vote.txt", "r");

    if (file == NULL)
    {
        printf("File Not Found");
    }

    while (fscanf(file, "%s", names) != EOF)
    {
        strcpy(user[i].name, names);
        i++;
    }
    length = i;

    for (i = 0; i < length; i++)
    {
        printf("%d. %s\n", i + 1, user[i].name);
    }
    printf("Choose Option : ");
    scanf("%d", &choice);
    FILE *file_write = fopen("D:\\semester 2\\programming fundamental\\project\\main project\\vote.txt", "w");
    for (i = 0; i < length; i++)
    {
        if (strcmp(user[i].name, user[choice - 1].name) != 0)
        {
            fprintf(file_write, "%s\n", user[i].name);
        }
    }
    fclose(file_write);
}

void ViewElectionResult()
{
    printf("\n Inside View Election Result\n");
    struct Candidate candidate[10];
    int i = 0, length, vote;
    char names[40];

    FILE *file = fopen("D:\\semester 2\\programming fundamental\\project\\main project\\candidate.txt", "r");

    if (file == NULL)
    {
        printf("File Not Found");
    }

    while (fscanf(file, "%s %d\n", candidate[i].name, &candidate[i].vote) != EOF)
    {
        i++;
    }
    fclose(file);

    length = i;
    printf("Length : %d", length);

    for (i = 0; i < length; i++)
    {
        printf("\n %s %d \n", candidate[i].name, candidate[i].vote);
        printf("\n Press Enter to Continue\n");
        getchar();
    }
}

void BlackList_Voter()
{
    int i = 0, length, choice;
    struct BlackList_Voter blackList_voter[100];
    struct Voter voter[100];

    FILE *voter_file = fopen("D:\\semester 2\\programming fundamental\\project\\main project\\voter.txt", "r");
    if (voter_file == NULL)
    {
        printf("File not Open");
        return;
    }

    while (fscanf(voter_file, "%s %d", voter[i].name) != EOF)
    {
        printf("%s\n", voter[i].name);
        i++;
    }
    fclose(voter_file);
    length = i;
    for (i = 0; i < length; i++)
    {
        printf("%d. %s\n", i + 1, voter[i].name);
    }
    printf("Choose Option : ");
    scanf("%d", &choice);
    // FILE *voter_file_write = fopen("D:\\semester 2\\programming fundamental\\project\\main project\\voter.txt", "w");
    for (i = 0; i < length; i++)
    {
        // if (i != choice - 1)
        if (strcmp(voter[i].name, voter[choice - 1].name) == 0)
        {
            FILE *blackList_file = fopen("D:\\semester 2\\programming fundamental\\project\\main project\\blacklist.txt", "a");
            if (blackList_file == NULL)
            {
                printf("File not Open");
                return;
            }
            fprintf(blackList_file, "%s\n", voter[choice - 1].name);
            fclose(blackList_file);
        }
        // fclose(voter_file_write);
    }
}