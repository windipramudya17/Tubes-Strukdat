#include "menu.h"
#include <stdlib.h>

const string ADMIN_USER = "admin";
const string ADMIN_PASS = "admin123";

// Username yang bisa digunakan : windi, ariel, ida, arya, jessie

// ========== AUTHENTICATION ==========
void tampilkanHeader(){
    cout << "===============================================================" << endl;
    cout << "                              COTIFY                           "<< endl;
    cout << "                       MUSIC STREAMING APP V2.0                " << endl;
    cout << "===============================================================" << endl;
}

bool login(CurrentUser &current, ListUser LU){
    string username, password;
    int pilihan;

    system("cls");
    tampilkanHeader();

    cout << "\n[1] Login sebagai Admin" << endl;
    cout << "[2] Login sebagai User" << endl;
    cout << "[0] Keluar" << endl;
    cout << "\nPilihan: ";
    cin >> pilihan;

    if(pilihan == 0) return false;

    system("cls");
    tampilkanHeader();

    if(pilihan == 1){
        cout << "\n=== LOGIN ADMIN ===" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if(username == ADMIN_USER && password == ADMIN_PASS){
            current.username = username;
            current.role = "admin";
            current.isLoggedIn = true;
            cout << "\nLogin berhasil! Selamat datang Admin!\n";
            system("pause");
            return true;
        }
        cout << "\nUsername/password salah!\n";
        system("pause");
        return false;
    }
    else if(pilihan == 2){
        cout << "\n=== LOGIN USER ===" << endl;
        cout << "Username: ";
        cin >> username;

        adrUser U = findUser(LU, username);
        if(U != NULL){
            current.username = username;
            current.role = "user";
            current.isLoggedIn = true;
            cout << "\nLogin berhasil! Selamat datang " << U->info.nama_lengkap << "!\n";
            system("pause");
            return true;
        }
        cout << "\nUsername tidak ditemukan!\n";
        system("pause");
        return false;
    }

    cout << "\nPilihan tidak valid!\n";
    system("pause");
    return false;
}

void logout(CurrentUser &current){
    current.username = "";
    current.role = "";
    current.isLoggedIn = false;
}

// ========== MENU ADMIN ==========
void menuAdmin(ListUser &LU, List_lagu &LL){
    int pil;
    string username, judul;
    adrUser U;
    address_lagu L;

    do{
        system("cls");
        tampilkanHeader();
        cout << "\n=== ADMIN DASHBOARD ===" << endl;
        cout << "\n--- USER MANAGEMENT ---" << endl;
        cout << "1. Lihat Semua User" << endl;
        cout << "2. Lihat Detail User & Playlistnya" << endl;
        cout << "3. Hapus User" << endl;
        cout << "\n--- MUSIC DATABASE ---" << endl;
        cout << "4. Lihat Semua Lagu" << endl;
        cout << "5. Tambah Lagu Baru" << endl;
        cout << "6. Edit Info Lagu" << endl;
        cout << "7. Hapus Lagu" << endl;
        cout << "\n--- ANALYTICS ---" << endl;
        cout << "8. Statistik Global" << endl;
        cout << "\n0. Logout" << endl;
        cout << "\nPilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("cls");
            printAllUsers(LU);
            system("pause");
            break;

        case 2:
            system("cls");
            printAllUsers(LU);
            cout << "Username: ";
            cin >> username;
            U = findUser(LU, username);
            if(U != NULL){
                cout << "\n";
                showUser(U);
                printAllPlaylists(U);
            }else{
                cout << "\nUser tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 3:
            system("cls");
            printAllUsers(LU);
            cout << "Username yang akan dihapus: ";
            cin >> username;
            U = findUser(LU, username);
            if(U != NULL){
                deleteUser(LU, U);
                cout << "\nUser berhasil dihapus!\n";
            }else{
                cout << "\nUser tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 4:
            printInfo_lagu(LL);
            cout << "Total: " << hitungLagu(LL) << " lagu\n";
            system("pause");
            break;

        case 5:
            system("cls");
            cout << "=== TAMBAH LAGU BARU ===" << endl;
            L = input_lagu();
            insertLast_lagu(LL, L);
            cout << "\nLagu berhasil ditambahkan!\n";
            system("pause");
            break;

        case 6:
            printInfo_lagu(LL);
            cout << "Judul lagu yang akan diedit: ";
            cin.ignore();
            getline(cin, judul);
            L = findElm_lagu(LL, judul);
            if(L != NULL){
                cout << "\n=== EDIT LAGU ===" << endl;
                editInfo_lagu(L);
                cout << "\nLagu berhasil diedit!\n";
            }else{
                cout << "\nLagu tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 7:
            printInfo_lagu(LL);
            cout << "Judul lagu yang akan dihapus: ";
            cin.ignore();
            getline(cin, judul);
            L = findElm_lagu(LL, judul);
            if(L != NULL){
                deleteSearch_lagu(LL, L);
                cout << "\nLagu berhasil dihapus!\n";
            }else{
                cout << "\nLagu tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 8:
            statistikGlobal(LU, LL);
            system("pause");
            break;

        case 0:
            cout << "\nLogout berhasil!\n";
            system("pause");
            break;

        default:
            cout << "\nPilihan tidak valid!\n";
            system("pause");
            break;
        }
    }while(pil != 0);
}

// ========== MENU USER ==========
void menuUser(ListUser &LU, List_lagu &LL, string username){
    adrUser U = findUser(LU, username);
    if(U == NULL) return;

    int pil;

    do{
        system("cls");
        tampilkanHeader();
        cout << "\n=== USER: " << U->info.username << " (" << U->info.tipe_akun << ") ===" << endl;
        cout << "Playlist: " << hitungPlaylist(U) << " | ";

        // Hitung total play
        int totalPlay = 0;
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            totalPlay += getTotalPlayCount(PL);
            PL = PL->next;
        }
        cout << "Total Play: " << totalPlay << "x" << endl;

        cout << "\n--- MY LIBRARY ---" << endl;
        cout << "1. Lihat Semua Playlist" << endl;
        cout << "2. Buat Playlist Baru" << endl;
        cout << "3. Hapus Playlist" << endl;
        cout << "4. Edit Playlist" << endl;
        cout << "\n--- PLAYLIST MANAGEMENT ---" << endl;
        cout << "5. Lihat Isi Playlist" << endl;
        cout << "6. Tambah Lagu ke Playlist" << endl;
        cout << "7. Hapus Lagu dari Playlist" << endl;
        cout << "8. Play Lagu" << endl;
        cout << "\n--- ACCOUNT ---" << endl;
        cout << "9. Edit Profil" << endl;
        cout << "\n0. Logout" << endl;
        cout << "\nPilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("cls");
            lihatSemuaPlaylist(U);
            system("pause");
            break;

        case 2:
            buatPlaylistBaru(U);
            system("pause");
            break;

        case 3:
            hapusPlaylistUser(U);
            system("pause");
            break;

        case 4:
            editPlaylistUser(U);
            system("pause");
            break;

        case 5:
            lihatIsiPlaylistMenu(U);
            system("pause");
            break;

        case 6:
            tambahLaguKePlaylistMenu(U, LL);
            system("pause");
            break;

        case 7:
            hapusLaguDariPlaylistMenu(U);
            system("pause");
            break;

        case 8:
            playLaguMenu(U);
            system("pause");
            break;

        case 9:
            system("cls");
            cout << "=== EDIT PROFIL ===" << endl;
            editUser(U);
            cout << "\nProfil berhasil diupdate!\n";
            system("pause");
            break;

        case 0:
            cout << "\nLogout berhasil!\n";
            system("pause");
            break;

        default:
            cout << "\nPilihan tidak valid!\n";
            system("pause");
            break;
        }
    }while(pil != 0);
}

// ========== USER OPERATIONS ==========
void lihatSemuaPlaylist(adrUser U){
    system("cls");
    cout << "=== PLAYLIST: " << U->info.username << " ===" << endl;
    printAllPlaylists(U);
}

void buatPlaylistBaru(adrUser U){
    system("cls");
    cout << "=== BUAT PLAYLIST BARU ===" << endl;
    adrPlaylist P = inputPlaylist(U);
    insertLastPlaylist(U, P);
    cout << "\nPlaylist berhasil dibuat!\n";
}

void hapusPlaylistUser(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string nama;
    cout << "Nama playlist yang akan dihapus: ";
    cin.ignore();
    getline(cin, nama);

    adrPlaylist P = findPlaylist(U, nama);
    if(P != NULL){
        deletePlaylist(U, P);
        cout << "\nPlaylist berhasil dihapus!\n";
    }else{
        cout << "\nPlaylist tidak ditemukan!\n";
    }
}

void editPlaylistUser(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string nama;
    cout << "Nama playlist yang akan diedit: ";
    cin.ignore();
    getline(cin, nama);

    adrPlaylist P = findPlaylist(U, nama);
    if(P != NULL){
        cout << "\n=== EDIT PLAYLIST ===" << endl;
        editPlaylist(P);
        cout << "\nPlaylist berhasil diedit!\n";
    }else{
        cout << "\nPlaylist tidak ditemukan!\n";
    }
}

void tambahLaguKePlaylistMenu(adrUser U, List_lagu LL){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist, judulLagu;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        return;
    }

    printInfo_lagu(LL);
    cout << "Judul lagu: ";
    getline(cin, judulLagu);

    address_lagu L = findElm_lagu(LL, judulLagu);
    if(L != NULL){
        tambahLaguKePlaylist(U, PL, L);
    }else{
        cout << "\nLagu tidak ditemukan!\n";
    }
}

void hapusLaguDariPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist, judulLagu;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        return;
    }

    printIsiPlaylist(PL);
    cout << "Judul lagu yang akan dihapus: ";
    getline(cin, judulLagu);

    adrItem IT = PL->firstItem;
    address_lagu L = NULL;
    while(IT != NULL){
        if(info_lagu(IT->lagu).judul == judulLagu){
            L = IT->lagu;
            break;
        }
        IT = IT->next;
    }

    if(L != NULL){
        hapusLaguDariPlaylist(PL, L);
    }else{
        cout << "\nLagu tidak ada di playlist!\n";
    }
}

void playLaguMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist, judulLagu;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        return;
    }

    printIsiPlaylist(PL);
    cout << "Judul lagu yang akan diputar: ";
    getline(cin, judulLagu);

    adrItem IT = PL->firstItem;
    address_lagu L = NULL;
    while(IT != NULL){
        if(info_lagu(IT->lagu).judul == judulLagu){
            L = IT->lagu;
            break;
        }
        IT = IT->next;
    }

    if(L != NULL){
        playLagu(PL, L);
    }else{
        cout << "\nLagu tidak ada di playlist!\n";
    }
}

void lihatIsiPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL != NULL){
        system("cls");
        showPlaylist(PL);
        printIsiPlaylist(PL);
    }else{
        cout << "\nPlaylist tidak ditemukan!\n";
    }
}

// ========== STATISTIK ==========
void statistikGlobal(ListUser LU, List_lagu LL){
    system("cls");
    cout << "========== STATISTIK GLOBAL ==========" << endl;

    int totalUser = hitungUser(LU);
    int totalLagu = hitungLagu(LL);
    int totalPlaylist = 0;
    int totalPlay = 0;

    adrUser U = LU.first;
    while(U != NULL){
        totalPlaylist += hitungPlaylist(U);
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            totalPlay += getTotalPlayCount(PL);
            PL = PL->next;
        }
        U = U->next;
    }

    cout << "\nTotal User: " << totalUser << endl;
    cout << "Total Lagu: " << totalLagu << endl;
    cout << "Total Playlist: " << totalPlaylist << endl;
    cout << "Total Play Count: " << totalPlay << "x" << endl;

    laguTerpopulerGlobal(LU);
    userTeraktif(LU);
    cout << "\n======================================" << endl;
}

void laguTerpopulerGlobal(ListUser LU){
    cout << "\n========== TOP 10 LAGU TERPOPULER ==========" << endl;

    // Array untuk menyimpan lagu dan play count
    address_lagu laguList[100];
    int playCount[100];
    int totalLagu = 0;

    // Kumpulkan semua lagu lalu hitung total play count
    adrUser U = LU.first;
    while(U != NULL){
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            adrItem IT = PL->firstItem;
            while(IT != NULL){
                // Cek apakah lagu sudah ada di list
                bool found = false;
                for(int i = 0; i < totalLagu; i++){
                    if(laguList[i] == IT->lagu){
                        playCount[i] += IT->play_count;
                        found = true;
                        break;
                    }
                }

                if(!found){
                    laguList[totalLagu] = IT->lagu;
                    playCount[totalLagu] = IT->play_count;
                    totalLagu++;
                }

                IT = IT->next;
            }
            PL = PL->next;
        }
        U = U->next;
    }

    // Sort descending
    for(int i = 0; i < totalLagu - 1; i++){
        for(int j = 0; j < totalLagu - i - 1; j++){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                address_lagu tempLagu = laguList[j];
                laguList[j] = laguList[j+1];
                laguList[j+1] = tempLagu;
            }
        }
    }

    // Tampilkan top 10
    int limit = (totalLagu < 10) ? totalLagu : 10;
    for(int i = 0; i < limit; i++){
        if(playCount[i] > 0){
            cout << (i+1) << ". " << info_lagu(laguList[i]).judul
                 << " - " << info_lagu(laguList[i]).artis
                 << " (" << playCount[i] << "x play)" << endl;
        }
    }
}

void userTeraktif(ListUser LU){
    cout << "\n========== TOP 5 USER TERAKTIF ==========" << endl;

    adrUser userList[50];
    int playCount[50];
    int totalUser = 0;

    adrUser U = LU.first;
    while(U != NULL){
        userList[totalUser] = U;
        playCount[totalUser] = 0;

        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            playCount[totalUser] += getTotalPlayCount(PL);
            PL = PL->next;
        }

        totalUser++;
        U = U->next;
    }

    // Sort descending
    for(int i = 0; i < totalUser - 1; i++){
        for(int j = 0; j < totalUser - i - 1; j++){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                adrUser tempUser = userList[j];
                userList[j] = userList[j+1];
                userList[j+1] = tempUser;
            }
        }
    }

    int limit = (totalUser < 5) ? totalUser : 5;
    for(int i = 0; i < limit; i++){
        if(playCount[i] > 0){
            cout << (i+1) << ". " << userList[i]->info.username
                 << " (" << userList[i]->info.nama_lengkap << ") - "
                 << playCount[i] << "x play" << endl;
        }
    }
}

// ========== DATA DUMMY ==========
void dataDummy(ListUser &LU, List_lagu &LL){
    // User sudah ada dari dataUser()
    adrUser U;
    adrPlaylist PL;
    address_lagu L;
    adrItem IT;
    infoPlaylist plInfo;

    // === Windi ===
    U = findUser(LU, "windi");
    if(U != NULL){
        // Playlist 1: My Favorites
        plInfo = {1, "My Favorites", "Lagu-lagu favorit saya", "01/01/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 2);  // Shape of You
        IT = alokasiItem(L);
        IT->play_count = 25;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 3);  // Blinding Lights
        IT = alokasiItem(L);
        IT->play_count = 18;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 6);  // Bad Guy
        IT = alokasiItem(L);
        IT->play_count = 12;
        insertLastItem(PL, IT);

        // Playlist 2: Workout
        plInfo = {2, "Workout Mix", "Energi untuk olahraga", "15/01/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 14);  // Lose Yourself
        IT = alokasiItem(L);
        IT->play_count = 30;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 4);  // Starboy
        IT = alokasiItem(L);
        IT->play_count = 15;
        insertLastItem(PL, IT);
    }

    // === ariel ===
    U = findUser(LU, "ariel");
    if(U != NULL){
        plInfo = {3, "Lagu Santai", "Untuk relaksasi", "10/02/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 5);  // Someone Like You
        IT = alokasiItem(L);
        IT->play_count = 20;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 10);  // Anti-Hero
        IT = alokasiItem(L);
        IT->play_count = 15;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 16);  // Perfect
        IT = alokasiItem(L);
        IT->play_count = 10;
        insertLastItem(PL, IT);
    }

    // === arya ===
    U = findUser(LU, "arya");
    if(U != NULL){
        plInfo = {4, "Rock Legends", "Classic rock hits", "20/02/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 1);  // Bohemian Rhapsody
        IT = alokasiItem(L);
        IT->play_count = 35;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 11);  // Hotel California
        IT = alokasiItem(L);
        IT->play_count = 28;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 12);  // Wonderwall
        IT = alokasiItem(L);
        IT->play_count = 22;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 15);  // Smells Like Teen
        IT = alokasiItem(L);
        IT->play_count = 18;
        insertLastItem(PL, IT);
    }

    // === ida ===
    U = findUser(LU, "ida");
    if(U != NULL){
        plInfo = {5, "Pop Hits 2020s", "Best pop songs", "01/03/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 7);  // Levitating
        IT = alokasiItem(L);
        IT->play_count = 40;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 8);  // Stay
        IT = alokasiItem(L);
        IT->play_count = 32;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 9);  // As It Was
        IT = alokasiItem(L);
        IT->play_count = 27;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 17);  // Peaches
        IT = alokasiItem(L);
        IT->play_count = 19;
        insertLastItem(PL, IT);

        plInfo = {6, "Study Music", "Fokus belajar", "15/03/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 18);  // Watermelon Sugar
        IT = alokasiItem(L);
        IT->play_count = 12;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 19);  // Save Your Tears
        IT = alokasiItem(L);
        IT->play_count = 8;
        insertLastItem(PL, IT);
    }

    // === Jessie ===
    U = findUser(LU, "jessie");
    if(U != NULL){
        plInfo = {7, "Hip-Hop Vibes", "Best rap songs", "10/03/2024"};
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 14);  // Lose Yourself
        IT = alokasiItem(L);
        IT->play_count = 45;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 4);  // Starboy
        IT = alokasiItem(L);
        IT->play_count = 22;
        insertLastItem(PL, IT);
    }
}
