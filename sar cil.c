#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//deklarasi variabel array
struct Produk{
    char produk[50];
    float harga;
};

//tampilan menu
void displayMenu(struct Produk produkDanHarga[], int jumlahProduk){
    printf("            Selamat Datang di Toko SKENSA            \n");
    printf("      Silahkan Pilih Barang yang Anda Inginkan :     \n");
    printf("=====================================================\n");
    printf("| No. |        Nama Barang        |      Harga      |\n");
    printf("-----------------------------------------------------\n");
    //print array produk dan harga
        for(int i = 0; i < jumlahProduk; i++){
            printf("|  %-2d |    %-19s    | Rp.%-12.0f |\n", i + 1, produkDanHarga[i].produk, produkDanHarga[i].harga);
        }
     printf("=====================================================\n");
     printf("\n  99. Struk Pembayaran");
     printf("\n  55. Reset Pilihan");
     printf("\n  00. Keluar\n");
     printf("\n=====================================================");

}

//fungsi untuk mengurutkan data pesanan dari jumlah yang terbanyak
void sortPesanan(struct Produk produkDanHarga[], int jumlahProduk, int jumlahBeli[]){
    for(int i = 0; i < jumlahProduk - 1; i++){
        for(int j = 0; j < jumlahProduk - i - 1; j++){
            if(jumlahBeli[j] < jumlahBeli[j + 1]){
                int tempQty = jumlahBeli[j];
                    jumlahBeli[j] = jumlahBeli[j + 1];
                    jumlahBeli[j + 1] = tempQty;

                struct Produk temp = produkDanHarga[j];
                       produkDanHarga[j] = produkDanHarga[j + 1];
                       produkDanHarga[j + 1] = temp;
            }
        }
    }
}

//membuat id struk
int generateStrukID(){
    time_t current_time;
    time (&current_time);

    int randNum = rand()%10000;
    int strukID = randNum + (int)current_time;

    return strukID;
}


int main()
{
    //array untuk produk dan harga    // ARRAY UNTUK MENYIMPAN DATA BARANG
    struct Produk produkDanHarga[]={
        {"Buku Tulis", 5000},
        {"Pensil", 2000},
        {"Penghapus", 1000},
        {"Penggaris", 1000},
        {"Bujur Sangkar", 500},
    };

    int jumlahProduk = sizeof(produkDanHarga)/sizeof(produkDanHarga[0]),
        jumlah,
        jumlahBeli[5] = {0},
        pilihan,
        strukID = generateStrukID(),
        no_barang = 0;

    float hargaAkhir[5] = {0},
          totalHarga,
          diskon[5] = {0},
          totalHargaAkhir = 0,
          totalDiskon = 0,
          totalBayar,
          uangBayar,
          kembalian;

    //mengambil waktu
    time_t current_time;
    struct tm*local_time;
    current_time = time(NULL);
    local_time = localtime(&current_time);
    char time_str[50];

    strftime(time_str, sizeof(time_str), " %a %b %d %H:%M:%S %Y", local_time);

    //nama file
    char filename[50];
    sprintf(filename, "struk %d.txt", strukID);

    //simpan file
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("\nGagal membuat file\n");
        exit(1);
    }

    //menampilkan menu
    displayMenu(produkDanHarga, jumlahProduk);

    //menampilkan field pilihan
    while (1){
        printf("\n\nMasukkan pilihan yang anda inginkan: ");
        scanf("%d", &pilihan);

        //kondisi untuk memilih barang yang akan dibeli
        if(pilihan >= 1 && pilihan <= jumlahProduk){
            //print untuk input user
            printf("\n [%d] Pembelian barang %s", pilihan, produkDanHarga[pilihan-1].produk);
            printf("\n     Jumlah: ");
            scanf("%d", &jumlah);

            printf("\n=====================================================");

            //menyimpan ke array
            jumlahBeli[pilihan-1] += jumlah;                                    //memasukkan jumlah pembelian masing-masing ke array
            hargaAkhir[pilihan-1] += produkDanHarga[pilihan-1].harga * jumlah;  //array untuk menghitung harga akhir saat pembayaran

            continue;

            //opsi struk
        } else if (pilihan == 99){
            //bubble sort
            sortPesanan(produkDanHarga, jumlahProduk, jumlahBeli);

            printf("\n                             Rekap Pesanan Barang                           \n");
            printf("==============================================================================\n");
            printf("| No. |  Jumlah  |    Nama Barang    |    Harga    | Total Harga |   Diskon  |\n");
            printf("------------------------------------------------------------------------------\n");
            //perulangan untuk rekap pesanan
                for(int i = 0; i < jumlahProduk; i++){
                    //menghitung total harga
                        totalHarga = produkDanHarga[i].harga * jumlahBeli[i];

                    if(jumlahBeli[i] > 0){

                        //menghitung diskon //KONDISI UNTUK DISKON
                        if(jumlahBeli[i] < 3){ // MEMBELI KURANG DARI 3 ITEM TIDAK DAPAT DISKON
                            diskon[i] = 0;
                        } else if (jumlahBeli[i] >= 3 && jumlahBeli[i] < 5){ // MEMBELI LEBIH DARI 3 DAN KURANG DARI 5 ITEM 10% DISKON
                            diskon[i] = totalHarga * 0.10;
                        } else if (jumlahBeli[i] >= 5){ // MEMBELI LEBIH DARI 5 ITEM MENDAPATKAN 15% DISKON
                            diskon[i] = totalHarga * 0.15;
                        }
                        //print barang yang dibeli
                        printf("|  %-2d |     %-2d   |   %-13s   |  Rp.%-7.0f |  Rp.%-6.0f  | Rp.%-7.0f|\n", i + 1, jumlahBeli[i],
                               produkDanHarga[i].produk, produkDanHarga[i].harga, totalHarga, diskon[i], no_barang++);
                    }
                    totalHargaAkhir += hargaAkhir[i];
                    totalDiskon += diskon[i];
                    totalBayar = totalHargaAkhir - totalDiskon;
                }
                printf("==============================================================================\n");
                printf("\n     Total Harga  :  Rp.%.0f", totalHargaAkhir);
                printf("\n     Total Diskon :  Rp.%.0f", totalDiskon);
                printf("\n     Total Bayar  :  Rp.%.0f", totalBayar);
                printf("\n\n==============================================================================\n");

                while(1){
                    //uang bayar
                    printf("Masukkan uang bayar: Rp.");
                    scanf("%f", &uangBayar);

                    //menghitung kembalian
                    if(uangBayar >= totalBayar){
                        kembalian = uangBayar - totalBayar;
                        printf("\n Kembalian : Rp.%.0f\n", kembalian);
                        break;
                    } else if (uangBayar < totalBayar){
                        printf("\n Maaf, uang anda kurang.\n");
                        continue;
                    }

                }

                //print ke txt
                fprintf(fp, "======================================================================\n");
                fprintf(fp, "|                             TOKO SKENSA                            |\n");
                fprintf(fp, "|                 Jl. HOS Cokroainoto No. 84 Denpasar               |\n");
                fprintf(fp, "|                          Telp. 0816285791                          |\n");
                fprintf(fp, "|                                Bali                                |\n");
                fprintf(fp, "|   ID Struk: %-55d|\n", strukID);
                fprintf(fp, "======================================================================\n");
                fprintf(fp, "|      Nama Barang      |    Harga    |   Total Harga   |   Diskon   |\n");
                fprintf(fp, "----------------------------------------------------------------------\n");
                for(int i = 0; i < jumlahProduk; i++){
                    if(jumlahBeli[i] > 0){
                            totalHarga = produkDanHarga[i].harga * jumlahBeli[i];
                            fprintf(fp, "| x%d %-18s | Rp.%-8.0f | Rp.%-12.0f | Rp.%-8.0f|\n", jumlahBeli[i],
                                    produkDanHarga[i].produk, produkDanHarga[i].harga, totalHarga, diskon[i]);
                    }
                }
                fprintf(fp, "======================================================================");
                fprintf(fp, "\n|     Total Harga  :  Rp.%-44.0f|", totalHargaAkhir);
                fprintf(fp, "\n|     Total Diskon :  Rp.%-44.0f|", totalDiskon);
                fprintf(fp, "\n|     Total Bayar  :  Rp.%-44.0f|", totalBayar);
                fprintf(fp, "\n|         Uang Bayar  :  Rp.%-41.0f|", uangBayar);
                fprintf(fp, "\n|         Kembalian   :  Rp.%-41.0f|", kembalian);
                fprintf(fp, "\n| Waktu Dan Hari: %-51s|\n", time_str);
                fprintf(fp, "======================================================================\n");
                fclose(fp);

                printf("\n Terima Kasih telah berbelanja!");
                printf("\nStruk tersimpan di %s\n", filename);

            break;

        //opsi reset pilihan
        } else if (pilihan == 55){
            for(int i = 0; i < jumlahProduk; i++){
                pilihan = 0;
                jumlahBeli[i] = 0;
                hargaAkhir[i] = 0;
            }
            system("cls");
            printf("\t     [!] Pilihan telah direset [!]\n\n");

            displayMenu(produkDanHarga, jumlahProduk);
            continue;

         //opsi keluar
        } else if (pilihan == 00){
            printf("exiting...");
            exit(0);
        } else {
            printf("\nPilihan tidak valid!");
            continue;
        }
    }
    return 0;
}
