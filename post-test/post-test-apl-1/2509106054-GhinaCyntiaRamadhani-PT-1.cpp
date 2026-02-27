#include <iostream>
#include <cstdlib>  
using namespace std;

int main() {

//LOGIN
    string namaUser;
    string passwordInput;
    string passwordBenar = "054"; 

    int jumlahPercobaanLogin = 0;
    bool statusLoginBerhasil = false;

    cout << "==============================\n";
    cout << "   PROGRAM KONVERSI WAKTU\n";
    cout << "=============================\n\n";

    while (jumlahPercobaanLogin < 3 && statusLoginBerhasil == false) {

        cout << "LOGIN\n";
        cout << "Nama     : ";
        getline(cin, namaUser);

        cout << "Password : ";
        getline(cin, passwordInput);

        if (passwordInput == passwordBenar) {
            statusLoginBerhasil = true;
            cout << "\nLogin berhasil! Selamat datang, "
                 << namaUser << endl;

            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
        } 
        else {
            jumlahPercobaanLogin = jumlahPercobaanLogin + 1;
            cout << "Password salah! Percobaan ke-"
                 << jumlahPercobaanLogin << endl << endl;
        }
    }

    if (statusLoginBerhasil == false) {
        cout << "Anda gagal login 3 kali.\n";
        cout << "Program berhenti.\n";
        return 0;
    }

//MENU UTAMA
    int pilihanMenu;

    do {
        system("cls");  

        cout << "==============================\n";
        cout << "         MENU UTAMA\n";
        cout << "==============================\n";
        cout << "1. Konversi jam ke menit dan detik\n";
        cout << "2. Konversi menit ke jam dan detik\n";
        cout << "3. Konversi detik ke jam dan menit\n";
        cout << "4. Keluar\n";
        cout << "==============================\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihanMenu;
        cin.ignore(); 

        cout << endl;

        if (pilihanMenu == 1) {

            system("cls");
            cout << "=== KONVERSI JAM KE MENIT DAN DETIK ===\n\n";

            double jumlahJam;
            double hasilMenit;
            double hasilDetik;

            cout << "Masukkan jumlah jam: ";
            cin >> jumlahJam;
            cin.ignore();

            hasilMenit = jumlahJam * 60;
            hasilDetik = jumlahJam * 3600;

            cout << jumlahJam << " jam = "
                 << hasilMenit << " menit dan "
                 << hasilDetik << " detik\n";
        }

        else if (pilihanMenu == 2) {

            system("cls");
            cout << "=== KONVERSI MENIT KE JAM DAN DETIK ===\n\n";

            double jumlahMenit;
            double hasilJam;
            double hasilDetik;

            cout << "Masukkan jumlah menit: ";
            cin >> jumlahMenit;
            cin.ignore();

            hasilJam = jumlahMenit / 60;
            hasilDetik = jumlahMenit * 60;

            cout << jumlahMenit << " menit = "
                 << hasilJam << " jam dan "
                 << hasilDetik << " detik\n";
        }

        else if (pilihanMenu == 3) {

            system("cls");
            cout << "=== KONVERSI DETIK KE JAM DAN MENIT ===\n\n";

            double jumlahDetik;
            double hasilJam;
            double hasilMenit;

            cout << "Masukkan jumlah detik: ";
            cin >> jumlahDetik;
            cin.ignore();

            hasilJam = jumlahDetik / 3600;
            hasilMenit = jumlahDetik / 60;

            cout << jumlahDetik << " detik = "
                 << hasilJam << " jam dan "
                 << hasilMenit << " menit\n";
        }

        else if (pilihanMenu == 4) {
            system("cls");
            cout << "Terima kasih telah menggunakan program.\n";
        }

        else {
            cout << "Pilihan tidak valid!\n";
        }

        cout << "\nTekan Enter untuk kembali ke menu...";
        cin.get();

    } while (pilihanMenu != 4);

    return 0;
}