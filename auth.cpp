#include "auth.h"
#include "pengguna.h"
#include <stdlib.h>

extern List_pengguna LP; // Akses list pengguna dari main

void tampilkanHeader(){
    cout << "===========================================================" << endl;
    cout << "        ___  ____   ___ _____ ___ _______   __" << endl;
    cout << "       / __|  _ \\ / _ \\_   _|_ _|  ___\\ \\ / /" << endl;
    cout << "       \\__ \\ |_) | |_| || |  | || |_   \\ V /" << endl;
    cout << "       |___/  __/ \\___/ |_| |___|_|     |_|" << endl;
    cout << "          |_|  MUSIC STREAMING APP" << endl;
    cout << "===========================================================" << endl;
}

void tampilkanWelcome(){
    system("cls");
    tampilkanHeader();
    cout << "\n";
    cout << "  Selamat datang di Spotify Clone - Music Streaming App!" << endl;
    cout << "  Nikmati jutaan lagu favorit Anda kapan saja!" << endl;
    cout << "\n";
    cout << "===========================================================" << endl;
}

bool login(CurrentUser &current){
    string username, password;
    int pilihan;

    tampilkanWelcome();

    cout << "\n";
    cout << "  [1] Login sebagai Admin" << endl;
    cout << "  [2] Login sebagai User" << endl;
    cout << "  [0] Keluar" << endl;
    cout << "\n";
    cout << "  Pilihan Anda: ";
    cin >> pilihan;

    if(pilihan == 0){
        return false;
    }

    system("cls");
    tampilkanHeader();

    if(pilihan == 1){
        cout << "\n=== LOGIN ADMIN ===" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if(username == ADMIN_USERNAME && password == ADMIN_PASSWORD){
            current.username = username;
            current.role = "admin";
            current.isLoggedIn = true;

            cout << "\n Login berhasil! Selamat datang Admin!" << endl;
            system("pause");
            return true;
        }
        else{
            cout << "\n Username atau password salah!" << endl;
            system("pause");
            return false;
        }
    }
    else if(pilihan == 2){
        cout << "\n=== LOGIN USER ===" << endl;
        cout << "Username: ";
        cin >> username;

        // Cek apakah username ada di database
        address_pengguna P = findElm_pengguna(LP, username);

        if(P != NULL){
            current.username = username;
            current.role = "user";
            current.isLoggedIn = true;

            cout << "\n Login berhasil!" << endl;
            cout << "Selamat datang, " << info_pengguna(P).nama_lengkap << "!" << endl;
            cout << "Tipe Akun: " << info_pengguna(P).tipe_akun << endl;
            system("pause");
            return true;
        }
        else{
            cout << "\n Username tidak ditemukan!" << endl;
            cout << "Silakan daftar terlebih dahulu." << endl;
            system("pause");
            return false;
        }
    }
    else{
        cout << "\n Pilihan tidak valid!" << endl;
        system("pause");
        return false;
    }
}

void logout(CurrentUser &current){
    current.username = "";
    current.role = "";
    current.isLoggedIn = false;

    cout << "\n  Anda telah logout!" << endl;
    system("pause");
}

bool isAdmin(CurrentUser current){
    return current.isLoggedIn && current.role == "admin";
}

bool isUser(CurrentUser current){
    return current.isLoggedIn && current.role == "user";
}
