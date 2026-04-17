#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

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

Barang dataBarang[100];
int jumlahBarang = 0;

void tekanEnter(){
    cout << "\nTekan enter untuk lanjut. . .";
    cin.ignore();
    cin.get();
}

//SORTING

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

//SEARCHING

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

//LOGIN

bool login(User *admin){
    string inputNama, inputNim;
    int sisa = 3;

    while(sisa > 0){
        system("cls");
        cout << "=== LOGIN ===\n";

        cout << "Username (Nama): ";
        cin >> inputNama;

        cout << "Password (NIM): ";
        cin >> inputNim;

        if(inputNama == admin->nama && inputNim == admin->nim){
            return true;
        } else {
            sisa--;
            cout << "Login gagal! Sisa kesempatan: " << sisa << endl;
            tekanEnter();
        }
    }
    return false;
}

//TAMPIL BARANG
void tampilBarangRekursif(Barang dataBarang[], int *jumlahBarang, int index){
    if(index == *jumlahBarang){
        return;
    }

    Barang *ptr = &dataBarang[index];

    cout << left << setw(10) << ptr->kode
         << setw(20) << ptr->nama
         << setw(10) << ptr->detail.ukuran
         << setw(10) << ptr->stok
         << setw(15) << ptr->harga << endl;

    tampilBarangRekursif(dataBarang, jumlahBarang, index + 1);
}

//CRUD

void tambahBarang(Barang dataBarang[], int *jumlahBarang){
    system("cls");
    cout << "=== TAMBAH DATA BARANG ===\n";

    cout << "Kode Barang   : ";
    cin >> dataBarang[*jumlahBarang].kode;

    cin.ignore();
    cout << "Nama Barang   : ";
    getline(cin, dataBarang[*jumlahBarang].nama);

    cout << "Ukuran        : ";
    getline(cin, dataBarang[*jumlahBarang].detail.ukuran);

    cout << "Stok          : ";
    cin >> dataBarang[*jumlahBarang].stok;

    cout << "Harga         : ";
    cin >> dataBarang[*jumlahBarang].harga;

    (*jumlahBarang)++;

    cout << "\nData berhasil ditambahkan!\n";
    tekanEnter();
}

void lihatBarang(Barang dataBarang[], int *jumlahBarang){
    system("cls");

    if(*jumlahBarang == 0){
        cout << "Tidak ada data.\n";
        tekanEnter();
        return;
    }

    int pilihSort;

    cout << "=== LIHAT DATA BARANG ===\n";
    cout << "1. Nama (Descending - Bubble Sort)\n";
    cout << "2. Harga (Ascending - Selection Sort)\n";
    cout << "3. Stok (Ascending - Insertion Sort)\n";

    do {
        cout << "Pilih (1-3): ";
        cin >> pilihSort;
    } while(pilihSort < 1 || pilihSort > 3);

    if(pilihSort == 1) bubbleSortNamaDesc(dataBarang, jumlahBarang);
    else if(pilihSort == 2) selectionSortHargaAsc(dataBarang, jumlahBarang);
    else insertionSortStokAsc(dataBarang, jumlahBarang);

    cout << fixed << setprecision(0);

    cout << "====================================================================\n";
    cout << left << setw(10) << "Kode"
         << setw(20) << "Nama"
         << setw(10) << "Ukuran"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;
    cout << "====================================================================\n";

    tampilBarangRekursif(dataBarang, jumlahBarang, 0);

    cout << "====================================================================\n";
    tekanEnter();
}

void updateBarang(Barang dataBarang[], int *jumlahBarang){
    system("cls");

    if(*jumlahBarang == 0){
        cout << "Data kosong!\n";
        tekanEnter();
        return;
    }

    cout << "=== UPDATE DATA BARANG ===\n";
    tampilBarangRekursif(dataBarang, jumlahBarang, 0);

    string kode;
    cout << "\nMasukkan kode barang: ";
    cin >> kode;

    int index = cariBarang(dataBarang, jumlahBarang, kode); // FIX

    if(index != -1){
        Barang *ptr = &dataBarang[index];

        cin.ignore();

        string namaBaru, ukuranBaru, stokBaru, hargaBaru;

        cout << "\n(Kosongkan jika tidak ingin diubah)\n";

        cout << "Nama baru   : ";
        getline(cin, namaBaru);

        cout << "Ukuran baru : ";
        getline(cin, ukuranBaru);

        cout << "Stok baru   : ";
        getline(cin, stokBaru);

        cout << "Harga baru  : ";
        getline(cin, hargaBaru);

        if(namaBaru != "") ptr->nama = namaBaru;
        if(ukuranBaru != "") ptr->detail.ukuran = ukuranBaru;
        if(stokBaru != "") ptr->stok = stoi(stokBaru);
        if(hargaBaru != "") ptr->harga = stod(hargaBaru);

        cout << "\nData berhasil diupdate!\n";
    } else {
        cout << "Data tidak ditemukan.\n";
    }

    tekanEnter();
}

void hapusBarang(Barang dataBarang[], int *jumlahBarang){
    system("cls");

    if(*jumlahBarang == 0){
        cout << "Data kosong!\n";
        tekanEnter();
        return;
    }

    cout << "=== HAPUS DATA BARANG ===\n";
    tampilBarangRekursif(dataBarang, jumlahBarang, 0);

    string kode;
    cout << "\nMasukkan kode barang: ";
    cin >> kode;

    int index = cariBarang(dataBarang, jumlahBarang, kode); // FIX

    if(index != -1){
        for(int i = index; i < (*jumlahBarang) - 1; i++){
            dataBarang[i] = dataBarang[i+1];
        }
        (*jumlahBarang)--;

        cout << "\nData berhasil dihapus!\n";
    } else {
        cout << "Data tidak ditemukan.\n";
    }

    tekanEnter();
}

//CARI DATA BARANG

void cariData(Barang dataBarang[], int *jumlahBarang){
    system("cls");

    if(*jumlahBarang == 0){
        cout << "Data kosong!\n";
        tekanEnter();
        return;
    }

    int pilih;
    cout << "=== CARI DATA BARANG ===\n";
    cout << "1. Cari berdasarkan Kode (Binary Search)\n";
    cout << "2. Cari berdasarkan Nama (Linear Search)\n";
    cout << "Pilih: ";
    cin >> pilih;

    if(pilih == 1){
        string kode;
        cout << "Masukkan kode: ";
        cin >> kode;

        sortKodeAsc(dataBarang, jumlahBarang);
        int index = binarySearchKode(dataBarang, jumlahBarang, kode);

        if(index != -1){
            cout << "\nData ditemukan:\n";
            cout << "Kode   : " << dataBarang[index].kode << endl;
            cout << "Nama   : " << dataBarang[index].nama << endl;
            cout << "Ukuran : " << dataBarang[index].detail.ukuran << endl;
            cout << "Stok   : " << dataBarang[index].stok << endl;
            cout << "Harga  : " << dataBarang[index].harga << endl;
        } else {
            cout << "Data tidak ditemukan.\n";
        }
    }
    else if(pilih == 2){
        cin.ignore();
        string nama;
        cout << "Masukkan nama: ";
        getline(cin, nama);

        int index = linearSearchNama(dataBarang, jumlahBarang, nama);

        if(index != -1){
            cout << "\nData ditemukan:\n";
            cout << "Kode   : " << dataBarang[index].kode << endl;
            cout << "Nama   : " << dataBarang[index].nama << endl;
            cout << "Ukuran : " << dataBarang[index].detail.ukuran << endl;
            cout << "Stok   : " << dataBarang[index].stok << endl;
            cout << "Harga  : " << dataBarang[index].harga << endl;
        } else {
            cout << "Data tidak ditemukan.\n";
        }
    }

    tekanEnter();
}

//MENU UTAMA

int main(){
    User admin = {"ghina", "054"};

    if(!login(&admin)){
        cout << "Anda gagal login 3 kali.\n";
        return 0;
    }

    int pilihan;

    do{
        system("cls");

        cout << "=== MENU UTAMA ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Cari Barang\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch(pilihan){
            case 1: tambahBarang(dataBarang, &jumlahBarang); break;
            case 2: lihatBarang(dataBarang, &jumlahBarang); break;
            case 3: updateBarang(dataBarang, &jumlahBarang); break;
            case 4: hapusBarang(dataBarang, &jumlahBarang); break;
            case 5: cariData(dataBarang, &jumlahBarang); break;
            case 6: cout << "Terima kasih!\n"; break;
            default:
                cout << "Pilihan tidak valid!\n";
                tekanEnter();
        }

    } while(pilihan != 6);

    return 0;
}