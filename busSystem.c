#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 50

typedef struct {
    int seatNumber;
    char passengerName[50];
    int isBooked;
    char from[50];
    char to[50];
    char date[20];
} Seat;

Seat busSeats[MAX_SEATS];

void initializeSeats() {
    for (int i = 0; i < MAX_SEATS; i++) {
        busSeats[i].seatNumber = i + 1;
        busSeats[i].isBooked = 0;
    }
}

void loadSeatsFromFile() {
    FILE *file = fopen("bus_seats.txt", "r");
    if (file != NULL) {
        fread(busSeats, sizeof(Seat), MAX_SEATS, file);
        fclose(file);
    }
}

void saveSeatsToFile() {
    FILE *file = fopen("bus_seats.txt", "w");
    if (file != NULL) {
        fwrite(busSeats, sizeof(Seat), MAX_SEATS, file);
        fclose(file);
    }
}

void bookSeat() {
    char date[20];
    printf("Enter date (dd/mm/yyyy): ");
    scanf("%s", date);

    int availableSeats = MAX_SEATS;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (busSeats[i].isBooked && strcmp(busSeats[i].date, date) == 0) {
            availableSeats--;
        }
    }

    if (availableSeats <= 0) {
        printf("No available seats for the specified date.\n");
        return;
    }

    for (int i = 0; i < MAX_SEATS; i++) {
        if (!busSeats[i].isBooked) {
            printf("Enter passenger name: ");
            scanf("%s", busSeats[i].passengerName);
            printf("Enter 'from' place: ");
            scanf("%s", busSeats[i].from);
            printf("Enter 'to' place: ");
            scanf("%s", busSeats[i].to);
            strcpy(busSeats[i].date, date);
            busSeats[i].isBooked = 1;
            printf("Seat booked successfully\n");
            saveSeatsToFile();
            break;
        }
    }
}

void deleteBooking() {
    char date[20];
    printf("Enter date (dd/mm/yyyy) to check bookings: ");
    scanf("%s", date);

    // Display booked seats for the specified date
    int bookedSeats = 0;
    printf("Booked seats for %s:\n", date);
    for (int i = 0; i < MAX_SEATS; i++) {
        if (busSeats[i].isBooked && strcmp(busSeats[i].date, date) == 0) {
            printf("Seat %d - Passenger: %s\n", busSeats[i].seatNumber, busSeats[i].passengerName);
            bookedSeats++;
        }
    }

    if (bookedSeats == 0) {
        printf("No bookings found for the specified date.\n");
        return;
    }

    char passengerName[50];
    printf("Enter the passenger name you want to delete the booking for: ");
    scanf("%s", passengerName);

    int deleted = 0;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (busSeats[i].isBooked && strcmp(busSeats[i].date, date) == 0 && strcmp(busSeats[i].passengerName, passengerName) == 0) {
            busSeats[i].isBooked = 0;
            deleted++;
        }
    }

    if (deleted == 0) {
        printf("No bookings found for the specified passenger on the specified date.\n");
    } else {
        printf("Deleted %d bookings for the specified passenger on the specified date.\n", deleted);
        saveSeatsToFile();
    }
}

void updateBooking() {
    char date[20];
    printf("Enter date (dd/mm/yyyy) to update bookings: ");
    scanf("%s", date);

    int updated = 0;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (busSeats[i].isBooked && strcmp(busSeats[i].date, date) == 0) {
            printf("Current booking details for seat %d:\n", busSeats[i].seatNumber);
            printf("Passenger: %s, From: %s, To: %s, Date: %s\n", busSeats[i].passengerName, busSeats[i].from, busSeats[i].to, busSeats[i].date);
            printf("Enter new passenger name: ");
            scanf("%s", busSeats[i].passengerName);
            printf("Enter new 'from' place: ");
            scanf("%s", busSeats[i].from);
            printf("Enter new 'to' place: ");
            scanf("%s", busSeats[i].to);
            printf("Booking updated successfully\n");
            updated++;
        }
    }

    if (updated == 0) {
        printf("No bookings found for the specified date.\n");
    } else {
        saveSeatsToFile();
    }
}

void displayBookedSeats() {
    char date[20];
    printf("Enter date (dd/mm/yyyy) to display bookings: ");
    scanf("%s", date);

    int bookedSeats = 0;
    printf("Booked seats for %s:\n", date);
    for (int i = 0; i < MAX_SEATS; i++) {
        if (busSeats[i].isBooked && strcmp(busSeats[i].date, date) == 0) {
            printf("Seat %d - Passenger: %s, From: %s, To: %s\n", busSeats[i].seatNumber, busSeats[i].passengerName, busSeats[i].from, busSeats[i].to);
            bookedSeats++;
        }
    }

    int availableSeats = MAX_SEATS - bookedSeats;
    printf("Available seats for %s: %d\n", date, availableSeats);
}

int main() {
    initializeSeats();
    loadSeatsFromFile();
    printf("WELCOME TO NIROSHA EXPRESS [VAVUNIYA - COLOMBO (NB ####)]\n ");
    printf("From Vavuniya 4:00 A.M To Colombo 09:30 A.M");
    printf("\n\n\n");
    printf("Stopping places: Vavuniya, Medawachchiya, Rabewa\n");
    printf("Mihintale, Galkulama, Thirappane, Maradankadawala, Kekirawa\n");
    printf("Dambulla, Galewela, Malsiripura, Ibbagamuwa, Kurunegala\n");
    printf("Pothuhera, Polgahawela, Alawwa, Warakapola, Nittambuwa\n");
    printf("Yakkala, Balummahara, Kadawatha, Kiribathgoda, Peliyagoda\n");
    printf("Maligawatta, Colombo Fort\n");

    int choice;
    do {
        printf("\nBus Seat Booking System\n");
        printf("1. Book a seat\n");
        printf("2. Delete booking\n");
        printf("3. Update booking\n");
        printf("4. Display booked seats\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookSeat();
                break;
            case 2:
                deleteBooking();
                break;
            case 3:
                updateBooking();
                break;
            case 4:
                displayBookedSeats();
                break;
            case 5:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
