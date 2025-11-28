#include "lagu.h"

string formatDurasi(int detik){
    int menit = detik / 60;
    int sisa = detik % 60;
    string hasil = to_string(menit) + ":";
    if(sisa < 10) hasil += "0";
    hasil += to_string(sisa);
    return hasil;
}

void createList_lagu(List_lagu &L){
    first_lagu(L) = NULL;
    last_lagu(L) = NULL;
}

address_lagu alokasi_lagu(lagu x){
    address_lagu P = new elmList_lagu;
    info_lagu(P) = x;
    next_lagu(P) = NULL;
    prev_lagu(P) = NULL;
    return P;
}

void dealokasi_lagu(address_lagu &P){
    delete P;
}

void insertFirst_lagu(List_lagu &L, address_lagu P){
    if(first_lagu(L) == NULL){
        first_lagu(L) = P;
        last_lagu(L) = P;
    }
    else{
        next_lagu(P) = first_lagu(L);
        prev_lagu(first_lagu(L)) = P;
        first_lagu(L) = P;
    }
}

void insertLast_lagu(List_lagu &L, address_lagu P){
    if(first_lagu(L) == NULL){
        first_lagu(L) = P;
        last_lagu(L) = P;
    }
    else{
        prev_lagu(P) = last_lagu(L);
        next_lagu(last_lagu(L)) = P;
        last_lagu(L) = P;
    }
}

address_lagu findElm_lagu(List_lagu L, string x){
    address_lagu P = first_lagu(L);
    while(P != NULL){
        if(info_lagu(P).judul == x){
            return P;
        }
        P = next_lagu(P);
    }
    return NULL;
}

address_lagu findElmByID_lagu(List_lagu L, int id){
    address_lagu P = first_lagu(L);
    while(P != NULL){
        if(info_lagu(P).id_lagu == id){
            return P;
        }
        P = next_lagu(P);
    }
    return NULL;
}

void deleteFirst_lagu(List_lagu &L, address_lagu &P){
    if(first_lagu(L) != NULL){
        P = first_lagu(L);
        if(first_lagu(L) == last_lagu(L)){
            first_lagu(L) = NULL;
            last_lagu(L) = NULL;
        }
        else{
            first_lagu(L) = next_lagu(P);
            prev_lagu(first_lagu(L)) = NULL;
            next_lagu(P) = NULL;
        }
    }
}

void deleteLast_lagu(List_lagu &L, address_lagu &P){
    if(first_lagu(L) != NULL){
        P = last_lagu(L);
        if(first_lagu(L) == last_lagu(L)){
            first_lagu(L) = NULL;
            last_lagu(L) = NULL;
        }
        else{
            last_lagu(L) = prev_lagu(P);
            next_lagu(last_lagu(L)) = NULL;
            prev_lagu(P) = NULL;
        }
    }
}

void deleteAfter_lagu(address_lagu Prec, address_lagu &P){
    P = next_lagu(Prec);
    if(P != NULL){
        next_lagu(Prec) = next_lagu(P);
        if(next_lagu(P) != NULL){
            prev_lagu(next_lagu(P)) = Prec;
        }
        next_lagu(P) = NULL;
        prev_lagu(P) = NULL;
    }
}

void deleteSearch_lagu(List_lagu &L, address_lagu &P){
    if(P != NULL){
        if(P == first_lagu(L)){
            deleteFirst_lagu(L, P);
        }
        else if(P == last_lagu(L)){
            deleteLast_lagu(L, P);
        }
        else{
            address_lagu Prec = prev_lagu(P);
            deleteAfter_lagu(Prec, P);
        }
    }
}

void showLagu(address_lagu P){
    cout << "ID: " << info_lagu(P).id_lagu << endl;
    cout << "Judul: " << info_lagu(P).judul << endl;
    cout << "Artis: " << info_lagu(P).artis << endl;
    cout << "Album: " << info_lagu(P).album << endl;
    cout << "Genre: " << info_lagu(P).genre << endl;
    cout << "Durasi: " << formatDurasi(info_lagu(P).durasi) << endl;
    cout << "Tahun: " << info_lagu(P).tahun << endl;
}

void printInfo_lagu(List_lagu L){
    address_lagu P = first_lagu(L);
    if(P == NULL){
        cout << "====================================================================================" << endl;
        cout << "\t\t\t\tDaftar Lagu Tersedia" << endl;
        cout << "====================================================================================" << endl;
        cout << endl;
        cout << "\t\t\t  Belum Ada Lagu yang Terdaftar\n" << endl;
    }
    else{
        system("cls");
        cout << "====================================================================================" << endl;
        cout << "\t\t\t\tDaftar Lagu Tersedia" << endl;
        cout << "====================================================================================" << endl;
        cout << "ID  | Judul Lagu\t\t| Artis\t\t| Album\t\t| Genre\t\t| Durasi | Tahun" << endl;
        cout << "====================================================================================" << endl;
        while(P != NULL){
            cout << info_lagu(P).id_lagu << "   | "
                 << info_lagu(P).judul << "\t| "
                 << info_lagu(P).artis << "\t| "
                 << info_lagu(P).album << "\t| "
                 << info_lagu(P).genre << "\t| "
                 << formatDurasi(info_lagu(P).durasi) << "  | "
                 << info_lagu(P).tahun;
            cout << endl;
            P = next_lagu(P);
        }
        cout << "\n";
    }
}

void editInfo_lagu(address_lagu &P){
    cout << "ID Lagu \t: " << info_lagu(P).id_lagu << " (tidak bisa diubah)" << endl;
    cout << "Judul Lagu \t: ";
    cin.ignore();
    getline(cin, info_lagu(P).judul);
    cout << "Artis \t\t: ";
    getline(cin, info_lagu(P).artis);
    cout << "Album \t\t: ";
    getline(cin, info_lagu(P).album);
    cout << "Genre \t\t: ";
    getline(cin, info_lagu(P).genre);
    cout << "Durasi (detik)\t: ";
    cin >> info_lagu(P).durasi;
    cout << "Tahun Rilis \t: ";
    cin >> info_lagu(P).tahun;
}

address_lagu input_lagu(){
    lagu x;
    static int counter = 101;
    x.id_lagu = counter++;
    cin.ignore();
    cout << "ID Lagu \t: " << x.id_lagu << " (Auto Generated)" << endl;
    cout << "Judul Lagu \t: ";
    getline(cin, x.judul);
    cout << "Artis \t\t: ";
    getline(cin, x.artis);
    cout << "Album \t\t: ";
    getline(cin, x.album);
    cout << "Genre \t\t: ";
    getline(cin, x.genre);
    cout << "Durasi (detik)\t: ";
    cin >> x.durasi;
    cout << "Tahun Rilis \t: ";
    cin >> x.tahun;

    return alokasi_lagu(x);
}

int hitungLagu(List_lagu L){
    int count = 0;
    address_lagu P = first_lagu(L);
    while(P != NULL){
        count++;
        P = next_lagu(P);
    }
    return count;
}

void data_lagu(List_lagu &L){
    lagu lg;
    address_lagu P;

    lg.id_lagu = 1;
    lg.judul = "Bohemian Rhapsody";
    lg.artis = "Queen";
    lg.album = "A Night at Opera";
    lg.genre = "Rock";
    lg.durasi = 354;
    lg.tahun = 1975;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 2;
    lg.judul = "Shape of You";
    lg.artis = "Ed Sheeran";
    lg.album = "Divide";
    lg.genre = "Pop";
    lg.durasi = 233;
    lg.tahun = 2017;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 3;
    lg.judul = "Blinding Lights";
    lg.artis = "The Weeknd";
    lg.album = "After Hours";
    lg.genre = "Synthwave";
    lg.durasi = 200;
    lg.tahun = 2019;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 4;
    lg.judul = "Starboy";
    lg.artis = "The Weeknd";
    lg.album = "Starboy";
    lg.genre = "R&B";
    lg.durasi = 230;
    lg.tahun = 2016;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 5;
    lg.judul = "Someone Like You";
    lg.artis = "Adele";
    lg.album = "21";
    lg.genre = "Pop";
    lg.durasi = 285;
    lg.tahun = 2011;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 6;
    lg.judul = "Bad Guy";
    lg.artis = "Billie Eilish";
    lg.album = "When We All Fall";
    lg.genre = "Pop";
    lg.durasi = 194;
    lg.tahun = 2019;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 7;
    lg.judul = "Levitating";
    lg.artis = "Dua Lipa";
    lg.album = "Future Nostalgia";
    lg.genre = "Pop";
    lg.durasi = 203;
    lg.tahun = 2020;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 8;
    lg.judul = "Stay";
    lg.artis = "Justin Bieber";
    lg.album = "Justice";
    lg.genre = "Pop";
    lg.durasi = 141;
    lg.tahun = 2021;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 9;
    lg.judul = "As It Was";
    lg.artis = "Harry Styles";
    lg.album = "Harry's House";
    lg.genre = "Pop";
    lg.durasi = 167;
    lg.tahun = 2022;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 10;
    lg.judul = "Anti-Hero";
    lg.artis = "Taylor Swift";
    lg.album = "Midnights";
    lg.genre = "Pop";
    lg.durasi = 200;
    lg.tahun = 2022;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 11;
    lg.judul = "Hotel California";
    lg.artis = "Eagles";
    lg.album = "Hotel California";
    lg.genre = "Rock";
    lg.durasi = 391;
    lg.tahun = 1976;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 12;
    lg.judul = "Wonderwall";
    lg.artis = "Oasis";
    lg.album = "Morning Glory";
    lg.genre = "Rock";
    lg.durasi = 258;
    lg.tahun = 1995;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 13;
    lg.judul = "Rolling in Deep";
    lg.artis = "Adele";
    lg.album = "21";
    lg.genre = "Soul";
    lg.durasi = 228;
    lg.tahun = 2010;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 14;
    lg.judul = "Lose Yourself";
    lg.artis = "Eminem";
    lg.album = "8 Mile";
    lg.genre = "Hip-Hop";
    lg.durasi = 326;
    lg.tahun = 2002;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 15;
    lg.judul = "Smells Like Teen";
    lg.artis = "Nirvana";
    lg.album = "Nevermind";
    lg.genre = "Grunge";
    lg.durasi = 301;
    lg.tahun = 1991;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 16;
    lg.judul = "Perfect";
    lg.artis = "Ed Sheeran";
    lg.album = "Divide";
    lg.genre = "Pop";
    lg.durasi = 263;
    lg.tahun = 2017;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 17;
    lg.judul = "Peaches";
    lg.artis = "Justin Bieber";
    lg.album = "Justice";
    lg.genre = "Pop";
    lg.durasi = 198;
    lg.tahun = 2021;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 18;
    lg.judul = "Watermelon Sugar";
    lg.artis = "Harry Styles";
    lg.album = "Fine Line";
    lg.genre = "Pop";
    lg.durasi = 174;
    lg.tahun = 2019;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 19;
    lg.judul = "Save Your Tears";
    lg.artis = "The Weeknd";
    lg.album = "After Hours";
    lg.genre = "Synthwave";
    lg.durasi = 215;
    lg.tahun = 2020;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 20;
    lg.judul = "Happier Than Ever";
    lg.artis = "Billie Eilish";
    lg.album = "Happier Than Ever";
    lg.genre = "Pop";
    lg.durasi = 298;
    lg.tahun = 2021;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);
}
