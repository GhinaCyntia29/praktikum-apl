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

int cariBarang(string kode){
    for(int i = 0; i < jumlahBarang; i++){
        if(dataBarang[i].kode == kode){
            return i;
        }
    }
    return -1;
}

//LOGIN
bool login(User admin){

    string inputNama;
    string inputNim;
    int sisaKesempatan = 3;

    while(sisaKesempatan > 0){

        system("cls");
        cout << "=== LOGIN ===\n";

        cout << "Username (Nama): ";
        cin >> inputNama;

        cout << "Password (NIM): ";
        cin >> inputNim;

        if(inputNama == admin.nama && inputNim == admin.nim){
            return true;
        }
        else{
            sisaKesempatan--;
            cout << "Login gagal! Sisa kesempatan: " << sisaKesempatan << endl;
            tekanEnter();
        }
    }

    return false;
}

//FUNGSI REKURSIF UNTUK MENAMPILKAN DATA BARANG
void tampilBarangRekursif(int index){

    if(index == jumlahBarang){
        return;
    }

    cout << left << setw(10) << dataBarang[index].kode
         << setw(20) << dataBarang[index].nama
         << setw(10) << dataBarang[index].detail.ukuran
         << setw(10) << dataBarang[index].stok
         << setw(15) << dataBarang[index].harga << endl;

    tampilBarangRekursif(index + 1);
}

//PROSEDUR TAMBAH BARANG
void tambahBarang(){

    system("cls");
    cout << "=== Tambah Data Barang ===\n";

    cout << "Kode Barang   : ";
    cin >> dataBarang[jumlahBarang].kode;

    cin.ignore();
    cout << "Nama Barang   : ";
    getline(cin, dataBarang[jumlahBarang].nama);

    cout << "Ukuran        : ";
    getline(cin, dataBarang[jumlahBarang].detail.ukuran);

    cout << "Stok          : ";
    cin >> dataBarang[jumlahBarang].stok;

    cout << "Harga         : ";
    cin >> dataBarang[jumlahBarang].harga;

    jumlahBarang++;

    cout << "\nData berhasil ditambahkan!\n";
    tekanEnter();
}

//PROSEDUR LIHAT BARANG
void lihatBarang(){

    system("cls");

    if(jumlahBarang == 0){
        cout << "Tidak ada data.\n";
    }
    else{

        cout << fixed << setprecision(0);

        cout << "====================================================================\n";
        cout << left << setw(10) << "Kode"
             << setw(20) << "Nama"
             << setw(10) << "Ukuran"
             << setw(10) << "Stok"
             << setw(15) << "Harga" << endl;

        cout << "====================================================================\n";

        //TAMPIL DATA DENGAN REKURSIF
        tampilBarangRekursif(0);

        cout << "====================================================================\n";
    }

    tekanEnter();
}

//PROSEDUR UPDATE BARANG
void updateBarang(){

    string kodeDicari;

    system("cls");

    cout << "Masukkan kode barang yang ingin diupdate: ";
    cin >> kodeDicari;

    int index = cariBarang(kodeDicari);

    if(index != -1){

        system("cls");

        cout << "=== Data Barang ===\n";
        cout << "Kode   : " << dataBarang[index].kode << endl;
        cout << "Nama   : " << dataBarang[index].nama << endl;
        cout << "Ukuran : " << dataBarang[index].detail.ukuran << endl;
        cout << "Stok   : " << dataBarang[index].stok << endl;
        cout << "Harga  : " << dataBarang[index].harga << endl;

        cin.ignore();

        string namaBaru, ukuranBaru;
        string stokInput, hargaInput;

        cout << "\n(Kosongkan jika tidak ingin diubah)\n";

        cout << "Nama baru   : ";
        getline(cin, namaBaru);

        cout << "Ukuran baru : ";
        getline(cin, ukuranBaru);

        cout << "Stok baru   : ";
        getline(cin, stokInput);

        cout << "Harga baru  : ";
        getline(cin, hargaInput);

        if(namaBaru != "")
            dataBarang[index].nama = namaBaru;

        if(ukuranBaru != "")
            dataBarang[index].detail.ukuran = ukuranBaru;

        if(stokInput != "")
            dataBarang[index].stok = stoi(stokInput);

        if(hargaInput != "")
            dataBarang[index].harga = stod(hargaInput);

        cout << "\nData berhasil diupdate!\n";
    }
    else{
        cout << "Data tidak ditemukan.\n";
    }

    tekanEnter();
}

//PROSEDUR HAPUS BARANG
void hapusBarang(){

    string kodeDicari;

    system("cls");

    cout << "Masukkan kode barang yang ingin dihapus: ";
    cin >> kodeDicari;

    int index = cariBarang(kodeDicari);

    if(index != -1){

        for(int i = index; i < jumlahBarang - 1; i++){
            dataBarang[i] = dataBarang[i+1];
        }

        jumlahBarang--;

        cout << "\nData berhasil dihapus!\n";
    }
    else{
        cout << "Data tidak ditemukan.\n";
    }

    tekanEnter();
}

//MENU UTAMA
int main(){

    User admin;
    admin.nama = "ghina";
    admin.nim  = "054";

    if(!login(admin)){
        cout << "Anda gagal login 3 kali. Program berhenti.\n";
        return 0;
    }

    int pilihanMenu;

    do{

        system("cls");

        cout << "=== MENU UTAMA ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";

        cout << "Pilih menu (1/2/3/4/5): ";
        cin >> pilihanMenu;

        switch(pilihanMenu){

            case 1:
                tambahBarang();
                break;

            case 2:
                lihatBarang();
                break;

            case 3:
                updateBarang();
                break;

            case 4:
                hapusBarang();
                break;

            case 5:
                cout << "Terima kasih telah menggunakan program.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
                tekanEnter();
        }

    }while(pilihanMenu != 5);

    return 0;
}