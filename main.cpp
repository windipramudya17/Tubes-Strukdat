#include <iostream>
#include "playlist.h"
#include "auth.h"

using namespace std;

// Global variables untuk diakses dari auth.cpp
List_pengguna LP;
List_lagu LL;
List_playlist LPL;

int main()
{
    CurrentUser currentUser;
    currentUser.isLoggedIn = false;

    createList_pengguna(LP);
    createList_lagu(LL);
    createList_playlist(LPL);

    // Load data dummy
    data_pengguna(LP);
    data_lagu(LL);
    data_playlist(LPL, LP, LL);

    // Main loop
    while(true){
        // Proses login
        if(!login(currentUser)){
            // User memilih keluar atau login gagal
            break;
        }

        // Setelah login berhasil, masuk ke menu sesuai role
        if(isAdmin(currentUser)){
            menuAdmin(LP, LL, LPL, currentUser.username);
        }
        else if(isUser(currentUser)){
            menuUser(LP, LL, LPL, currentUser.username);
        }

        // Setelah logout, kembali ke login screen
        logout(currentUser);
    }

    system("cls");
    cout << "\n===========================================================" << endl;
    cout << "  Terima kasih telah menggunakan Spotify Clone!" << endl;
    cout << "  Sampai jumpa lagi!" << endl;
    cout << "===========================================================" << endl;

    return 0;
}
