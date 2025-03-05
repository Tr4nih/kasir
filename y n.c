#include <stdio.h> //memasukkan library dasar c (bagus)
#include <string.h> //memasukkan library manipulasi string (bagus)
#include <stdlib.h>  //memasukkan library untuk konversi tipe data (bagus)

#define MAX_ITEMS 100 //mendefinisikan max item yang bisa ditambahkan (bagus)

typedef struct { //membuat struct data
    char nama[50]; //variable nama dengan char dan leght 50 (bagus)
    float harga; //variable harga dengan tipe data float (bagus)
} Barang; //menentukan nama struct (bagus)

typedef struct { //membuat struct data (bagus)
    char nama[50]; //variable nama dengan char dan leght 50 (bagus)
    float harga; //variable harga dengan tipe data float (bagus)
    int jumlah; //variable jumlah dengan tipe data integer (bagus)
    float diskon; //variable diskon dengan tipe data slot (bagus)
    float subtotal; //variable subtotal dengan tipe data float (bagus)
} Item; //menentukan nanam struct (bagus)

void tampilkanBarangTersedia(Barang barangTersedia[], int totalBarang) { //fungsi tampilkanBarangTersedia (bagus)
    printf("\n=== DAFTAR BARANG TERSEDIA ===\n"); //mencetak output (bagus)
    for (int i = 0; i < totalBarang; i++) { //melakukan looping (bagus)
        printf("%d. %s - Rp%.2f\n", i + 1, barangTersedia[i].nama, barangTersedia[i].harga); //mencetak output dengab menampilkan barang (bagus)
    } //penutup for (bagus)
}

void urutkanBarang(Item items[], int totalItems) { //fungsi urutkanBarang (bagus)
    for (int i = 0; i < totalItems - 1; i++) { //melakukan perulangan (bagus)
        for (int j = i + 1; j < totalItems; j++) { //melakukan perungan (bagus)
            if (items[j].subtotal > items[i].subtotal) { // Urutkan berdasarkan total harga tertinggi (bagus)
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void tampilkanStruk(char kasir[], Item items[], int totalItems, float totalHarga, float totalDiskon) { //fungsi untuk menampilkan struk (bagus)
    printf("\n===================================================================\n"); //mencetak output (bagus)
    printf("| %-3s | %-6s | %-15s | %-10s | %-10s | %-10s |\n", "No.", "Jumlah", "Nama Barang", "Harga", "Total", "Diskon"); //mencetak output (bagus)
    printf("===================================================================\n"); //mencetak output (bagus)

    for (int i = 0; i < totalItems; i++) { //melakukan perulangan (bagus)
        printf("| %-3d | %-6d | %-15s | Rp.%-8.2f | Rp.%-8.2f | Rp.%-8.2f |\n",
               i + 1, items[i].jumlah, items[i].nama, items[i].harga,
               items[i].subtotal, items[i].diskon);
    }
    printf("===================================================================\n"); //mencetak output hasil (bagus)
    printf("Total Harga  = Rp. %.2f,-\n", totalHarga);
    printf("Total Diskon = Rp. %.2f,-\n", totalDiskon);
    printf("Total Bayar  = Rp. %.2f,-\n", totalHarga - totalDiskon);
}

void cetakStrukKeFile(char kasir[], Item items[], int totalItems, float totalHarga, float totalDiskon, float uangDibayar, float kembalian) { //fungsi untuk memasukkan data ke dalam struk (bagus)
    FILE *file = fopen("struk_pembayaran.txt", "w");
    if (file == NULL) { //kondisi jika gagal memasukkan data ke dalam struk (bagus)
        printf("Gagal membuka file untuk menulis struk.\n");
        return;
    }

    fprintf(file, "\n===================================================================\n"); //mencetak output dan dimasukkan dalam file sturk (bagus)
    fprintf(file, "| %-3s | %-6s | %-15s | %-10s | %-10s | %-10s |\n", "No.", "Jumlah", "Nama Barang", "Harga", "Total", "Diskon");
    fprintf(file, "===================================================================\n");

    for (int i = 0; i < totalItems; i++) { //melakukan perulangan pada struk (bagus)
        fprintf(file, "| %-3d | %-6d | %-15s | Rp.%-8.2f | Rp.%-8.2f | Rp.%-8.2f |\n", //mencetak output dengan mengatur tata letaknya (bagus)
                i + 1, items[i].jumlah, items[i].nama, items[i].harga, //memanggil perulangan di file struk (bagus)
                items[i].subtotal, items[i].diskon);
    }
    fprintf(file, "===================================================================\n"); //mencetak output dan memasukkannya ke dalam file struk (bagus)
    fprintf(file, "Total Harga  = Rp. %.2f,-\n", totalHarga);
    fprintf(file, "Total Diskon = Rp. %.2f,-\n", totalDiskon);
    fprintf(file, "Total Bayar  = Rp. %.2f,-\n", totalHarga - totalDiskon);
    fprintf(file, "Uang Dibayar = Rp. %.2f,-\n", uangDibayar);
    fprintf(file, "Kembalian    = Rp. %.2f,-\n", kembalian);

    fclose(file); //memberhentikan proses (bagus)
    printf("Struk telah dicetak ke dalam file struk_pembayaran.txt\n");
}

float hitungDiskon(int jumlah) { //menghitung diskon berdasarkan jumlah barang yang dibeli (bagus)
    if (jumlah >= 10) { //jika jumlah lebih atau sama dengan 10 diskon yang didapat sebesar 0.15 (bagus)
        return 0.15;
    } else if (jumlah >= 5) {//jika jumlah lebih atau sama dengan 5 diskon yang didapat sebesar 0.10 (bagus)
        return 0.10;
    } else if (jumlah >= 3) { //jika jumlah lebih atau sama dengan 3 diskon yang didapat sebesar 0.05 (bagus)
        return 0.05;
    }
    return 0;
}

void prosesPilihanBarang(char input[], Barang barangTersedia[], Item items[], int *totalItems, float *subtotal, float *totalDiskon) { //proses pilih barang (bagus)
    char *token = strtok(input, ", "); //memisahkan input berdasarkan koma (bagus)
    while (token != NULL) { //melakukan perulangan selagi masih ada input (bagus)
        int pilihanBarang = atoi(token); //mengubah string menjadi angka (bagus)

        if (pilihanBarang < 1 || pilihanBarang > 5) { //jika rentan pilihan tidak sesuai maka tidak valid (bagus)
            printf("Pilihan %d tidak valid!\n", pilihanBarang);
        } else {
            int indexBarang = pilihanBarang - 1; //kondisi jika pilihan sesuai (bagus)
            items[*totalItems].harga = barangTersedia[indexBarang].harga; //memproses barang yang dipilih dengan menyimpan ke dalam item (bagus)
            strcpy(items[*totalItems].nama, barangTersedia[indexBarang].nama);

            printf("Masukkan jumlah barang %s: ", barangTersedia[indexBarang].nama); //memasukkan jumlah barang yang dibeli (bagus)
            scanf("%d", &items[*totalItems].jumlah); //menyimpan input pengguna (bagus)

            items[*totalItems].diskon = hitungDiskon(items[*totalItems].jumlah) * items[*totalItems].harga * items[*totalItems].jumlah; //menghitung diskon (bagus)
            items[*totalItems].subtotal = (items[*totalItems].harga * items[*totalItems].jumlah) - items[*totalItems].diskon;

            *subtotal += items[*totalItems].subtotal; //menambahkan total harga dan diskon secara keseluruhan (bagus)
            *totalDiskon += items[*totalItems].diskon;
            (*totalItems)++;
        }

        token = strtok(NULL, ", ");
    }
}

int main() { //menjalankan program utama (bagus)
    Barang barangTersedia[] = { //mengisi array barangTersedia (bagus)
        {"Beras", 12000},
        {"Gula", 15000},
        {"Minyak Goreng", 20000},
        {"Sabun", 5000},
        {"Susu", 25000}
    };
    int totalBarangTersedia = sizeof(barangTersedia) / sizeof(barangTersedia[0]); //mengatur elemen array statis (bagus)

    Item items[MAX_ITEMS]; //array untuk menyimpan daftar barang yang dibeli (bagus)
    int totalItems = 0;
    char inputBarang[100], tambahLagi;
    float subtotal = 0, totalDiskon = 0;
    float uangDibayar = 0, kembalian = 0;
    char kasir[50];

    printf("=== SISTEM KASIR ===\n"); //mencetak output untuk memasukkan nama pengguna (bagus)
    printf("Masukkan nama kasir: ");
    fgets(kasir, sizeof(kasir), stdin); //menyimpan input dan memasukkan ke file struk (bagus)
    kasir[strcspn(kasir, "\n")] = 0;

    tampilkanBarangTersedia(barangTersedia, totalBarangTersedia); //menampilkan daftar barang (bagus)

    do { //melakukan looping (bagus)
        printf("Pilih barang (misalnya: 1, 2, 3): "); //penguna dapat memilih lebih dari satu barang (bagus)
        fgets(inputBarang, sizeof(inputBarang), stdin);
        inputBarang[strcspn(inputBarang, "\n")] = 0;
        prosesPilihanBarang(inputBarang, barangTersedia, items, &totalItems, &subtotal, &totalDiskon);
        printf("Tambah barang lagi? (y/n): "); //memunculkan pilihan apakah tambah barang lagi atau tidak (bagus)
        scanf(" %c", &tambahLagi);
        getchar();
    } while (tambahLagi == 'y' || tambahLagi == 'Y');

    urutkanBarang(items, totalItems); //mengurutkan barang berdasarkan nama atau harga (bagus)
    tampilkanStruk(kasir, items, totalItems, subtotal, totalDiskon); //mencetak struk sementara (bagus)

    do { //melakukan looping untuk proses pembayaran (bagus)
        printf("Masukkan uang bayar: ");
        scanf("%f", &uangDibayar);
        if (uangDibayar < (subtotal - totalDiskon)) { //jika uang tidak cukup maka sistem akan mengulang dari awal (bagus)
            printf("Uang yang dibayarkan kurang. Silakan masukkan jumlah yang cukup.\n");
        }
    } while (uangDibayar < (subtotal - totalDiskon));

    kembalian = uangDibayar - (subtotal - totalDiskon); //menghitung kembalian (bagus)
    printf("Kembalian: Rp. %.2f,-\n", kembalian); //mencetak kembalian (bagus)

    printf("\n=== STRUK PEMBAYARAN ===\n");
    tampilkanStruk(kasir, items, totalItems, subtotal, totalDiskon); //menampilkan struk pada sistem (bagus)
    cetakStrukKeFile(kasir, items, totalItems, subtotal, totalDiskon, uangDibayar, kembalian); //mencetak struk ke dalam file (bagus)

    printf("\n=== TERIMA KASIH TELAH BERBELANJA! ===\n");

    return 0; //menutup sistem (bagus)
}
