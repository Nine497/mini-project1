#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct Member
{
    char memberID[50];
    char firstName[50];
    char lastName[50];
    char role[50];
    char age[10];
    char username[50];
    char password[50];
    char tel[50];
};

struct Node
{
    struct Member data;
    struct Node *next;
};

void memberDataRead(struct Node **head)
{
    FILE *file = fopen("member.csv", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open CSV file\n");
        exit(1);
    }

    char line[1024];
    int skipFirstLine = 1;

    while (fgets(line, sizeof(line), file))
    {
        if (skipFirstLine)
        {
            skipFirstLine = 0;
            continue;
        }

        char *token = strtok(line, ",");
        struct Member member;

        strcpy(member.memberID, token);
        token = strtok(NULL, ",");
        strcpy(member.firstName, token);
        token = strtok(NULL, ",");
        strcpy(member.lastName, token);
        token = strtok(NULL, ",");
        strcpy(member.role, token);
        token = strtok(NULL, ",");
        strcpy(member.age, token);
        token = strtok(NULL, ",");
        strcpy(member.username, token);
        token = strtok(NULL, ",");
        strcpy(member.password, token);
        token = strtok(NULL, ",");
        strcpy(member.tel, token);

        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        memcpy(&newNode->data, &member, sizeof(struct Member));
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            struct Node *current = *head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    fclose(file);
}

void displayLogin(struct Node *head, char loggedInUser[])
{
    int loginAttempts = 0;

    while (loginAttempts < 3)
    {
        system("clear");
        printf("=====================================\n");
        printf("|             Login                |\n");
        printf("=====================================\n\n");

        char username[50];
        char password[50];
        printf("Username: ");
        scanf("%s", username);

        printf("Password: ");
        scanf("%s", password);

        struct Node *current = head;

        while (current != NULL)
        {
            if (strcmp(current->data.username, username) == 0 &&
                strcmp(current->data.password, password) == 0)
            {
                printf("Welcome, %s!\n", current->data.firstName);
                strcpy(loggedInUser, current->data.memberID);
                getch();
                return;
            }
            current = current->next;
        }

        printf("\nLogin failed. Username or password is incorrect. %d attempts remaining.\n", 2 - loginAttempts);
        sleep(3);
        loggedInUser[0] = '\0';
        loginAttempts++;
    }

    printf("\nMaximum login attempts reached.\n");
}

int displayMenu()
{
    int choice;
    system("clear");
    printf("=====================================\n");
    printf("|           Login System           |\n");
    printf("=====================================\n\n");

    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("4. Show member\n");
    printf("5. Show member\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    return choice;
}

int displayCusMenu()
{
    int cuschoice;
    system("clear");
    printf("=====================================\n");
    printf("|           Customer Menu           |\n");
    printf("=====================================\n\n");

    printf("1. Reservation\n");
    printf("2. Change Username\n");
    printf("3. Change Password\n");
    printf("4. Change Name\n");
    printf("5. Log out\n");

    printf("Enter your choice: ");
    scanf("%d", &cuschoice);

    return cuschoice;
}

void displayMembers(struct Node *head)
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    system("clear");
    printf("=====================================\n");
    printf("|          Member List             |\n");
    printf("=====================================\n\n");

    struct Node *current = head;
    int memberCount = 1;

    while (current != NULL)
    {
        printf("Member %d:\n", memberCount);
        printf("Member ID: %s\n", current->data.memberID);
        printf("First Name: %s\n", current->data.firstName);
        printf("Last Name: %s\n", current->data.lastName);
        printf("Role: %s\n", current->data.role);
        printf("Age: %s\n", current->data.age);
        printf("Username: %s\n", current->data.username);
        printf("Password: %s\n", current->data.password);
        printf("Tel : %s\n", current->data.tel);
        printf("\n");

        current = current->next;
        memberCount++;
    }
}

struct Room
{
    char roomID[50];
    char roomType[50];
    char price[50];
    char status[50];
};

struct RoomNode
{
    struct Room data;
    struct RoomNode *next;
};

void RoomDataRead(struct RoomNode **head)
{
    FILE *file = fopen("RoomData.csv", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open CSV file\n");
        exit(1);
    }

    char line[1024];
    int skipFirstLine = 1;

    while (fgets(line, sizeof(line), file))
    {
        if (skipFirstLine)
        {
            skipFirstLine = 0;
            continue;
        }

        char *token = strtok(line, ",");
        struct Room room;
        strcpy(room.roomID, token);

        token = strtok(NULL, ",");
        strcpy(room.roomType, token);
        token = strtok(NULL, ",");
        strcpy(room.status, token);
        token = strtok(NULL, ",");
        strcpy(room.price, token);

        struct RoomNode *newNode = (struct RoomNode *)malloc(sizeof(struct RoomNode));
        if (newNode == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        memcpy(&newNode->data, &room, sizeof(struct Room));
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            struct RoomNode *current = *head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    fclose(file);
}

void displayRoom(struct RoomNode *head)
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    system("clear");
    printf("=====================================\n");
    printf("|          Room List               |\n");
    printf("=====================================\n\n");

    struct RoomNode *current = head;
    int roomCount = 1;

    while (current != NULL)
    {
        printf("Room %d:\n", roomCount);
        printf("Room ID: %s\n", current->data.roomID);
        printf("Room Type: %s\n", current->data.roomType);
        printf("Price: %s\n", current->data.price);
        printf("Status: %s\n", current->data.status);
        printf("\n");

        current = current->next;
        roomCount++;
    }
}

struct Reservation
{
    char bookingID[50];
    char memberID[50];
    char roomID[50];
    char checkinDate[50];
    char checkoutDate[50];
};

struct ReservationNode
{
    struct Reservation data;
    struct ReservationNode *next;
};

int displayReservationMenu()
{
    int cusRMchoice;
    while (1)
    {
        system("clear");
        printf("=====================================\n");
        printf("|        Make a Reservation         |\n");
        printf("=====================================\n\n");

        printf("1. Make a Reservation\n");
        printf("2. Go Back to Customer Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &cusRMchoice);
        return cusRMchoice;
    }
}

void reservationDataRead(struct ReservationNode **ReservationHead)
{
    FILE *file = fopen("Reservation.csv", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open reservation.csv file\n");
        exit(1);
    }

    char line[1024];
    int skipFirstLine = 1;

    while (fgets(line, sizeof(line), file))
    {
        if (skipFirstLine)
        {
            skipFirstLine = 0;
            continue;
        }

        char *token = strtok(line, ",");
        struct Reservation reservation;

        strcpy(reservation.bookingID, token);
        token = strtok(NULL, ",");
        strcpy(reservation.memberID, token);
        token = strtok(NULL, ",");
        strcpy(reservation.roomID, token);
        token = strtok(NULL, ",");
        strcpy(reservation.checkinDate, token);
        token = strtok(NULL, ",");
        strcpy(reservation.checkoutDate, token);

        struct ReservationNode *newNode = (struct ReservationNode *)malloc(sizeof(struct ReservationNode));
        if (newNode == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        memcpy(&newNode->data, &reservation, sizeof(struct Reservation));
        newNode->next = NULL;

        if (*ReservationHead == NULL)
        {
            *ReservationHead = newNode;
        }
        else
        {
            struct ReservationNode *current = *ReservationHead;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    fclose(file);
}

int RoomAvailable(struct RoomNode *roomsHead)
{
    char RoomID;
    struct RoomNode *currentRoom = roomsHead;
    system("clear");
    printf("=====================================\n");
    printf("|        Room Available               |\n");
    printf("=====================================\n\n");
    while (currentRoom != NULL)
    {
        if (strcmp(currentRoom->data.status, "Vacant") == 0)
        {
            printf("Room %s ---------------------- \n", currentRoom->data.roomID);
            printf("Type : %s \n", currentRoom->data.roomType);
            printf("Status : %s \n\n", currentRoom->data.status);
        }
        currentRoom = currentRoom->next;
    }

    printf("Choose a room :");
    scanf("%d", &RoomID);
    return RoomID;
}

int calculateNights(int checkinday, int checkinmonth, int checkinyear, int checkoutday, int checkoutmonth, int checkoutyear)
{
    int nights = (checkoutyear - checkinyear) * 360 + (checkoutmonth - checkinmonth) * 30 + (checkoutday - checkinday);
    return nights;
}

void Booking(struct RoomNode *roomsHead, int UserRoomId)
{
    int Checkinday, Checkinmonth, Checkinyear, Checkoutday, Checkoutmonth, Checkoutyear;
    char UserRoom[50];
    struct RoomNode *currentRoom = roomsHead;
    while (currentRoom != NULL)
    {
        if (atoi(currentRoom->data.roomID) == UserRoomId)
        {
            if (strcmp(currentRoom->data.status, "Vacant") == 0)
            {
                system("clear");
                printf("=====================================\n");
                printf("|        Booking                    |\n");
                printf("=====================================\n\n");
                printf("Room %s ---------------------- \n", currentRoom->data.roomID);
                printf("Type : %s \n", currentRoom->data.roomType);
                printf("Status : %s \n\n", currentRoom->data.status);
                printf("Price per night : %s", currentRoom->data.price);
                printf("Enter a Check in date (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &Checkinday, &Checkinmonth, &Checkinyear);
                if (Checkinday <= 0 || Checkinday > 30 || Checkinmonth <= 0 || Checkinmonth > 12 || Checkinyear < 2566)
                {
                    printf("Invalid check-in date.\n");
                    getch();
                    break;
                };
                printf("Enter a Check out date (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &Checkoutday, &Checkoutmonth, &Checkoutyear);
                if (Checkoutday <= 0 || Checkoutday > 30 || Checkoutmonth <= 0 || Checkoutmonth > 12 || Checkoutyear < 2566)
                {
                    printf("Invalid check-out date.\n");
                    getch();
                    break;
                }
                else
                {
                    int nights = calculateNights(Checkinday, Checkinmonth, Checkinyear, Checkoutday, Checkoutmonth, Checkoutyear);

                    if (nights <= 0)
                    {
                        printf("Invalid dates. Check-out date must be after check-in date.\n");
                        getch();
                    }
                    else
                    {
                        int roomPrice = atoi(currentRoom->data.price);
                        int total = nights * roomPrice;
                        printf("Total price for %d nights: %d\n", nights, total);
                        getch();
                    }

                    break;
                }
            }
            else
            {
                printf("Room with ID %d is already booked.\n", UserRoomId);
                getch();
                break;
            }
        }

        currentRoom = currentRoom->next;
    }

    if (currentRoom == NULL)
    {
        printf("Room with ID %d not found.\n", UserRoomId);
        getch();
    }
}

int main()
{
    struct Node *memberHead = NULL;
    memberDataRead(&memberHead);

    struct RoomNode *roomHead = NULL;
    RoomDataRead(&roomHead);

    struct ReservationNode *ReservationHead = NULL;
    reservationDataRead(&ReservationHead);

    int loggedIn = 0;
    char loggedInUser[50] = "";

    struct Node *user = NULL;

    while (1)
    {
        int choice;
        if (!loggedIn)
        {
            choice = displayMenu();

            switch (choice)
            {
            case 1:
                displayLogin(memberHead, loggedInUser);
                if (loggedInUser[0] != '\0')
                {
                    user = memberHead;
                    while (user != NULL)
                    {
                        if (strcmp(user->data.memberID, loggedInUser) == 0)
                        {
                            loggedIn = 1;
                            break;
                        }
                        user = user->next;
                    }
                    if (loggedIn)
                    {
                        if (strcmp(user->data.role, "customer") == 0)
                        {
                            while (loggedIn)
                            {
                                int cuschoice, roomIdReservation;
                                cuschoice = displayCusMenu();

                                switch (cuschoice)
                                {
                                case 1:
                                    roomIdReservation = RoomAvailable(roomHead);
                                    Booking(roomHead, roomIdReservation);
                                    break;
                                case 2:
                                    // Change Username
                                    break;
                                case 3:
                                    // Change Username
                                    break;
                                case 4:
                                    // Change Password
                                    break;
                                case 5:
                                    // Change Name
                                    break;
                                case 6:
                                    // Change Tel.
                                    break;
                                case 7:
                                    // Logout
                                    loggedIn = 0;
                                    loggedInUser[0] = '\0';
                                    break;
                                default:
                                    printf("Invalid choice. Please try again.\n");
                                }
                            }
                        }
                        else if (strcmp(user->data.role, "admin") == 0)
                        {
                            while (loggedIn)
                            {
                            }
                        }
                        else if (strcmp(user->data.role, "employee") == 0)
                        {
                        }
                    }
                }
                break;
            case 2:
                // Implement registration logic here
                break;
            case 3:
                printf("Exiting the program...\n");
                exit(0);
                break;
            case 4:
                // Display member information here
                break;
            case 5:
                // Display room information here
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        else
        {
            // Handle actions for a logged-in user based on their role
            // This part is handled within the nested loops
        }
    }
    return 0;
}
