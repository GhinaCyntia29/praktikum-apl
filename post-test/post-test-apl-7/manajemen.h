#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// DEKLARASI STRUCT
// ==========================================
struct User {
    string nama;
    string nim;
};

struct Barang {
    string kode;
    string nama;
    int stok;
    double harga;

    struct Detail {
        string ukuran;
    } detail;
};

// ==========================================
// FUNGSI SORTING
// ==========================================
void bubbleSortNamaDesc(Barang data[], int *n){
    for(int i = 0; i < (*n) - 1; i++){
        for(int j = 0; j < (*n) - i - 1; j++){
            if(data[j].nama < data[j+1].nama){
                swap(data[j], data[j+1]);
            }
        }
    }
}

void selectionSortHargaAsc(Barang data[], int *n){
    for(int i = 0; i < (*n) - 1; i++){
        int min = i;
        for(int j = i+1; j < (*n); j++){
            if(data[j].harga < data[min].harga){
                min = j;
            }
        }
        swap(data[i], data[min]);
    }
}

void insertionSortStokAsc(Barang data[], int *n){
    for(int i = 1; i < (*n); i++){
        Barang key = data[i];
        int j = i - 1;

        while(j >= 0 && data[j].stok > key.stok){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

void sortKodeAsc(Barang data[], int *n){
    for(int i = 0; i < (*n) - 1; i++){
        for(int j = 0; j < (*n) - i - 1; j++){
            if(data[j].kode > data[j+1].kode){
                swap(data[j], data[j+1]);
            }
        }
    }
}

// ==========================================
// FUNGSI SEARCHING
// ==========================================
int cariBarang(Barang dataBarang[], int *jumlahBarang, string kode){
    for(int i = 0; i < *jumlahBarang; i++){
        if(dataBarang[i].kode == kode){
            return i;
        }
    }
    return -1;
}

int linearSearchNama(Barang data[], int *n, string cari){
    for(int i = 0; i < *n; i++){
        if(data[i].nama == cari){
            return i;
        }
    }
    return -1;
}

int binarySearchKode(Barang data[], int *n, string cari){
    int left = 0, right = *n - 1;

    while(left <= right){
        int mid = (left + right) / 2;

        if(data[mid].kode == cari){
            return mid;
        }
        else if(data[mid].kode < cari){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}

#endif