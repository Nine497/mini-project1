#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

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

    while (1)
    {
        system("cls");
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

        printf("\nLogin failed. Username or password is incorrect.\n");
        printf("\nPress any key to login again or press 'Q' to back to main menu.");
        int key = getch();
        if (key == 'Q' || key == 'q')
        {
            return;
        }
        getch();
        loggedInUser[0] = '\0';
    }
}

int displayMenu()
{
    int choice;

    while (1)
    {
        system("cls");
        printf("=====================================\n");
        printf("|           Login System           |\n");
        printf("=====================================\n\n");

        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("4. Show members\n");
        printf("5. Show Room\n");
        printf("6. Show Reservation\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a valid choice.\n");
            system("pause");
            continue;
        }

        if (choice < 1 || choice > 6)
        {
            printf("Invalid choice. Please enter a valid option between 1-5.\n");
            system("pause");
        }
        else
        {
            break;
        }
    }

    return choice;
}

int displayCusMenu()
{
    int cuschoice;

    while (1)
    {
        system("cls");
        printf("=====================================\n");
        printf("|           Customer Menu           |\n");
        printf("=====================================\n\n");

        printf("1. Reservation\n");
        printf("2. Edit account\n");
        printf("3. Log out\n");

        printf("Enter your choice: ");

        if (scanf("%d", &cuschoice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a valid choice.\n");
            system("pause");
            continue;
        }

        if (cuschoice < 1 || cuschoice > 3)
        {
            printf("Invalid choice. Please enter a valid option between 1-3.\n");
            system("pause");
        }
        else
        {
            break;
        }
    }

    return cuschoice;
}

void displayMembers(struct Node *head)
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    system("cls");
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
        printf("Tel : %s", current->data.tel);
        printf("-------------------------------\n\n");

        current = current->next;
        memberCount++;
    }
    system("pause");
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
    system("cls");
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
        printf("Price per night: %s", current->data.price);
        printf("Status: %s\n", current->data.status);
        printf("-------------------------------\n");
        current = current->next;
        roomCount++;
    }
    system("pause");
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
        system("cls");
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

void displayReservation(struct ReservationNode *ReservationHead)
{
    system("cls"); // Clear the screen

    printf("=====================================\n");
    printf("|         Reservation Details       |\n");
    printf("=====================================\n\n");

    if (ReservationHead == NULL)
    {
        printf("No reservations found.\n");
        return;
    }

    struct ReservationNode *current = ReservationHead;

    while (current != NULL)
    {
        printf("Booking ID: %s\n", current->data.bookingID);
        printf("Member ID: %s\n", current->data.memberID);
        printf("Room ID: %s\n", current->data.roomID);
        printf("Check-in Date: %s\n", current->data.checkinDate);
        printf("Check-out Date: %s\n", current->data.checkoutDate);
        printf("-------------------------------\n\n");

        current = current->next;
    }

    printf("Press any key to continue...");
    getch(); // Wait for user input to continue
}

int isDateBefore(int day1, int month1, int year1)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (year1 < (tm.tm_year + 1900))
    {
        return 1;
    }
    else if (year1 > (tm.tm_year + 1900))
    {
        return 0;
    }
    else if (month1 < (tm.tm_mon + 1))
    {
        return 1;
    }
    else if (month1 > (tm.tm_mon + 1))
    {
        return 0; //
    }
    else if (day1 < tm.tm_mday)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

long generateBookingID(int userID)
{
    time_t current_time;
    time(&current_time);

    struct tm *time_info = localtime(&current_time);

    long bookingID = (long)(time_info->tm_year + 1900) * 1000000 + (long)(time_info->tm_mon + 1) * 10000 + (long)time_info->tm_mday * 100 + (long)time_info->tm_hour * 10000 + (long)time_info->tm_min * 100 + (long)time_info->tm_sec;

    bookingID += userID;

    return bookingID;
}

int isRoomAvailable(struct RoomNode *roomsHead, const char *roomID)
{
    struct RoomNode *currentRoom = roomsHead;

    while (currentRoom != NULL)
    {
        if (strcmp(currentRoom->data.roomID, roomID) == 0 && strcmp(currentRoom->data.status, "Occupied") == 0)
        {
            return 0;
        }
        currentRoom = currentRoom->next;
    }

    return 1;
}

int RoomAvailable(struct RoomNode *roomsHead)
{
    char RoomID[10];
    system("cls");
    printf("=====================================\n");
    printf("|        Room Available               |\n");
    printf("=====================================\n\n");

    struct RoomNode *currentRoom = roomsHead;
    int roomCount = 0;

    while (currentRoom != NULL)
    {
        if (strcmp(currentRoom->data.status, "Occupied") == 1)
        {
            printf("Room %s ---------------------- \n", currentRoom->data.roomID);
            printf("Type : %s \n", currentRoom->data.roomType);
            printf("Status : %s \n\n", currentRoom->data.status);
            roomCount++;
        }
        currentRoom = currentRoom->next;
    }

    if (roomCount == 0)
    {
        printf("No rooms are currently available.\n");
        printf("Press 0 to go back to the main menu: ");
        scanf("%s", RoomID);

        if (strcmp(RoomID, "0") == 0)
        {
            return 0;
        }

        printf("Invalid choice. Please try again.\n");
        return -1;
    }

    while (1)
    {
        printf("Choose a room (or 0 to go back to the main menu): ");
        scanf("%s", RoomID);

        if (strcmp(RoomID, "0") == 0)
        {
            return 0;
        }

        if (isRoomAvailable(roomsHead, RoomID))
        {
            return atoi(RoomID);
        }
        else
        {
            printf("Room with ID %s is already booked.\n", RoomID);
        }
    }
}

int calculateNights(int checkinday, int checkinmonth, int checkinyear, int checkoutday, int checkoutmonth, int checkoutyear)
{
    int nights = (checkoutyear - checkinyear) * 360 + (checkoutmonth - checkinmonth) * 30 + (checkoutday - checkinday);

    return nights;
}

void SaveReservation(int userID, int roomID, char *checkinDate, char *checkoutDate, char *bookingID)
{
    FILE *file = fopen("Reservation.csv", "a");
    if (file == NULL)
    {
        printf("Failed to open Reservation.csv for writing.\n");
        return;
    }

    fprintf(file, "%s,%d,%d,%s,%s\n", bookingID, userID, roomID, checkinDate, checkoutDate);

    fclose(file);
}

void payment()
{
    printf("|-----------------------------------|\n");
    printf("|                                   |\n");
    printf("|                                   |\n");
    printf("|              QR CODE              |\n");
    printf("|                                   |\n");
    printf("|                                   |\n");
    printf("|-----------------------------------|\n");
    return;
}

void printLoadingAnimation(int seconds)
{
    char animation[] = "|/-\\";
    int i;
    for (i = 0; i < seconds * 2; i++)
    {
        printf("Waiting for payment verification... %c\r", animation[i % 4]);
        fflush(stdout);
        usleep(500000);
    }
    printf("Payment verification complete!\n");
}

int Booking(struct RoomNode *roomsHead, int UserRoomId, int userID)
{
    int Checkinday, Checkinmonth, Checkinyear, Checkoutday, Checkoutmonth, Checkoutyear;
    char UserRoom[50];
    struct RoomNode *currentRoom = roomsHead;
    int returnToMainMenu = 0;

    while (currentRoom != NULL)
    {
        if (atoi(currentRoom->data.roomID) == UserRoomId)
        {
            if (strcmp(currentRoom->data.status, "Occupied") == 1)
            {
                system("cls");
                printf("=====================================\n");
                printf("|        Booking                    |\n");
                printf("=====================================\n\n");
                printf("Room %s ---------------------- \n", currentRoom->data.roomID);
                printf("Type : %s \n", currentRoom->data.roomType);
                printf("Status : %s \n", currentRoom->data.status);
                printf("Price per night : %s\n\n", currentRoom->data.price);
                printf("Input '99' to return to the main menu...\n\n");

                while (1)
                {
                    printf("Enter a Check in date (dd/mm/yyyy): ");
                    scanf("%d/%d/%d", &Checkinday, &Checkinmonth, &Checkinyear);

                    if (Checkinday == 99)
                    {
                        returnToMainMenu = 1;
                        break;
                    }

                    if (Checkinday <= 0 || Checkinday > 30 || Checkinmonth <= 0 || Checkinmonth > 12 || Checkinyear < 2021)
                    {
                        printf("Invalid check-in date.\n");
                        getch();
                    }
                    else if (!isDateBefore(Checkinday, Checkinmonth, Checkinyear))
                    {
                        printf("Invalid check-in date. Check-out date must be after today's date.\n");
                        getch();
                    }
                    else
                    {
                        break;
                    }
                }

                if (returnToMainMenu)
                {
                    break;
                }

                while (1)
                {
                    printf("Enter a Check out date (dd/mm/yyyy): ");
                    scanf("%d/%d/%d", &Checkoutday, &Checkoutmonth, &Checkoutyear);

                    if (Checkoutday == 99)
                    {
                        returnToMainMenu = 1;
                        break;
                    }

                    if (Checkoutday <= 0 || Checkoutday > 30 || Checkoutmonth <= 0 || Checkoutmonth > 12 || Checkoutyear < 2021)
                    {
                        printf("Invalid check-out date.\n");
                        getch();
                    }
                    else if (!isDateBefore(Checkoutday, Checkoutmonth, Checkoutyear))
                    {
                        printf("Invalid check-out date. Check-out date must be after today's date.\n");
                        getch();
                    }
                    else
                    {
                        break;
                    }
                }

                if (returnToMainMenu)
                {
                    break;
                }

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
                    printf("---------------------------------------------\n");
                    printf("Total price for %d nights: %d\n", nights, total);

                    char bookingID[50];
                    sprintf(bookingID, "%d", generateBookingID(userID));

                    int roomidReser = atoi(currentRoom->data.roomID);

                    char checkindate[50];
                    sprintf(checkindate, "%d/%d/%d", Checkinday, Checkinmonth, Checkinyear);

                    char checkoutdate[50];
                    sprintf(checkoutdate, "%d/%d/%d", Checkoutday, Checkoutmonth, Checkoutyear);

                    SaveReservation(userID, roomidReser, checkindate, checkoutdate, bookingID);

                    printf("Press any key to make a payment...\n");
                    getch();
                    payment();
                    printf("Press any key when you paid...\n");
                    getch();
                    printf("---------------------------------------------");
                    printLoadingAnimation(5);

                    return roomidReser;
                }
                break;
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

void ChangeStatusRoom(int roomid, struct RoomNode *roomHead)
{
    struct RoomNode *currentRoom = roomHead;
    char roomID[50];
    sprintf(roomID, "%d", roomid);

    while (currentRoom != NULL)
    {
        if (strcmp(currentRoom->data.roomID, roomID) == 0)
        {
            strcpy(currentRoom->data.status, "Occupied");
            break;
        }
        currentRoom = currentRoom->next;
    }

    if (currentRoom == NULL)
    {
        printf("Room with ID %s not found.\n", roomID);
    }
    else
    {
        FILE *file = fopen("Roomdata.csv", "w");
        if (file == NULL)
        {
            printf("Failed to open Roomdata.csv for writing.\n");
            return;
        }

        fprintf(file, "roomID,roomType,status,price\n");

        currentRoom = roomHead;
        while (currentRoom != NULL)
        {
            fprintf(file, "%s,%s,%s,%s", currentRoom->data.roomID, currentRoom->data.roomType, currentRoom->data.status, currentRoom->data.price);
            currentRoom = currentRoom->next;
        }

        fclose(file);
        printf("\nYour Reservation successfully!.\n");
        system("pause");
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

            if (choice == 1)
            {
                displayLogin(memberHead, loggedInUser);
                if (loggedInUser[0] != '\0')
                {
                    struct Node *user = memberHead;
                    while (user != NULL)
                    {
                        if (strcmp(user->data.memberID, loggedInUser) == 0)
                        {
                            int loggedIn = 1;
                            while (loggedIn)
                            {
                                int cuschoice;
                                cuschoice = displayCusMenu();
                                if (cuschoice == 1)
                                {
                                    
                                    // int roomIdReservation = RoomAvailable(roomHead);
                                    // int userid = atoi(loggedInUser);
                                    // int roomidReser = Booking(roomHead, roomIdReservation, userid);
                                    // ChangeStatusRoom(roomidReser, roomHead);
                                    // reservationDataRead(&ReservationHead);
                                }
                                else if (cuschoice == 2)
                                {
                                    // Edit account
                                }
                                else if (cuschoice == 3)
                                {
                                    loggedIn = 0;
                                    loggedInUser[0] = '\0';
                                    break;
                                }
                                else
                                {
                                    printf("Invalid choice. Please try again.\n");
                                }
                            }
                            break;
                        }
                        user = user->next;
                    }
                }
            }
            else if (choice == 2)
            {
                // registration
            }
            else if (choice == 3)
            {
                printf("Exiting the program...\n");
                exit(0);
            }
            else if (choice == 4)
            {
                displayMembers(memberHead);
            }
            else if (choice == 5)
            {
                displayRoom(roomHead);
            }
            else if (choice == 6)
            {
                displayReservation(ReservationHead);
            }
            else
            {
                printf("Invalid choice. Please try again.\n");
            }
        }
        else
        {
            // Handle actions role
        }
    }
    return 0;
}
