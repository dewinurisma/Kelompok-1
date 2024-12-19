#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CARRIAGES 3
#define SEATS_PER_CARRIAGE 10

void displayMainMenu();
void displayCarriageOptions();
void selectSeat(int carriageNumber);
void saveBooking(const char *name, int carriageNumber, int seatNumber);
void viewAvailability();

int seats[NUM_CARRIAGES][SEATS_PER_CARRIAGE] = {0};

int main() {
    int choice;

    while (1) {
        displayMainMenu();
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCarriageOptions();
                break;
            case 2:
                viewAvailability();
                break;
            case 3:
                printf("Terima kasih telah menggunakan sistem pemesanan kereta api kelompok 1!\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }

    return 0;
}

void displayMainMenu() {
    printf("\n=== Sistem Pemesanan Kursi Kereta Api ===\n");
    printf("1. Pesan Tiket\n");
    printf("2. Lihat Ketersediaan Kursi\n");
    printf("3. Tutup sistem\n");
}

void displayCarriageOptions() {
    int carriageNumber;
    int i;

    printf("\n=== Pilih Gerbong ===\n");
    for (i = 0; i < NUM_CARRIAGES; i++) {
        printf("%d. Gerbong %d\n", i + 1, i + 1);
    }

    printf("Pilih nomor gerbong: ");
    scanf("%d", &carriageNumber);

    if (carriageNumber < 1 || carriageNumber > NUM_CARRIAGES) {
        printf("Nomor gerbong tidak valid. Silakan coba lagi.\n");
        return;
    }

    selectSeat(carriageNumber);
}

void selectSeat(int carriageNumber) {
    int seatNumber;
    char name[50];
    int i;

    printf("\n=== Pilih Kursi di Gerbong %d ===\n", carriageNumber);
    printf("+-------------------------------+\n");
    printf("| Kursi: ");

    for (i = 0; i < SEATS_PER_CARRIAGE; i++) {
        if (seats[carriageNumber - 1][i] == 0) {
            printf("%2d ", i + 1);
        } else {
            printf("-- ");
        }
    }
    printf("|\n+-------------------------------+\n");

    printf("Masukkan nomor kursi yang ingin Anda pilih: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > SEATS_PER_CARRIAGE || seats[carriageNumber - 1][seatNumber - 1] == 1) {
        printf("Nomor kursi tidak valid atau sudah dipesan. Silakan coba lagi.\n");
        return;
    }

    printf("Masukkan nama Anda: ");
    scanf("%s", name);

    seats[carriageNumber - 1][seatNumber - 1] = 1;
    saveBooking(name, carriageNumber, seatNumber);

    printf("Pemesanan berhasil! %s telah memesan kursi nomor %d di gerbong %d.\n", name, seatNumber, carriageNumber);
}

void saveBooking(const char *name, int carriageNumber, int seatNumber) {
    FILE *file;
    file = fopen("reservasi.txt", "a");

    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data.\n");
        return;
    }

    fprintf(file, "Nama: %s, Gerbong: %d, Kursi: %d\n", name, carriageNumber, seatNumber);
    fclose(file);
}

void viewAvailability() {
    int i, j;
    printf("\n=== Ketersediaan Kursi ===\n");
    for (i = 0; i < NUM_CARRIAGES; i++) {
        printf("\nGerbong %d:\n", i + 1);
        printf("+-------------------------------+\n");
        printf("| Kursi: ");

        for (j = 0; j < SEATS_PER_CARRIAGE; j++) {
            if (seats[i][j] == 0) {
                printf("%2d ", j + 1);
            } else {
                printf("-- ");
            }
        }
        printf("|\n+-------------------------------+\n");
    }
}

