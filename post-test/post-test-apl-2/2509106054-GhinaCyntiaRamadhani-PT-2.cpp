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

int main() {

//LOGIN
    User admin;
    admin.nama = "ghina";   
    admin.nim  = "054";    

    string inputNama;
    string inputNim;
    int sisaKesempatan = 3;
    bool loginBerhasil = false;

    while (sisaKesempatan > 0) {
        system("cls");
        cout << "=== LOGIN ===\n";
        cout << "Username (Nama): ";
        cin >> inputNama;

        cout << "Password (NIM): ";
        cin >> inputNim;

        if (inputNama == admin.nama && inputNim == admin.nim) {
            loginBerhasil = true;
            break;
        } else {
            sisaKesempatan--;
            cout << "Login gagal! Sisa kesempatan: "
                 << sisaKesempatan << endl;

            cout << "\nTekan enter untuk lanjut. . .";
            cin.ignore();
            cin.get();
            system("cls");
        }
    }

    if (!loginBerhasil) {
        cout << "Anda gagal login 3 kali. Program berhenti.\n";
        return 0;
    }

    int pilihanMenu;

//MENU UTAMA
    do {
        system("cls");
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1/2/3/4/5): ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {

            case 1:
            {
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

            cout << "\nTekan enter untuk lanjut. . .";
            cin.ignore();
            cin.get();
            break;
            }

            case 2:
            {
                system("cls");

                if (jumlahBarang == 0) {
                    cout << "Tidak ada data.\n";
                } else {

                    cout << fixed << setprecision(0);

                    cout << "====================================================================\n";
                    cout << left << setw(10) << "Kode"
                         << setw(20) << "Nama"
                         << setw(10) << "Ukuran"
                         << setw(10) << "Stok"
                         << setw(15) << "Harga" << endl;
                    cout << "====================================================================\n";

                    for (int i = 0; i < jumlahBarang; i++) {
                        cout << left << setw(10) << dataBarang[i].kode
                             << setw(20) << dataBarang[i].nama
                             << setw(10) << dataBarang[i].detail.ukuran
                             << setw(10) << dataBarang[i].stok
                             << setw(15) << dataBarang[i].harga << endl;
                    }

                    cout << "====================================================================\n";
                }

                cout << "\nTekan enter untuk lanjut. . .";
                cin.ignore();
                cin.get();
                break;
            }

            case 3:
            {
                string kodeDicari;
                bool ditemukan = false;

                system("cls");
                cout << "Masukkan kode barang yang ingin diupdate: ";
                cin >> kodeDicari;

                for (int i = 0; i < jumlahBarang; i++) {
                    if (dataBarang[i].kode == kodeDicari) {
                        ditemukan = true;
                        system("cls");

                        cout << "=== Data Barang ===\n";
                        cout << "Kode   : " << dataBarang[i].kode << endl;
                        cout << "Nama   : " << dataBarang[i].nama << endl;
                        cout << "Ukuran : " << dataBarang[i].detail.ukuran << endl;
                        cout << "Stok   : " << dataBarang[i].stok << endl;
                        cout << "Harga  : " << dataBarang[i].harga << endl;

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

                        if (namaBaru != "")
                            dataBarang[i].nama = namaBaru;

                        if (ukuranBaru != "")
                            dataBarang[i].detail.ukuran = ukuranBaru;

                        if (stokInput != "")
                            dataBarang[i].stok = stoi(stokInput);

                        if (hargaInput != "")
                            dataBarang[i].harga = stod(hargaInput);

                        cout << "\nData berhasil diupdate!\n";
                        break;
                    }
                }

                if (!ditemukan) {
                    cout << "Data tidak ditemukan.\n";
                }

                cout << "\nTekan enter untuk lanjut. . .";
                cin.ignore();
                cin.get();
                break;
            }

            case 4:
            {
                string kodeDicari;
                bool ditemukan = false;

                system("cls");
                cout << "Masukkan kode barang yang ingin dihapus: ";
                cin >> kodeDicari;

                for (int i = 0; i < jumlahBarang; i++) {
                    if (dataBarang[i].kode == kodeDicari) {

                        for (int j = i; j < jumlahBarang - 1; j++) {
                            dataBarang[j] = dataBarang[j + 1];
                        }

                        jumlahBarang--;
                        cout << "\nData berhasil dihapus!\n";
                        ditemukan = true;
                        break;
                    }
                }

                if (!ditemukan) {
                    cout << "Data tidak ditemukan.\n";
                }

                cout << "\nTekan enter untuk lanjut. . .";
                cin.ignore();
                cin.get();
                break;
            }

            case 5:
                cout << "Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
                cout << "\nTekan enter untuk lanjut. . .";
                cin.ignore();
                cin.get();
        }

    } while (pilihanMenu != 5);

    return 0;
}