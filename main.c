
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>

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
                printf("\nPress any key to continue.");
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

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a valid choice.\n");
            system("pause");
            continue;
        }

        if (choice < 1 || choice > 3)
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

int displayCusMenu(char *userfullname)
{
    int cuschoice;

    while (1)
    {
        system("cls");
        printf("=========================================================\n");
        printf("          Welcome, %s           \n", userfullname);
        printf("=========================================================\n\n");

        printf("1. Reservation\n");
        printf("2. Your Reservation\n");
        printf("3. Edit account\n");
        printf("4. Log out\n");

        printf("Enter your choice: ");

        if (scanf("%d", &cuschoice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a valid choice.\n");
            system("pause");
            continue;
        }

        if (cuschoice < 1 || cuschoice > 4)
        {
            printf("Invalid choice. Please enter a valid option between 1-4.\n");
            system("pause");
        }
        else
        {
            break;
        }
    }

    return cuschoice;
}

int displayEmpMenu(char *userfullname)
{
    int Empchoice;

    while (1)
    {
        system("cls");
        printf("=========================================================\n");
        printf("          Welcome,Employee %s           \n", userfullname);
        printf("=========================================================\n\n");

        printf("1. Show Reservation\n");
        printf("2. Show Member\n");
        printf("3. Show Room\n");
        printf("4. Log out\n");

        printf("Enter your choice: ");

        if (scanf("%d", &Empchoice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a valid choice.\n");
            system("pause");
            continue;
        }

        if (Empchoice < 1 || Empchoice > 4)
        {
            printf("Invalid choice. Please enter a valid option between 1-4.\n");
            system("pause");
        }
        else
        {
            break;
        }
    }

    return Empchoice;
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
    char bed[50];
    char size[50];
    char Guests[50];
    char price[50];
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
        strcpy(room.bed, token);
        token = strtok(NULL, ",");
        strcpy(room.size, token);
        token = strtok(NULL, ",");
        strcpy(room.Guests, token);
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
        printf("Bed: %s\n", current->data.bed);
        printf("Room size: %s\n", current->data.size);
        printf("Guests : %s\n", current->data.Guests);
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
    char total[50];
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
        strcpy(reservation.total, token);
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

void displayUserReservation(struct RoomNode *roomsHead, struct ReservationNode *ReservationHead, int userid)
{
    system("cls"); // Clear the screen
    char UserID[50];
    sprintf(UserID, "%d", userid);
    printf("==========================================\n");
    printf("|         Your Reservation Details       |\n");
    printf("==========================================\n\n");
    if (ReservationHead == NULL)
    {
        printf("No reservations found.\n");
        return;
    }

    struct ReservationNode *Reservationcurrent = ReservationHead;

    while (Reservationcurrent != NULL)
    {
        if (strcmp(UserID, Reservationcurrent->data.memberID) == 0)
        {
            struct RoomNode *Roomcurrent = roomsHead;
            printf("Booking ID: %s--------------------\n", Reservationcurrent->data.bookingID);
            printf("Room ID: %s\n", Reservationcurrent->data.roomID);
            while (Roomcurrent != NULL)
            {
                if (strcmp(Reservationcurrent->data.roomID, Roomcurrent->data.roomID) == 0)
                {
                    printf("Room Type: %s\n", Roomcurrent->data.roomType);
                    printf("Bed: %s\n", Roomcurrent->data.bed);
                    printf("Room size: %s\n", Roomcurrent->data.size);
                    printf("Guests : %s\n", Roomcurrent->data.Guests);
                }
                Roomcurrent = Roomcurrent->next;
            }
            printf("Price Total : %s\n", Reservationcurrent->data.total);
            printf("Check-in Date: %s\n", Reservationcurrent->data.checkinDate);
            printf("Check-out Date: %s\n", Reservationcurrent->data.checkoutDate);
            printf("---------------------------------------------\n\n");
        }
        Reservationcurrent = Reservationcurrent->next;
    }

    printf("Press any key to back to menu...");
    getch(); // Wait for user input to continue
    return;
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
        printf("Price Total : %s\n", current->data.total);
        printf("Check-in Date: %s\n", current->data.checkinDate);
        printf("Check-out Date: %s\n", current->data.checkoutDate);
        printf("-------------------------------\n\n");

        current = current->next;
    }

    printf("Press any key to continue...");
    getch(); // Wait for user input to continue
}

bool validateDate(const char *date)
{
    int day, month, year;
    // ใช้ sscanf เพื่อแยกวันที่, เดือน, และปีจากสตริง
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3)
    {
        // รูปแบบไม่ถูกต้อง
        return false;
    }

    if (year < 2022 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        printf("1");
        return false;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        printf("2");
        return false;
    }
    else if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            if (day > 29)
            {
                printf("3");
                return false;
            }
        }
        else
        {
            if (day > 28)
            {
                printf("4");
                return false;
            }
        }
    }

    return true;
}

bool isDateBefore(const char *checkinDate, const char *checkoutDate)
{
    int checkinDay, checkinMonth, checkinYear;
    int checkoutDay, checkoutMonth, checkoutYear;

    if (sscanf(checkinDate, "%d/%d/%d", &checkinDay, &checkinMonth, &checkinYear) != 3 ||
        sscanf(checkoutDate, "%d/%d/%d", &checkoutDay, &checkoutMonth, &checkoutYear) != 3)
    {
        return false; // รูปแบบวันที่ไม่ถูกต้อง
    }

    if (checkinYear < checkoutYear ||
        (checkinYear == checkoutYear && checkinMonth < checkoutMonth) ||
        (checkinYear == checkoutYear && checkinMonth == checkoutMonth && checkinDay < checkoutDay))
    {
        return true; // checkinDate อยู่ก่อน checkoutDate
    }

    return false; // checkinDate ไม่อยู่ก่อน checkoutDate
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

int CheckRoomAvailable(struct ReservationNode *ReservationHead, int RoomID, char *checkinDate, char *checkoutDate)
{
    struct ReservationNode *currentReservation = ReservationHead;
    char RoomidInput[50];
    sprintf(RoomidInput, "%d", RoomID);

    struct tm checkin_tm;
    struct tm checkout_tm;
    struct tm checkin_res_tm;
    struct tm checkout_res_tm;

    memset(&checkin_tm, 0, sizeof(struct tm));
    memset(&checkout_tm, 0, sizeof(struct tm));
    memset(&checkin_res_tm, 0, sizeof(struct tm));
    memset(&checkout_res_tm, 0, sizeof(struct tm));

    int day, month, year;

    if (sscanf(checkinDate, "%d/%d/%d", &day, &month, &year) != 3)
    {
        // การแปลงวันที่ไม่สำเร็จ
        printf("Invalid check-in date format.\n");
        return -1;
    }
    checkin_tm.tm_mday = day;
    checkin_tm.tm_mon = month - 1;
    checkin_tm.tm_year = year - 1900;

    if (sscanf(checkoutDate, "%d/%d/%d", &day, &month, &year) != 3)
    {
        // การแปลงวันที่ไม่สำเร็จ
        printf("Invalid check-out date format.\n");
        return -1;
    }
    checkout_tm.tm_mday = day;
    checkout_tm.tm_mon = month - 1;
    checkout_tm.tm_year = year - 1900;

    while (currentReservation != NULL)
    {
        if (strcmp(RoomidInput, currentReservation->data.roomID) == 0)
        {
            if (sscanf(currentReservation->data.checkinDate, "%d/%d/%d", &day, &month, &year) != 3)
            {
                // การแปลงวันที่ไม่สำเร็จ
                printf("Invalid date format in reservation data.\n");
                return -1;
            }
            checkin_res_tm.tm_mday = day;
            checkin_res_tm.tm_mon = month - 1;
            checkin_res_tm.tm_year = year - 1900;

            if (sscanf(currentReservation->data.checkoutDate, "%d/%d/%d", &day, &month, &year) != 3)
            {
                // การแปลงวันที่ไม่สำเร็จ
                printf("Invalid date format in reservation data.\n");
                return -1;
            }
            checkout_res_tm.tm_mday = day;
            checkout_res_tm.tm_mon = month - 1;
            checkout_res_tm.tm_year = year - 1900;

            if (mktime(&checkin_tm) <= mktime(&checkout_res_tm) && mktime(&checkout_tm) >= mktime(&checkin_res_tm))
            {
                // หากมีการจองในช่วงเวลานี้
                return 1;
            }
        }
        currentReservation = currentReservation->next;
    }

    // ห้องไม่ถูกจองในช่วงเวลาที่กำหนด
    return 0;
}

int calculateNights(int checkinday, int checkinmonth, int checkinyear, int checkoutday, int checkoutmonth, int checkoutyear)
{
    int nights = 0;

    while (checkinday != checkoutday || checkinmonth != checkoutmonth || checkinyear != checkoutyear)
    {
        nights++;
        checkinday++;

        if ((checkinday == 31 && (checkinmonth == 4 || checkinmonth == 6 || checkinmonth == 9 || checkinmonth == 11)) ||
            (checkinday == 32 && !(checkinmonth == 4 || checkinmonth == 6 || checkinmonth == 9 || checkinmonth == 11)))
        {
            checkinday = 1;
            checkinmonth++;
        }

        if (checkinmonth > 12)
        {
            checkinmonth = 1;
            checkinyear++;
        }
    }

    return nights;
}

void SaveReservation(int userID, int roomID, char *checkinDate, char *checkoutDate, char *bookingID, int total)
{
    printf("%d", total);
    FILE *file = fopen("Reservation.csv", "a");
    if (file == NULL)
    {
        printf("Failed to open Reservation.csv for writing.\n");
        return;
    }

    fprintf(file, "%s,%d,%d,%d,%s,%s\n", bookingID, userID, roomID, total, checkinDate, checkoutDate);

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
        Sleep(5000);
    }
    printf("Payment verification complete!\n");
    getch();
}

int Booking(struct RoomNode *roomsHead, int UserRoomId, int userID, char *checkinDate, char *checkoutDate)
{
    char checkinDateSend[50];
    char checkoutDateSend[50];
    strcpy(checkinDateSend, checkinDate);
    strcpy(checkoutDateSend, checkoutDate);

    int datecheckin = atoi(strtok(checkinDate, "/"));
    int monthcheckin = atoi(strtok(NULL, "/"));
    int yearcheckin = atoi(strtok(NULL, "/"));

    int datecheckout = atoi(strtok(checkoutDate, "/"));
    int monthcheckout = atoi(strtok(NULL, "/"));
    int yearcheckout = atoi(strtok(NULL, "/"));

    char UserRoom[50];
    struct RoomNode *currentRoom = roomsHead;
    int returnToMainMenu = 0;

    while (currentRoom != NULL)
    {
        printf("Room %s ---------------------- \n", currentRoom->data.roomID);
        if (atoi(currentRoom->data.roomID) == UserRoomId)
        {
            system("cls");
            printf("=====================================\n");
            printf("|        Booking                    |\n");
            printf("=====================================\n\n");
            printf("Room %s ---------------------- \n", currentRoom->data.roomID);
            printf("Type : %s \n", currentRoom->data.roomType);
            printf("Bed: %s\n", currentRoom->data.bed);
            printf("Room size: %s\n", currentRoom->data.size);
            printf("Guests : %s\n", currentRoom->data.Guests);
            printf("Price per night : %s\n\n", currentRoom->data.price);
            printf("Input '99' to return to the main menu...\n\n");

            int nights = calculateNights(datecheckin, monthcheckin, yearcheckin, datecheckout, monthcheckout, yearcheckout);

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
                printf("Check in Date : %s\n", checkinDateSend);
                printf("Check out Date : %s\n", checkoutDateSend);
                printf("Total price for %d nights: %d\n", nights, total);

                char bookingID[50];
                sprintf(bookingID, "%d", generateBookingID(userID));

                int roomidReser = atoi(currentRoom->data.roomID);

                printf("Press any key to make a payment...\n");
                getch();
                payment();
                printf("Press any key when you paid...\n");
                SaveReservation(userID, roomidReser, checkinDateSend, checkoutDateSend, bookingID, total);
                getch();
                printf("---------------------------------------------");

                return roomidReser;
            }
            break;
        }
        currentRoom = currentRoom->next;
    }

    if (currentRoom == NULL)
    {
        printf("Room with ID %d not found.\n", UserRoomId);
        getch();
    }
}

int displayAvailableRooms(struct RoomNode *roomsHead, struct ReservationNode *ReservationHead, char *checkinDate, char *checkoutDate, int userid)
{
    struct ReservationNode *currentReservation = ReservationHead;
    struct RoomNode *currentRoom = roomsHead;
    int availableRoomCount = 0;
    int availableRoomIDs[100];
    int RoomID;
    struct tm checkin_tm;
    struct tm checkout_tm;

    memset(&checkin_tm, 0, sizeof(struct tm));
    memset(&checkout_tm, 0, sizeof(struct tm));

    int day, month, year;

    if (sscanf(checkinDate, "%d/%d/%d", &day, &month, &year) != 3)
    {
        // การแปลงวันที่ไม่สำเร็จ
        printf("Invalid date format.\n");
        return -1;
    }

    checkin_tm.tm_mday = day;
    checkin_tm.tm_mon = month - 1;
    checkin_tm.tm_year = year - 1900;

    if (sscanf(checkoutDate, "%d/%d/%d", &day, &month, &year) != 3)
    {
        // การแปลงวันที่ไม่สำเร็จ
        printf("Invalid date format.\n");
        return -1;
    }

    checkout_tm.tm_mday = day;
    checkout_tm.tm_mon = month - 1;
    checkout_tm.tm_year = year - 1900;

    while (currentRoom != NULL)
    {
        int isRoomBooked = 0;

        while (currentReservation != NULL)
        {
            struct tm checkin_res_tm;
            struct tm checkout_res_tm;

            memset(&checkin_res_tm, 0, sizeof(struct tm));
            memset(&checkout_res_tm, 0, sizeof(struct tm));

            if (strcmp(currentRoom->data.roomID, currentReservation->data.roomID) == 0)
            {
                if (sscanf(currentReservation->data.checkinDate, "%d/%d/%d", &day, &month, &year) != 3)
                {
                    // การแปลงวันที่ไม่สำเร็จ
                    printf("Invalid date format in reservation data.\n");
                    return -1;
                }

                checkin_res_tm.tm_mday = day;
                checkin_res_tm.tm_mon = month - 1;
                checkin_res_tm.tm_year = year - 1900;

                if (sscanf(currentReservation->data.checkoutDate, "%d/%d/%d", &day, &month, &year) != 3)
                {
                    // การแปลงวันที่ไม่สำเร็จ
                    printf("Invalid date format in reservation data.\n");
                    return -1;
                }

                checkout_res_tm.tm_mday = day;
                checkout_res_tm.tm_mon = month - 1;
                checkout_res_tm.tm_year = year - 1900;

                if (mktime(&checkin_tm) <= mktime(&checkout_res_tm) && mktime(&checkout_tm) >= mktime(&checkin_res_tm))
                {
                    // หากมีการจองในช่วงเวลานี้
                    isRoomBooked = 1;
                    break;
                }
            }
            currentReservation = currentReservation->next;
        }

        if (!isRoomBooked)
        {
            // เพิ่ม RoomID ลงในอาร์เรย์
            availableRoomIDs[availableRoomCount] = atoi(currentRoom->data.roomID);
            availableRoomCount++;

            // แสดงข้อมูลของห้องว่าง
            printf("Room %s ---------------------- \n", currentRoom->data.roomID);
            printf("Type : %s \n", currentRoom->data.roomType);
            printf("Bed: %s\n", currentRoom->data.bed);
            printf("Room size: %s\n", currentRoom->data.size);
            printf("Guests : %s\n", currentRoom->data.Guests);
        }

        // รีเซ็ตตัวชี้การจองกลับไปที่หัว
        currentReservation = ReservationHead;
        currentRoom = currentRoom->next;
    }

    if (availableRoomCount == 0)
    {
        printf("No available rooms in the specified period.\n");
    }

    while (1)
    {
        printf("Choose a room (or 0 to go back to the main menu): ");
        scanf("%d", &RoomID);

        if (RoomID == 0)
        {
            return 0;
        }

        int isRoomValid = 0;
        int i;
        for (i = 0; i < availableRoomCount; i++)
        {
            if (availableRoomIDs[i] == RoomID)
            {
                isRoomValid = 1;
                Booking(roomsHead, RoomID, userid, checkinDate, checkoutDate);
                return RoomID;
            }
        }

        if (!isRoomValid)
        {
            printf("\nInvalid room id input");
        }
    }
}

// ฟังก์ชันแสดงรายการห้องที่ว่างและให้ผู้ใช้เลือก
int RoomAvailable(struct RoomNode *roomsHead, struct ReservationNode *ReservationHead, int userid)
{
    char checkinDate[50];
    char checkoutDate[50];
    system("cls");

    while (1)
    {
        printf("Enter a Check in date (dd/mm/yyyy): ");
        scanf("%s", checkinDate);

        if (strcmp(checkinDate, "99/99/9999") == 0)
        {
            return 0;
        }

        if (!validateDate(checkinDate))
        {
            printf("Invalid check-in date. Please enter a valid date.\n");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("Enter a Check out date (dd/mm/yyyy): ");
        scanf("%s", checkoutDate);

        if (strcmp(checkoutDate, "99/99/9999") == 0)
        {
            return 0;
        }

        if (!validateDate(checkoutDate) || !isDateBefore(checkinDate, checkoutDate))
        {
            printf("Invalid check-out date. Please enter a valid date.\n");
        }
        else
        {
            break;
        }
    }

    printf("=====================================\n");
    printf("|        Room Available               |\n");
    printf("=====================================\n\n");
    return displayAvailableRooms(roomsHead, ReservationHead, checkinDate, checkoutDate, userid);
}

bool isAlpha(const char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool isAlphaNumeric(const char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isalnum(str[i]))
        {
            return false;
        }
    }
    return true;
}

// ฟังก์ชั่นเขียนข้อมูลสมาชิกลงในไฟล์ CSV
void registration(struct Node *memberHead)
{
    char latestMemberID[50] = "0";
    struct Node *current = memberHead;

    while (current != NULL)
    {
        if (atoi(current->data.memberID) > atoi(latestMemberID))
        {
            strcpy(latestMemberID, current->data.memberID);
        }
        current = current->next;
    }

    int newMemberID = atoi(latestMemberID) + 1;
    char role[50] = "customer";
    char firstName[50], lastName[50], username[50], password[50], tel[50];
    int age;
    system("cls");
    printf("%d\n", newMemberID);
    printf("==============================\n");
    printf("|         Registration       |\n");
    printf("==============================\n\n");

    printf("Enter first name: ");
    while (1)
    {
        scanf("%s", firstName);
        if (!isAlpha(firstName))
        {
            printf("Invalid input for first name. Please enter only alphabetic characters.\n");
        }
        else
        {
            break;
        }
    }

    printf("Enter last name: ");
    while (1)
    {
        scanf("%s", lastName);
        if (!isAlpha(lastName))
        {
            printf("Invalid input for last name. Please enter only alphabetic characters.\n");
        }
        else
        {
            break;
        }
    }

    printf("Enter username: ");
    while (1)
    {
        scanf("%s", username);
        if (!isAlphaNumeric(username))
        {
            printf("Invalid input for username. Please enter only alphanumeric characters.\n");
        }
        else
        {
            break;
        }
    }

    printf("Enter password: ");
    scanf("%s", password);
    // You can add more password validation here if needed.

    printf("Enter Age: ");
    while (1)
    {
        if (scanf("%d", &age) != 1)
        {
            printf("Invalid input for age. Please enter a valid number.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer.
        }
        else
        {
            break;
        }
    }

    printf("Enter tel: ");
    scanf("%s", tel);

    FILE *file = fopen("member.csv", "a");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open CSV file\n");
        exit(1);
    }

    fprintf(file, "%d,%s,%s,%s,%d,%s,%s,%s\n", newMemberID, firstName, lastName, role, age, username, password, tel);

    fclose(file);
}

int main()
{
    struct Node *memberHead = NULL;
    memberDataRead(&memberHead);

    struct RoomNode *roomHead = NULL;
    RoomDataRead(&roomHead);

    struct ReservationNode *reservationHead = NULL;
    reservationDataRead(&reservationHead);

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
                            loggedIn = 1;
                            while (loggedIn)
                            {
                                char userfullname[50];
                                strcpy(userfullname, user->data.firstName);
                                strcat(userfullname, " ");
                                strcat(userfullname, user->data.lastName);

                                if (strcmp(user->data.role, "customer") == 0)
                                { // Use double quotes for string comparison
                                    int cuschoice;
                                    int userId = atoi(loggedInUser);
                                    cuschoice = displayCusMenu(userfullname);
                                    if (cuschoice == 1)
                                    {
                                        int roomIdReservation = RoomAvailable(roomHead, reservationHead, userId);
                                        reservationDataRead(&reservationHead);
                                    }
                                    else if (cuschoice == 2)
                                    {
                                        displayUserReservation(roomHead, reservationHead, userId);
                                    }
                                    else if (cuschoice == 3)
                                    {
                                        // Edit account
                                    }
                                    else if (cuschoice == 4)
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
                                else if (strcmp(user->data.role, "employee") == 0)
                                { // Use double quotes for string comparison
                                    int Empchoice;
                                    Empchoice = displayEmpMenu(userfullname);
                                    if (Empchoice == 1)
                                    {
                                        displayReservation(reservationHead);
                                    }
                                    else if (Empchoice == 2)
                                    {
                                        displayMembers(memberHead);
                                    }
                                    else if (Empchoice == 3)
                                    {
                                        displayRoom(roomHead);
                                    }
                                    else if (Empchoice == 4)
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
                            }
                            break;
                        }
                        user = user->next;
                    }
                }
            }
            else if (choice == 2)
            {
                registration(memberHead);
                memberDataRead(&memberHead);
            }
            else if (choice == 3)
            {
                printf("Exiting the program...\n");
                exit(0);
            }
            else
            {
                printf("Invalid choice. Please try again.\n");
            }
        }
        else
        {
            // Handle actions for a logged-in user
        }
    }
    return 0;
}
