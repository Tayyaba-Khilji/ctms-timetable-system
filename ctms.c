#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DAYS 4
#define MAX_PERIODS 4
#define MAX_ROOMS 4
#define MAX_SLOTS 4

typedef struct {
    char subject[50];
    char teacher[50];
    char department[50];
    char room[50];
} Timetable;

// Predefined rooms
char rooms[MAX_ROOMS][20] = {"ROOM R    ", "ROOM G    ", "ROOM K    ", "LAB CLO6  "};

// Timetable storage
Timetable timetable[MAX_SLOTS][MAX_DAYS];

// Room occupancy tracking
int roomsOccupied[MAX_SLOTS][MAX_ROOMS] = {0};

void generateTimetable(char subject[], char teacher[], char department[]) {
    int periods = MAX_PERIODS;

    printf("\nGenerated Timetable:\n");
    printf("Subject: %s | Teacher: %s | Department: %s\n\n", subject, teacher, department);


    printf("Time Slot / Day        Monday                  Tuesday                 Wednesday               Thursday\n");
    printf("                       %-23s %-23s %-23s %-23s\n", rooms[0], rooms[1], rooms[2], rooms[3]);
    printf("--------------------------------------------------------------------------------------------------------------\n");

    srand(time(0));

    int assigned = 0;
    while (assigned < periods) {
        int day = rand() % MAX_DAYS;
        int slot = rand() % MAX_SLOTS;
        int roomIdx = rand() % MAX_ROOMS;

        // Check if this room and slot is already occupied
        if (roomsOccupied[slot][roomIdx] == 0 && strlen(timetable[slot][day].subject) == 0) {
            roomsOccupied[slot][roomIdx] = 1;
            strcpy(timetable[slot][day].subject, subject);
            strcpy(timetable[slot][day].teacher, teacher);
            strcpy(timetable[slot][day].department, department);
            strcpy(timetable[slot][day].room, rooms[roomIdx]);
            assigned++;
        }
    }

    // Printing the timetable with subjects
    for (int i = 0; i < MAX_SLOTS; i++) {
        printf("%-24s", (i == 0) ? "9:00 AM - 10:00 AM" :
                              (i == 1) ? "10:00 AM - 11:00 AM" :
                              (i == 2) ? "11:00 AM - 12:00 PM" : "12:00 PM - 1:00 PM");

        // Print subjects for each day
        for (int j = 0; j < MAX_DAYS; j++) {
            if (strlen(timetable[i][j].subject) > 0) {
                printf("%-23s ", timetable[i][j].subject);
            } else {
                printf("                         ");
            }
        }
        printf("\n");
    }
}

// Function to check if all slots are occupied
int isTimetableFull() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        for (int j = 0; j < MAX_ROOMS; j++) {
            if (roomsOccupied[i][j] == 0) {
                return 0; // Still some slots available
            }
        }
    }
    return 1;
}

int main() {
    char subject[50], teacher[50], department[50];
    char choice;

    do {
        if (isTimetableFull()) {
            printf("\nAll time slots and rooms are fully occupied. Thank you!\n");
            break;
        }


        printf("\nEnter the teacher's name: ");
        scanf(" %[^\n]s", teacher);
        printf("Enter the subject: ");
        scanf(" %[^\n]s", subject);
        printf("Enter the department: ");
        scanf(" %[^\n]s", department);


        generateTimetable(subject, teacher, department);


        if (!isTimetableFull()) {
            printf("\nDo you want to generate another timetable? (y/n): ");
            scanf(" %c", &choice);
        } else {
            printf("\nAll time slots and rooms are fully occupied. Thank you!\n");
            break;
        }
    } while (choice == 'y' || choice == 'Y');

    return 0;
}