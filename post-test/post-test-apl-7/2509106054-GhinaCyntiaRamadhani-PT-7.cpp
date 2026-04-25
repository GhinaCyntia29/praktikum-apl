#include <iostream>
#include <iomanip>
#include <string>
#include <limits>    
#include <stdexcept> 

//memanggil user-defined library
#include "manajemen.h"

using namespace std;

Barang dataBarang[100];
int jumlahBarang = 0;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tekanEnter(){
    cout << "\nTekan Enter untuk lanjut. . .";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

//LOGIN
bool login(User *admin){
    string inputNama, inputNim;
    int sisa = 3;

    while(sisa > 0){
        clearScreen();
        cout << "======================================\n";
        cout << "            LOGIN SISTEM              \n";
        cout << "======================================\n";

        cout << "Username (Nama) : ";
        cin >> inputNama;

        cout << "Password (NIM)  : ";
        cin >> inputNim;

        if(inputNama == admin->nama && inputNim == admin->nim){
            cout << "\nLogin berhasil!";
            tekanEnter();
            return true;
        } else {
            sisa--;
            cout << "\n[!] Login gagal! Sisa kesempatan: " << sisa << endl;
            if(sisa > 0) tekanEnter();
        }
    }
    return false;
}

//TAMPIL BARANG
void tampilBarangRekursif(Barang dataBarang[], int *jumlahBarang, int index){
    if(index == *jumlahBarang) return;

    Barang *ptr = &dataBarang[index];

    cout << left << setw(10) << ptr->kode
         << setw(20) << ptr->nama
         << setw(10) << ptr->detail.ukuran
         << setw(10) << ptr->stok
         << setw(15) << ptr->harga << endl;

    tampilBarangRekursif(dataBarang, jumlahBarang, index + 1);
}

//CRUD & FITUR UTAMA (ERROR HANDLING)
void tambahBarang(Barang dataBarang[], int *jumlahBarang){
    clearScreen();
    cout << "======================================\n";
    cout << "          TAMBAH DATA BARANG          \n";
    cout << "======================================\n";

    try {
        cout << "Kode Barang   : ";
        cin >> dataBarang[*jumlahBarang].kode;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama Barang   : ";
        getline(cin, dataBarang[*jumlahBarang].nama);

        cout << "Ukuran        : ";
        getline(cin, dataBarang[*jumlahBarang].detail.ukuran);

        cout << "Stok          : ";
        if (!(cin >> dataBarang[*jumlahBarang].stok)) {
            throw invalid_argument("Input stok harus berupa angka!");
        }
        if (dataBarang[*jumlahBarang].stok < 0) {
            throw runtime_error("Stok tidak boleh bernilai negatif!");
        }

        cout << "Harga         : ";
        if (!(cin >> dataBarang[*jumlahBarang].harga)) {
            throw invalid_argument("Input harga harus berupa angka!");
        }
        if (dataBarang[*jumlahBarang].harga < 0) {
            throw runtime_error("Harga tidak boleh bernilai negatif!");
        }

        (*jumlahBarang)++;
        cout << "\nData berhasil ditambahkan!\n";

    } catch (const exception& e) {
        //menangkap error dan membersihkan cin error state
        cout << "\n[ERROR] " << e.what() << endl;
        cout << "[!] Gagal menambahkan barang.\n";
        cin.clear();
    }
    
    tekanEnter();
}

void lihatBarang(Barang dataBarang[], int *jumlahBarang){
    clearScreen();
    if(*jumlahBarang == 0){
        cout << "[!] Tidak ada data barang yang tersimpan.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tekanEnter();
        return;
    }

    int pilihSort;

    cout << "======================================\n";
    cout << "          LIHAT DATA BARANG           \n";
    cout << "======================================\n";
    cout << "1. Nama (Descending - Bubble Sort)\n";
    cout << "2. Harga (Ascending - Selection Sort)\n";
    cout << "3. Stok (Ascending - Insertion Sort)\n";

    try {
        cout << "Pilih metode sorting (1-3): ";
        if (!(cin >> pilihSort)) {
            throw invalid_argument("Pilihan harus berupa angka!");
        }
        if (pilihSort < 1 || pilihSort > 3) {
            throw out_of_range("Pilihan diluar jangkauan (1-3)!");
        }

        if(pilihSort == 1) bubbleSortNamaDesc(dataBarang, jumlahBarang);
        else if(pilihSort == 2) selectionSortHargaAsc(dataBarang, jumlahBarang);
        else insertionSortStokAsc(dataBarang, jumlahBarang);

        cout << fixed << setprecision(0);
        cout << "\n=================================================================\n";
        cout << left << setw(10) << "Kode"
             << setw(20) << "Nama"
             << setw(10) << "Ukuran"
             << setw(10) << "Stok"
             << setw(15) << "Harga" << endl;
        cout << "=================================================================\n";

        tampilBarangRekursif(dataBarang, jumlahBarang, 0);

        cout << "=================================================================\n";

    } catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << endl;
        cin.clear();
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    tekanEnter();
}

void updateBarang(Barang dataBarang[], int *jumlahBarang){
    clearScreen();
    if(*jumlahBarang == 0){
        cout << "[!] Data kosong!\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tekanEnter();
        return;
    }

    cout << "======================================\n";
    cout << "         UPDATE DATA BARANG           \n";
    cout << "======================================\n";
    
    cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(10) << "Ukuran" << setw(10) << "Stok" << setw(15) << "Harga" << endl;
    cout << "-----------------------------------------------------------------\n";
    tampilBarangRekursif(dataBarang, jumlahBarang, 0);
    cout << "-----------------------------------------------------------------\n";

    try {
        string kode;
        cout << "\nMasukkan kode barang yang ingin diupdate: ";
        cin >> kode;

        int index = cariBarang(dataBarang, jumlahBarang, kode);

        //melempar error jika data tidak ditemukan
        if(index == -1) {
            throw out_of_range("Barang dengan kode tersebut tidak ditemukan!");
        }

        Barang *ptr = &dataBarang[index];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string namaBaru, ukuranBaru, stokBaru, hargaBaru;

        cout << "\n(Tekan Enter/Kosongkan jika tidak ingin diubah)\n";

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
        
        if(stokBaru != "") {
            int tempStok = stoi(stokBaru);
            if (tempStok < 0) throw runtime_error("Stok tidak boleh negatif!");
            ptr->stok = tempStok;
        }
        
        if(hargaBaru != "") {
            double tempHarga = stod(hargaBaru);
            if (tempHarga < 0) throw runtime_error("Harga tidak boleh negatif!");
            ptr->harga = tempHarga;
        }

        cout << "\nData berhasil diupdate!\n";

    } catch (const invalid_argument& e) {
        cout << "\n[ERROR] Input gagal! Pastikan stok/harga diisi dengan angka bulat/desimal.\n";
        cin.clear();
    } catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << endl;
    }

    tekanEnter(); 
}

void hapusBarang(Barang dataBarang[], int *jumlahBarang){
    clearScreen();
    if(*jumlahBarang == 0){
        cout << "[!] Data kosong!\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tekanEnter();
        return;
    }

    cout << "======================================\n";
    cout << "          HAPUS DATA BARANG           \n";
    cout << "======================================\n";

    cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(10) << "Ukuran" << setw(10) << "Stok" << setw(15) << "Harga" << endl;
    cout << "-----------------------------------------------------------------\n";
    tampilBarangRekursif(dataBarang, jumlahBarang, 0);
    cout << "-----------------------------------------------------------------\n";

    try {
        string kode;
        cout << "\nMasukkan kode barang yang ingin dihapus: ";
        cin >> kode;

        int index = cariBarang(dataBarang, jumlahBarang, kode);

        if(index == -1){
            throw out_of_range("Kode barang tidak ditemukan di dalam sistem!");
        }

        for(int i = index; i < (*jumlahBarang) - 1; i++){
            dataBarang[i] = dataBarang[i+1];
        }
        (*jumlahBarang)--;

        cout << "\nData berhasil dihapus!\n";

    } catch(const exception& e) {
        cout << "\n[ERROR] " << e.what() << endl;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    tekanEnter();
}

void cariData(Barang dataBarang[], int *jumlahBarang){
    clearScreen();
    if(*jumlahBarang == 0){
        cout << "[!] Data kosong!\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tekanEnter();
        return;
    }

    cout << "======================================\n";
    cout << "           CARI DATA BARANG           \n";
    cout << "======================================\n";
    cout << "1. Cari berdasarkan Kode (Binary Search)\n";
    cout << "2. Cari berdasarkan Nama (Linear Search)\n";
    
    try {
        int pilih;
        cout << "Pilih metode (1-2): ";
        if (!(cin >> pilih)) {
            throw invalid_argument("Pilihan harus berupa angka!");
        }

        if(pilih == 1){
            string kode;
            cout << "Masukkan kode barang: ";
            cin >> kode;

            sortKodeAsc(dataBarang, jumlahBarang); 
            int index = binarySearchKode(dataBarang, jumlahBarang, kode);

            if(index == -1) throw logic_error("Data dengan kode tersebut tidak ditemukan.");

            cout << "\nData ditemukan:\n";
            cout << "=================================================================\n";
            cout << left << setw(10) << "Kode"
                 << setw(20) << "Nama"
                 << setw(10) << "Ukuran"
                 << setw(10) << "Stok"
                 << setw(15) << "Harga" << endl;
            cout << "=================================================================\n";
            cout << left << setw(10) << dataBarang[index].kode
                 << setw(20) << dataBarang[index].nama
                 << setw(10) << dataBarang[index].detail.ukuran
                 << setw(10) << dataBarang[index].stok
                 << setw(15) << dataBarang[index].harga << endl;
            cout << "=================================================================\n";
            
        }
        else if(pilih == 2){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string nama;
            cout << "Masukkan nama barang: ";
            getline(cin, nama);

            int index = linearSearchNama(dataBarang, jumlahBarang, nama);

            if(index == -1) throw logic_error("Data dengan nama tersebut tidak ditemukan.");

            cout << "\nData ditemukan:\n";
            cout << "=================================================================\n";
            cout << left << setw(10) << "Kode"
                 << setw(20) << "Nama"
                 << setw(10) << "Ukuran"
                 << setw(10) << "Stok"
                 << setw(15) << "Harga" << endl;
            cout << "=================================================================\n";
            cout << left << setw(10) << dataBarang[index].kode
                 << setw(20) << dataBarang[index].nama
                 << setw(10) << dataBarang[index].detail.ukuran
                 << setw(10) << dataBarang[index].stok
                 << setw(15) << dataBarang[index].harga << endl;
            cout << "=================================================================\n";
        } else {
            throw out_of_range("Pilihan di luar jangkauan!");
        }

    } catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << endl;
        cin.clear();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    tekanEnter();
}

//MENU UTAMA
int main(){
    User admin = {"ghina", "054"};

    if(!login(&admin)){
        cout << "\n[!] Anda telah gagal login 3 kali. Program dihentikan.\n";
        return 0;
    }

    int pilihan;

    do {
        clearScreen();
        cout << "======================================\n";
        cout << "              MENU UTAMA              \n";
        cout << "======================================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Cari Barang\n";
        cout << "6. Keluar\n";
        cout << "======================================\n";
        
        try {
            cout << "Pilih (1-6): ";
            if (!(cin >> pilihan)) {
                throw invalid_argument("Input tidak valid! Harap masukkan angka.");
            }

            switch(pilihan){
                case 1: tambahBarang(dataBarang, &jumlahBarang); break;
                case 2: lihatBarang(dataBarang, &jumlahBarang); break;
                case 3: updateBarang(dataBarang, &jumlahBarang); break;
                case 4: hapusBarang(dataBarang, &jumlahBarang); break;
                case 5: cariData(dataBarang, &jumlahBarang); break;
                case 6: cout << "\nTerima kasih telah menggunakan program ini!\n"; break;
                default: throw out_of_range("Pilihan tidak ada di menu!");
            }
        } catch (const exception& e) {
            cout << "\n[ERROR] " << e.what() << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            tekanEnter();
        }

    } while(pilihan != 6);

    return 0;
}