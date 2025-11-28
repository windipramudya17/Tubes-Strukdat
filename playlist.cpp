#include "playlist.h"

void createList_playlist(List_playlist &L){
    first_playlist(L) = NULL;
}

address_playlist alokasi_playlist(address_pengguna PP, address_lagu PL){
    address_playlist P = new elmList_playlist;
    kelagu(P) = PL;
    kepengguna(P) = PP;
    next_playlist(P) = NULL;
    return P;
}

void dealokasi_playlist(address_playlist &P){
    delete P;
}

void insertFirst_playlist(List_playlist &L, address_playlist P){
    if(first_playlist(L) == NULL){
        first_playlist(L) = P;
    }
    else{
        next_playlist(P) = first_playlist(L);
        first_playlist(L) = P;
    }
}

void insertLast_playlist(List_playlist &L, address_playlist P){
    if(first_playlist(L) == NULL){
        first_playlist(L) = P;
    }
    else{
        address_playlist Q = first_playlist(L);
        while(next_playlist(Q) != NULL){
            Q = next_playlist(Q);
        }
        next_playlist(Q) = P;
    }
}

address_playlist find_playlist(List_playlist L, string username, string judul){
    address_playlist P = first_playlist(L);
    while(P != NULL){
        if(info_pengguna(kepengguna(P)).username == username &&
           info_lagu(kelagu(P)).judul == judul){
            return P;
        }
        P = next_playlist(P);
    }
    return NULL;
}

void deleteFirst_playlist(List_playlist &L, address_playlist &P){
    if(first_playlist(L) != NULL){
        P = first_playlist(L);
        first_playlist(L) = next_playlist(P);
        next_playlist(P) = NULL;
    }
}

void deleteLast_playlist(List_playlist &L, address_playlist &P){
    if(first_playlist(L) != NULL){
        if(next_playlist(first_playlist(L)) == NULL){
            P = first_playlist(L);
            first_playlist(L) = NULL;
        }
        else{
            address_playlist Q = first_playlist(L);
            while(next_playlist(next_playlist(Q)) != NULL){
                Q = next_playlist(Q);
            }
            P = next_playlist(Q);
            next_playlist(Q) = NULL;
        }
    }
}

void deleteAfter_playlist(address_playlist Prec, address_playlist &P){
    if(Prec != NULL){
        P = next_playlist(Prec);
        if(P != NULL){
            next_playlist(Prec) = next_playlist(P);
            next_playlist(P) = NULL;
        }
    }
}

void deleteSearch_playlist(List_playlist &L, address_playlist &P){
    if(P != NULL){
        if(P == first_playlist(L)){
            deleteFirst_playlist(L, P);
        }
        else{
            address_playlist Prec = first_playlist(L);
            while(next_playlist(Prec) != P && Prec != NULL){
                Prec = next_playlist(Prec);
            }
            if(Prec != NULL){
                if(next_playlist(P) == NULL){
                    deleteLast_playlist(L, P);
                }
                else{
                    deleteAfter_playlist(Prec, P);
                }
            }
        }
    }
}

void delete_playlist(List_playlist &L, address_playlist &P){
    deleteSearch_playlist(L, P);
}

void print_playlist(List_playlist L){
    address_playlist P = first_playlist(L);
    if (P == NULL){
        cout << "====================================================================================" << endl;
        cout << "\t\t\t\tDaftar Playlist Pengguna" << endl;
        cout << "====================================================================================" << endl;
        cout << endl;
        cout << "\t\t\t  Belum Ada Playlist yang Dibuat\n" << endl;
    }
    else{
        cout << "====================================================================================" << endl;
        cout << "\t\t\t\tDaftar Playlist Pengguna" << endl;
        cout << "====================================================================================" << endl;
        cout << "Username\t| Nama Pengguna\t| Judul Lagu\t\t| Artis\t\t| Genre\t\t| Durasi" << endl;
        cout << "====================================================================================" << endl;
        while(P != NULL){
            cout << info_pengguna(kepengguna(P)).username << "\t| "
                 << info_pengguna(kepengguna(P)).nama_lengkap << "\t| "
                 << info_lagu(kelagu(P)).judul << "\t| "
                 << info_lagu(kelagu(P)).artis << "\t| "
                 << info_lagu(kelagu(P)).genre << "\t| "
                 << formatDurasi(info_lagu(kelagu(P)).durasi);
            cout << endl;
            P = next_playlist(P);
        }
        cout << "\n";
    }
}

void print_playlist_pengguna(List_playlist L, address_pengguna PP){
    address_playlist P = first_playlist(L);
    int count = 0;
    int total_durasi = 0;

    cout << "\n========== Playlist: " << info_pengguna(PP).username
         << " (" << info_pengguna(PP).nama_lengkap << ") ==========" << endl;
    cout << "Tipe Akun: " << info_pengguna(PP).tipe_akun << endl;
    cout << "\n";

    while(P != NULL){
        if(kepengguna(P) == PP){
            count++;
            cout << count << ". " << info_lagu(kelagu(P)).judul
                 << " - " << info_lagu(kelagu(P)).artis
                 << " [" << info_lagu(kelagu(P)).genre << "]"
                 << " (" << formatDurasi(info_lagu(kelagu(P)).durasi) << ")" << endl;
            total_durasi += info_lagu(kelagu(P)).durasi;
        }
        P = next_playlist(P);
    }

    if(count == 0){
        cout << "Belum ada lagu dalam playlist" << endl;
    }
    else{
        cout << "\n----------------------------------------" << endl;
        cout << "Total Lagu: " << count << " | Total Durasi: " << formatDurasi(total_durasi) << endl;
        cout << "========================================" << endl;
    }
}

void print_pendengar_lagu(List_playlist L, address_lagu PL){
    address_playlist P = first_playlist(L);
    int count = 0;

    cout << "\n========== Pendengar Lagu ==========" << endl;
    cout << "Judul: " << info_lagu(PL).judul << endl;
    cout << "Artis: " << info_lagu(PL).artis << endl;
    cout << "Album: " << info_lagu(PL).album << endl;
    cout << "\nDaftar Pendengar:\n" << endl;

    while(P != NULL){
        if(kelagu(P) == PL){
            count++;
            cout << count << ". " << info_pengguna(kepengguna(P)).username
                 << " (" << info_pengguna(kepengguna(P)).nama_lengkap << ") - "
                 << info_pengguna(kepengguna(P)).tipe_akun << endl;
        }
        P = next_playlist(P);
    }

    if(count == 0){
        cout << "Belum ada pengguna yang mendengarkan lagu ini" << endl;
    }
    else{
        cout << "\n----------------------------------------" << endl;
        cout << "Total Pendengar: " << count << " pengguna" << endl;
        cout << "========================================" << endl;
    }
}

void delete_pengguna_all(List_playlist &LPL, List_pengguna &LP, address_pengguna &PP){
    address_playlist P = first_playlist(LPL);
    address_playlist temp;

    while(P != NULL){
        temp = P;
        P = next_playlist(P);
        if(kepengguna(temp) == PP){
            deleteSearch_playlist(LPL, temp);
            dealokasi_playlist(temp);
        }
    }
    deleteSearch_pengguna(LP, PP);
    dealokasi_pengguna(PP);
}

void delete_lagu_all(List_playlist &LPL, List_lagu &LL, address_lagu &PL){
    address_playlist P = first_playlist(LPL);
    address_playlist temp;

    while(P != NULL){
        temp = P;
        P = next_playlist(P);
        if(kelagu(temp) == PL){
            deleteSearch_playlist(LPL, temp);
            dealokasi_playlist(temp);
        }
    }
    deleteSearch_lagu(LL, PL);
    dealokasi_lagu(PL);
}

void input_playlist(List_pengguna LP, List_lagu LL, List_playlist &LPL){
    address_pengguna PP;
    address_lagu PL;
    address_playlist PPL;
    pengguna pdicari;
    lagu ldicari;

    printInfo_pengguna(LP);
    cout << "\nUsername Pengguna: ";
    cin.ignore();
    getline(cin, pdicari.username);
    PP = findElm_pengguna(LP, pdicari.username);

    if (PP != NULL){
        system("cls");
        printInfo_lagu(LL);
        cout << "\nUsername: " << pdicari.username << endl;
        cout << "Judul Lagu yang ingin ditambahkan: ";
        getline(cin, ldicari.judul);
        PL = findElm_lagu(LL, ldicari.judul);

        if (PL != NULL){
            // Cek apakah lagu sudah ada di playlist
            address_playlist cek = find_playlist(LPL, pdicari.username, ldicari.judul);
            if(cek != NULL){
                cout << "\nLagu sudah ada dalam playlist Anda!" << endl;
            }
            else{
                PPL = alokasi_playlist(PP, PL);
                insertLast_playlist(LPL, PPL);
                cout << "\nLagu Berhasil Ditambahkan ke Playlist!" << endl;
            }
        }
        else{
            cout << "\nLagu tidak ditemukan" << endl;
        }
    }
    else{
        cout << "\nPengguna tidak ditemukan" << endl;
    }
}

void search_pengguna(List_pengguna LP, List_playlist LPL, address_pengguna PP){
    print_playlist_pengguna(LPL, PP);
}

void search_lagu(List_lagu LL, List_playlist LPL, address_lagu PL){
    print_pendengar_lagu(LPL, PL);
}

int hitungPlaylist(List_playlist L){
    int count = 0;
    address_playlist P = first_playlist(L);
    while(P != NULL){
        count++;
        P = next_playlist(P);
    }
    return count;
}

int hitungPlaylistPengguna(List_playlist L, address_pengguna PP){
    int count = 0;
    address_playlist P = first_playlist(L);
    while(P != NULL){
        if(kepengguna(P) == PP){
            count++;
        }
        P = next_playlist(P);
    }
    return count;
}

int hitungPendengarLagu(List_playlist L, address_lagu PL){
    int count = 0;
    address_playlist P = first_playlist(L);
    while(P != NULL){
        if(kelagu(P) == PL){
            count++;
        }
        P = next_playlist(P);
    }
    return count;
}

void lagu_terpopuler(List_playlist LPL, List_lagu LL){
    if(first_playlist(LPL) == NULL){
        cout << "\nBelum ada data playlist" << endl;
        return;
    }

    cout << "\n========== 5 Lagu Terpopuler ==========" << endl;

    address_lagu PL = first_lagu(LL);
    address_lagu top_lagu[5];
    int top_count[5];

    for(int i = 0; i < 5; i++){
        top_lagu[i] = NULL;
        top_count[i] = 0;
    }

    while(PL != NULL){
        int count = hitungPendengarLagu(LPL, PL);

        // Masukkan ke top 5
        for(int i = 0; i < 5; i++){
            if(count > top_count[i]){
                // Geser data
                for(int j = 4; j > i; j--){
                    top_lagu[j] = top_lagu[j-1];
                    top_count[j] = top_count[j-1];
                }
                top_lagu[i] = PL;
                top_count[i] = count;
                break;
            }
        }
        PL = next_lagu(PL);
    }

    for(int i = 0; i < 5; i++){
        if(top_lagu[i] != NULL && top_count[i] > 0){
            cout << (i+1) << ". " << info_lagu(top_lagu[i]).judul
                 << " - " << info_lagu(top_lagu[i]).artis
                 << " (" << top_count[i] << " pendengar)" << endl;
        }
    }
}

void pengguna_teraktif(List_playlist LPL, List_pengguna LP){
    if(first_playlist(LPL) == NULL){
        cout << "\nBelum ada data playlist" << endl;
        return;
    }

    cout << "\n========== 5 Pengguna Teraktif ==========" << endl;

    address_pengguna PP = first_pengguna(LP);
    address_pengguna top_user[5];
    int top_count[5];

    for(int i = 0; i < 5; i++){
        top_user[i] = NULL;
        top_count[i] = 0;
    }

    while(PP != NULL){
        int count = hitungPlaylistPengguna(LPL, PP);

        // Masukkan ke top 5
        for(int i = 0; i < 5; i++){
            if(count > top_count[i]){
                // Geser data
                for(int j = 4; j > i; j--){
                    top_user[j] = top_user[j-1];
                    top_count[j] = top_count[j-1];
                }
                top_user[i] = PP;
                top_count[i] = count;
                break;
            }
        }
        PP = next_pengguna(PP);
    }

    for(int i = 0; i < 5; i++){
        if(top_user[i] != NULL && top_count[i] > 0){
            cout << (i+1) << ". " << info_pengguna(top_user[i]).username
                 << " (" << info_pengguna(top_user[i]).nama_lengkap << ") - "
                 << top_count[i] << " lagu" << endl;
        }
    }
}

void lagu_berdasarkan_genre(List_lagu LL){
    cout << "\n========== Lagu Berdasarkan Genre ==========" << endl;

    address_lagu P = first_lagu(LL);
    string genres[20];
    int genre_count[20];
    int total_genres = 0;

    // Hitung jumlah lagu per genre
    while(P != NULL){
        bool found = false;
        for(int i = 0; i < total_genres; i++){
            if(genres[i] == info_lagu(P).genre){
                genre_count[i]++;
                found = true;
                break;
            }
        }
        if(!found){
            genres[total_genres] = info_lagu(P).genre;
            genre_count[total_genres] = 1;
            total_genres++;
        }
        P = next_lagu(P);
    }

    // Tampilkan hasil
    for(int i = 0; i < total_genres; i++){
        cout << genres[i] << ": " << genre_count[i] << " lagu" << endl;
    }
}

void pengguna_premium_vs_free(List_pengguna LP, List_playlist LPL){
    cout << "\n========== Analisis Pengguna Premium vs Free ==========" << endl;

    int premium_users = 0, free_users = 0;
    int premium_playlist = 0, free_playlist = 0;

    address_pengguna PP = first_pengguna(LP);
    while(PP != NULL){
        if(info_pengguna(PP).tipe_akun == "Premium"){
            premium_users++;
            premium_playlist += hitungPlaylistPengguna(LPL, PP);
        }
        else{
            free_users++;
            free_playlist += hitungPlaylistPengguna(LPL, PP);
        }
        PP = next_pengguna(PP);
    }

    cout << "\nPengguna Premium: " << premium_users << " orang" << endl;
    cout << "Total Lagu di Playlist Premium: " << premium_playlist << endl;
    if(premium_users > 0)
        cout << "Rata-rata: " << (float)premium_playlist/premium_users << " lagu/pengguna" << endl;

    cout << "\nPengguna Free: " << free_users << " orang" << endl;
    cout << "Total Lagu di Playlist Free: " << free_playlist << endl;
    if(free_users > 0)
        cout << "Rata-rata: " << (float)free_playlist/free_users << " lagu/pengguna" << endl;
}

void statistik_playlist(List_playlist LPL, List_pengguna LP, List_lagu LL){
    system("cls");
    cout << "===========================================================" << endl;
    cout << "\t\tSTATISTIK APLIKASI MUSIK" << endl;
    cout << "===========================================================" << endl;

    int total_pengguna = hitungPengguna(LP);
    int total_lagu = hitungLagu(LL);
    int total_playlist = hitungPlaylist(LPL);

    cout << "\n--- DATA UMUM ---" << endl;
    cout << "Total Pengguna\t\t: " << total_pengguna << endl;
    cout << "Total Lagu\t\t: " << total_lagu << endl;
    cout << "Total Entri Playlist\t: " << total_playlist << endl;

    lagu_terpopuler(LPL, LL);
    pengguna_teraktif(LPL, LP);
    lagu_berdasarkan_genre(LL);
    pengguna_premium_vs_free(LP, LPL);

    cout << "\n===========================================================" << endl;
}

void data_playlist(List_playlist &L, List_pengguna LP, List_lagu LL){
    address_playlist P;
    address_pengguna PP;
    address_lagu PL;

    PP = findElm_pengguna(LP, "john_doe");
    PL = findElmByID_lagu(LL, 2);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "john_doe");
    PL = findElmByID_lagu(LL, 3);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "john_doe");
    PL = findElmByID_lagu(LL, 8);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "jane_smith");
    PL = findElmByID_lagu(LL, 5);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "jane_smith");
    PL = findElmByID_lagu(LL, 10);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "mike_wilson");
    PL = findElmByID_lagu(LL, 1);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "mike_wilson");
    PL = findElmByID_lagu(LL, 11);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "mike_wilson");
    PL = findElmByID_lagu(LL, 15);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "sarah_lee");
    PL = findElmByID_lagu(LL, 3);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "sarah_lee");
    PL = findElmByID_lagu(LL, 6);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "sarah_lee");
    PL = findElmByID_lagu(LL, 7);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "david_brown");
    PL = findElmByID_lagu(LL, 14);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "lisa_johnson");
    PL = findElmByID_lagu(LL, 7);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "lisa_johnson");
    PL = findElmByID_lagu(LL, 16);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "alex_turner");
    PL = findElmByID_lagu(LL, 12);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "alex_turner");
    PL = findElmByID_lagu(LL, 3);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "emma_watson");
    PL = findElmByID_lagu(LL, 9);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);

    PP = findElm_pengguna(LP, "emma_watson");
    PL = findElmByID_lagu(LL, 18);
    P = alokasi_playlist(PP, PL);
    insertLast_playlist(L, P);
}

void menu(List_pengguna &LP, List_lagu &LL, List_playlist &LPL) {
    int pil;
    pengguna pdicari;
    lagu ldicari;
    address_pengguna PP;
    address_lagu PL;
    address_playlist PPL;

    data_pengguna(LP);
    data_lagu(LL);
    data_playlist(LPL, LP, LL);

    do {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "\t     APLIKASI PEMUTAR MUSIK MODERN" << endl;
        cout << "\t\t   (Spotify Clone)" << endl;
        cout << "===========================================================" << endl;
        cout << " --- INPUT --- " << endl;
        cout << " 1.  Daftar Pengguna Baru" << endl;
        cout << " 2.  Tambah Lagu Baru" << endl;
        cout << " 3.  Tambah Lagu ke Playlist" << endl;
        cout << " --- EDIT --- " << endl;
        cout << " 4.  Edit Profil Pengguna" << endl;
        cout << " 5.  Edit Info Lagu" << endl;
        cout << " --- VIEW --- " << endl;
        cout << " 6.  Lihat Semua Pengguna" << endl;
        cout << " 7.  Lihat Semua Lagu" << endl;
        cout << " 8.  Lihat Semua Playlist" << endl;
        cout << " 9.  Statistik & Analytics" << endl;
        cout << " --- DELETE --- " << endl;
        cout << " 10. Hapus Akun Pengguna" << endl;
        cout << " 11. Hapus Lagu" << endl;
        cout << " 12. Hapus Lagu dari Playlist" << endl;
        cout << " --- SEARCHING --- " << endl;
        cout << " 13. Cari Playlist Pengguna" << endl;
        cout << " 14. Cari Pendengar Lagu" << endl;
        cout << " 15. Cari Lagu Berdasarkan Judul" << endl;
        cout << " 16. Cari Pengguna Berdasarkan Username" << endl;
        cout << endl;
        cout << " 0.  Exit " << endl;
        cout << "===========================================================" << endl;
        cout << " Masukkan Pilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("CLS");
            cout << "===========================================================" << endl;
            cout << "\t\tDaftar Pengguna Baru" << endl;
            cout << "===========================================================" << endl;
            PP = input_pengguna();
            insertLast_pengguna(LP, PP);
            cout << "\nPengguna Berhasil Terdaftar!" << endl;
            cout << endl;
            system("pause");
            break;

        case 2:
            system("CLS");
            cout << "===========================================================" << endl;
            cout << "\t\tTambah Lagu Baru" << endl;
            cout << "===========================================================" << endl;
            PL = input_lagu();
            insertLast_lagu(LL, PL);
            cout << "\nLagu Berhasil Ditambahkan!" << endl;
            cout << endl;
            system("pause");
            break;

        case 3:
            system("cls");
            input_playlist(LP, LL, LPL);
            cout << endl;
            system("pause");
            break;

        case 4:
            system("Cls");
            printInfo_pengguna(LP);
            cout << "Masukkan Username yang ingin diubah: ";
            cin.ignore();
            getline(cin, pdicari.username);
            PP = findElm_pengguna(LP, pdicari.username);
            if(PP != NULL){
                cout << "\nPengguna ditemukan!" << endl;
                system("PAUSE");
                system("CLS");
                cout << "=== Edit Profil ===" << endl;
                editInfo_pengguna(PP);
                cout << "\nProfil Berhasil Diubah!" << endl;
            }
            else{
                cout << "\nPengguna tidak ditemukan!" << endl;
            }
            system("PAUSE");
            break;

        case 5:
            system("cls");
            printInfo_lagu(LL);
            cout << "Masukkan Judul Lagu yang ingin diubah: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                cout << "\nLagu ditemukan!" << endl;
                system("PAUSE");
                system("cls");
                cout << "=== Edit Info Lagu ===" << endl;
                editInfo_lagu(PL);
                cout << "\nInfo Lagu Berhasil Diubah!" << endl;
            }
            else{
                cout << "\nLagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 6:
            system("CLS");
            printInfo_pengguna(LP);
            system("PAUSE");
            break;

        case 7:
            system("CLS");
            printInfo_lagu(LL);
            system("PAUSE");
            break;

        case 8:
            system("cls");
            print_playlist(LPL);
            system("PAUSE");
            break;

        case 9:
            statistik_playlist(LPL, LP, LL);
            system("PAUSE");
            break;

        case 10:
            system("Cls");
            printInfo_pengguna(LP);
            cout << "\nMasukkan Username yang ingin dihapus: ";
            cin.ignore();
            getline(cin, pdicari.username);
            PP = findElm_pengguna(LP, pdicari.username);
            if(PP != NULL){
                delete_pengguna_all(LPL, LP, PP);
                cout << "\nAkun Pengguna Berhasil Dihapus!" << endl;
                cout << "(Semua playlist pengguna juga telah dihapus)" << endl;
            }
            else{
                cout << "\nPengguna tidak ditemukan!" << endl;
            }
            system("PAUSE");
            break;

        case 11:
            system("cls");
            printInfo_lagu(LL);
            cout << "\nMasukkan Judul Lagu yang ingin dihapus: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                delete_lagu_all(LPL, LL, PL);
                cout << "\nLagu Berhasil Dihapus!" << endl;
                cout << "(Lagu juga telah dihapus dari semua playlist)" << endl;
            }
            else{
                cout << "\nLagu tidak ditemukan!" << endl;
            }
            system("PAUSE");
            break;

        case 12:
            system("cls");
            print_playlist(LPL);
            cout << "\nMasukkan Username: ";
            cin.ignore();
            getline(cin, pdicari.username);
            cout << "Masukkan Judul Lagu: ";
            getline(cin, ldicari.judul);
            PPL = find_playlist(LPL, pdicari.username, ldicari.judul);
            if(PPL != NULL){
                delete_playlist(LPL, PPL);
                dealokasi_playlist(PPL);
                cout << "\nLagu berhasil dihapus dari playlist!" << endl;
            }
            else{
                cout << "\nData tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 13:
            system("cls");
            printInfo_pengguna(LP);
            cout << "\nMasukkan Username yang dicari: ";
            cin.ignore();
            getline(cin, pdicari.username);
            PP = findElm_pengguna(LP, pdicari.username);
            if(PP != NULL){
                search_pengguna(LP, LPL, PP);
            }
            else{
                cout << "\nPengguna tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 14:
            system("cls");
            printInfo_lagu(LL);
            cout << "\nMasukkan Judul Lagu yang dicari: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                search_lagu(LL, LPL, PL);
            }
            else{
                cout << "\nLagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 15:
            system("cls");
            cout << "===========================================================" << endl;
            cout << "\t\tCari Lagu Berdasarkan Judul" << endl;
            cout << "===========================================================" << endl;
            cout << "Masukkan Judul Lagu: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                cout << "\n=== Lagu Ditemukan ===" << endl;
                showLagu(PL);
                cout << "\nJumlah Pendengar: " << hitungPendengarLagu(LPL, PL) << " pengguna" << endl;
            }
            else{
                cout << "\nLagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 16:
            system("cls");
            cout << "===========================================================" << endl;
            cout << "\t\tCari Pengguna Berdasarkan Username" << endl;
            cout << "===========================================================" << endl;
            cout << "Masukkan Username: ";
            cin.ignore();
            getline(cin, pdicari.username);
            PP = findElm_pengguna(LP, pdicari.username);
            if(PP != NULL){
                cout << "\n=== Pengguna Ditemukan ===" << endl;
                showPengguna(PP);
                cout << "\nJumlah Lagu di Playlist: " << hitungPlaylistPengguna(LPL, PP) << " lagu" << endl;
            }
            else{
                cout << "\nPengguna tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 0:
            cout << "\n===========================================================" << endl;
            cout << "  Terima Kasih Telah Menggunakan Aplikasi Pemutar Musik!" << endl;
            cout << "===========================================================" << endl;
            system("PAUSE");
            break;

        default:
            cout << "\nAngka yang anda masukkan salah!" << endl;
            cout << "Silakan masukkan angka 0-16" << endl;
            system("PAUSE");
            break;
        }
    } while (pil != 0);
}

// ============= MENU ADMIN =============
void menuAdmin(List_pengguna &LP, List_lagu &LL, List_playlist &LPL, string adminName){
    int pil;
    pengguna pdicari;
    lagu ldicari;
    address_pengguna PP;
    address_lagu PL;

    do {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "           ADMIN DASHBOARD - SPOTIFY CLONE" << endl;
        cout << "===========================================================" << endl;
        cout << " Logged in as: " << adminName << " (Administrator)" << endl;
        cout << "===========================================================" << endl;
        cout << " --- MANAJEMEN DATA --- " << endl;
        cout << " 1.  Lihat Semua Pengguna" << endl;
        cout << " 2.  Lihat Semua Lagu" << endl;
        cout << " 3.  Lihat Semua Playlist" << endl;
        cout << " 4.  Tambah Lagu Baru ke Database" << endl;
        cout << " 5.  Edit Info Lagu" << endl;
        cout << " 6.  Hapus Lagu dari Database" << endl;
        cout << " 7.  Hapus Akun Pengguna" << endl;
        cout << " --- ANALYTICS & REPORTS --- " << endl;
        cout << " 8.  Statistik & Analytics Lengkap" << endl;
        cout << " 9.  Cari Pengguna Berdasarkan Username" << endl;
        cout << " 10. Cari Lagu Berdasarkan Judul" << endl;
        cout << " 11. Lihat Pendengar Suatu Lagu" << endl;
        cout << " --- ACCOUNT --- " << endl;
        cout << " 0.  Logout" << endl;
        cout << "===========================================================" << endl;
        cout << " Masukkan Pilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("CLS");
            printInfo_pengguna(LP);
            cout << "\nTotal Pengguna: " << hitungPengguna(LP) << endl;
            system("PAUSE");
            break;

        case 2:
            system("CLS");
            printInfo_lagu(LL);
            cout << "\nTotal Lagu: " << hitungLagu(LL) << endl;
            system("PAUSE");
            break;

        case 3:
            system("cls");
            print_playlist(LPL);
            cout << "\nTotal Entri Playlist: " << hitungPlaylist(LPL) << endl;
            system("PAUSE");
            break;

        case 4:
            system("CLS");
            cout << "===========================================================" << endl;
            cout << "\t\tTambah Lagu Baru ke Database" << endl;
            cout << "===========================================================" << endl;
            PL = input_lagu();
            insertLast_lagu(LL, PL);
            cout << "\n✓ Lagu Berhasil Ditambahkan ke Database!" << endl;
            system("pause");
            break;

        case 5:
            system("cls");
            printInfo_lagu(LL);
            cout << "\nMasukkan Judul Lagu yang ingin diubah: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                cout << "\n✓ Lagu ditemukan!" << endl;
                system("PAUSE");
                system("cls");
                cout << "=== Edit Info Lagu ===" << endl;
                editInfo_lagu(PL);
                cout << "\n✓ Info Lagu Berhasil Diubah!" << endl;
            }
            else{
                cout << "\n✗ Lagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 6:
            system("cls");
            printInfo_lagu(LL);
            cout << "\nMasukkan Judul Lagu yang ingin dihapus: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                delete_lagu_all(LPL, LL, PL);
                cout << "\n✓ Lagu Berhasil Dihapus dari Database!" << endl;
                cout << "  (Lagu juga telah dihapus dari semua playlist)" << endl;
            }
            else{
                cout << "\n✗ Lagu tidak ditemukan!" << endl;
            }
            system("PAUSE");
            break;

        case 7:
            system("Cls");
            printInfo_pengguna(LP);
            cout << "\nMasukkan Username yang ingin dihapus: ";
            cin.ignore();
            getline(cin, pdicari.username);
            PP = findElm_pengguna(LP, pdicari.username);
            if(PP != NULL){
                delete_pengguna_all(LPL, LP, PP);
                cout << "\n✓ Akun Pengguna Berhasil Dihapus!" << endl;
                cout << "  (Semua playlist pengguna juga telah dihapus)" << endl;
            }
            else{
                cout << "\n✗ Pengguna tidak ditemukan!" << endl;
            }
            system("PAUSE");
            break;

        case 8:
            statistik_playlist(LPL, LP, LL);
            system("PAUSE");
            break;

        case 9:
            system("cls");
            cout << "===========================================================" << endl;
            cout << "\t\tCari Pengguna Berdasarkan Username" << endl;
            cout << "===========================================================" << endl;
            cout << "Masukkan Username: ";
            cin.ignore();
            getline(cin, pdicari.username);
            PP = findElm_pengguna(LP, pdicari.username);
            if(PP != NULL){
                cout << "\n=== Pengguna Ditemukan ===" << endl;
                showPengguna(PP);
                cout << "\nJumlah Lagu di Playlist: " << hitungPlaylistPengguna(LPL, PP) << " lagu" << endl;
            }
            else{
                cout << "\n✗ Pengguna tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 10:
            system("cls");
            cout << "===========================================================" << endl;
            cout << "\t\tCari Lagu Berdasarkan Judul" << endl;
            cout << "===========================================================" << endl;
            cout << "Masukkan Judul Lagu: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                cout << "\n=== Lagu Ditemukan ===" << endl;
                showLagu(PL);
                cout << "\nJumlah Pendengar: " << hitungPendengarLagu(LPL, PL) << " pengguna" << endl;
            }
            else{
                cout << "\n✗ Lagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 11:
            system("cls");
            printInfo_lagu(LL);
            cout << "\nMasukkan Judul Lagu yang dicari: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                search_lagu(LL, LPL, PL);
            }
            else{
                cout << "\n✗ Lagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 0:
            cout << "\n✓ Logout berhasil!" << endl;
            system("PAUSE");
            break;

        default:
            cout << "\n✗ Pilihan tidak valid!" << endl;
            system("PAUSE");
            break;
        }
    } while (pil != 0);
}

// ============= MENU USER =============
void menuUser(List_pengguna &LP, List_lagu &LL, List_playlist &LPL, string username){
    int pil;
    lagu ldicari;
    address_pengguna PP;
    address_lagu PL;
    address_playlist PPL;

    // Ambil data user yang login
    PP = findElm_pengguna(LP, username);

    do {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "           USER DASHBOARD - SPOTIFY CLONE" << endl;
        cout << "===========================================================" << endl;
        cout << " Logged in as: " << info_pengguna(PP).username << endl;
        cout << " Nama: " << info_pengguna(PP).nama_lengkap << endl;
        cout << " Tipe Akun: " << info_pengguna(PP).tipe_akun << endl;
        cout << " Total Lagu di Playlist: " << hitungPlaylistPengguna(LPL, PP) << " lagu" << endl;
        cout << "===========================================================" << endl;
        cout << " --- MY PLAYLIST --- " << endl;
        cout << " 1.  Lihat Playlist Saya" << endl;
        cout << " 2.  Tambah Lagu ke Playlist" << endl;
        cout << " 3.  Hapus Lagu dari Playlist" << endl;
        cout << " --- EXPLORE --- " << endl;
        cout << " 4.  Browse Semua Lagu" << endl;
        cout << " 5.  Cari Lagu Berdasarkan Judul" << endl;
        cout << " 6.  Lihat Lagu Terpopuler" << endl;
        cout << " --- MY ACCOUNT --- " << endl;
        cout << " 7.  Edit Profil Saya" << endl;
        cout << " 8.  Lihat Info Akun Lengkap" << endl;
        cout << " --- ACCOUNT --- " << endl;
        cout << " 0.  Logout" << endl;
        cout << "===========================================================" << endl;
        cout << " Masukkan Pilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("CLS");
            search_pengguna(LP, LPL, PP);
            system("PAUSE");
            break;

        case 2:
            system("cls");
            printInfo_lagu(LL);
            cout << "\nJudul Lagu yang ingin ditambahkan: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);

            if (PL != NULL){
                // Cek apakah lagu sudah ada di playlist
                address_playlist cek = find_playlist(LPL, username, ldicari.judul);
                if(cek != NULL){
                    cout << "\n✗ Lagu sudah ada dalam playlist Anda!" << endl;
                }
                else{
                    PPL = alokasi_playlist(PP, PL);
                    insertLast_playlist(LPL, PPL);
                    cout << "\n✓ Lagu Berhasil Ditambahkan ke Playlist!" << endl;
                }
            }
            else{
                cout << "\n✗ Lagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 3:
            system("cls");
            search_pengguna(LP, LPL, PP);
            cout << "\nMasukkan Judul Lagu yang ingin dihapus: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PPL = find_playlist(LPL, username, ldicari.judul);
            if(PPL != NULL){
                delete_playlist(LPL, PPL);
                dealokasi_playlist(PPL);
                cout << "\n✓ Lagu berhasil dihapus dari playlist!" << endl;
            }
            else{
                cout << "\n✗ Lagu tidak ada dalam playlist Anda!" << endl;
            }
            system("pause");
            break;

        case 4:
            system("CLS");
            printInfo_lagu(LL);
            cout << "\nTotal Lagu Tersedia: " << hitungLagu(LL) << endl;
            system("PAUSE");
            break;

        case 5:
            system("cls");
            cout << "===========================================================" << endl;
            cout << "\t\tCari Lagu Berdasarkan Judul" << endl;
            cout << "===========================================================" << endl;
            cout << "Masukkan Judul Lagu: ";
            cin.ignore();
            getline(cin, ldicari.judul);
            PL = findElm_lagu(LL, ldicari.judul);
            if(PL != NULL){
                cout << "\n=== Lagu Ditemukan ===" << endl;
                showLagu(PL);
                cout << "\nJumlah Pendengar: " << hitungPendengarLagu(LPL, PL) << " pengguna" << endl;

                // Cek apakah user sudah punya lagu ini
                address_playlist cek = find_playlist(LPL, username, ldicari.judul);
                if(cek != NULL){
                    cout << "✓ Lagu ini sudah ada di playlist Anda" << endl;
                }
                else{
                    cout << "✗ Lagu ini belum ada di playlist Anda" << endl;
                }
            }
            else{
                cout << "\n✗ Lagu tidak ditemukan!" << endl;
            }
            system("pause");
            break;

        case 6:
            system("cls");
            cout << "===========================================================" << endl;
            cout << "\t\tLAGU TERPOPULER" << endl;
            cout << "===========================================================" << endl;
            lagu_terpopuler(LPL, LL);
            cout << "\n===========================================================" << endl;
            system("PAUSE");
            break;

        case 7:
            system("CLS");
            cout << "===========================================================" << endl;
            cout << "\t\tEdit Profil Saya" << endl;
            cout << "===========================================================" << endl;
            editInfo_pengguna(PP);
            cout << "\n✓ Profil Berhasil Diubah!" << endl;
            system("PAUSE");
            break;

        case 8:
            {
                system("CLS");
                cout << "===========================================================" << endl;
                cout << "\t\tInfo Akun Lengkap" << endl;
                cout << "===========================================================" << endl;
                showPengguna(PP);
                cout << "\n--- Statistik Playlist ---" << endl;
                cout << "Total Lagu: " << hitungPlaylistPengguna(LPL, PP) << " lagu" << endl;

                // Hitung total durasi
                address_playlist P = first_playlist(LPL);
                int total_durasi = 0;
                while(P != NULL){
                    if(kepengguna(P) == PP){
                        total_durasi += info_lagu(kelagu(P)).durasi;
                    }
                    P = next_playlist(P);
                }
                cout << "Total Durasi: " << formatDurasi(total_durasi) << endl;
                cout << "\n===========================================================" << endl;
                system("PAUSE");
            }
            break;

        case 0:
            cout << "\n✓ Logout berhasil!" << endl;
            system("PAUSE");
            break;

        default:
            cout << "\n✗ Pilihan tidak valid!" << endl;
            system("PAUSE");
            break;
        }
    } while (pil != 0);
}
