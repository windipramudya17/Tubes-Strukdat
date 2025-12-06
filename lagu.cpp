#include "lagu.h"
#include <stdlib.h>

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

address_lagu findElm_lagu(List_lagu L, string judul){
    address_lagu P = first_lagu(L);
    while(P != NULL){
        if(info_lagu(P).judul == judul){
            return P;
        }
        P = next_lagu(P);
    }
    return NULL;
}

address_lagu findLaguByID(List_lagu L, int id){
    address_lagu P = first_lagu(L);
    while(P != NULL){
        if(info_lagu(P).id_lagu == id){
            return P;
        }
        P = next_lagu(P);
    }
    return NULL;
}

void deleteSearch_lagu(List_lagu &L, address_lagu &P){
    if(P == NULL) return;

    if(P == first_lagu(L) && P == last_lagu(L)){
        first_lagu(L) = NULL;
        last_lagu(L) = NULL;
    }
    else if(P == first_lagu(L)){
        first_lagu(L) = next_lagu(P);
        prev_lagu(first_lagu(L)) = NULL;
    }
    else if(P == last_lagu(L)){
        last_lagu(L) = prev_lagu(P);
        next_lagu(last_lagu(L)) = NULL;
    }
    else{
        next_lagu(prev_lagu(P)) = next_lagu(P);
        prev_lagu(next_lagu(P)) = prev_lagu(P);
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
        cout << "\nBelum ada lagu\n" << endl;
        return;
    }

    system("cls");
    cout << "==================================================================================" << endl;
    cout << "                            DAFTAR LAGU TERSEDIA" << endl;
    cout << "==================================================================================" << endl;
    cout << "ID  | Judul\t\t\t| Artis\t\t| Genre\t\t| Durasi | Tahun" << endl;
    cout << "==================================================================================" << endl;

    while(P != NULL){
        cout << info_lagu(P).id_lagu << "   | "
             << info_lagu(P).judul << "\t| "
             << info_lagu(P).artis << "\t| "
             << info_lagu(P).genre << "\t| "
             << formatDurasi(info_lagu(P).durasi) << " | "
             << info_lagu(P).tahun << endl;
        P = next_lagu(P);
    }
    cout << endl;
}

void editInfo_lagu(address_lagu &P){
    cout << "Judul: ";
    cin.ignore();
    getline(cin, info_lagu(P).judul);
    cout << "Artis: ";
    getline(cin, info_lagu(P).artis);
    cout << "Album: ";
    getline(cin, info_lagu(P).album);
    cout << "Genre: ";
    getline(cin, info_lagu(P).genre);
    cout << "Durasi (detik): ";
    cin >> info_lagu(P).durasi;
    cout << "Tahun: ";
    cin >> info_lagu(P).tahun;
}

address_lagu input_lagu(){
    lagu x;
    static int counter = 101;
    x.id_lagu = counter++;
    cin.ignore();
    cout << "ID: " << x.id_lagu << endl;
    cout << "Judul: ";
    getline(cin, x.judul);
    cout << "Artis: ";
    getline(cin, x.artis);
    cout << "Album: ";
    getline(cin, x.album);
    cout << "Genre: ";
    getline(cin, x.genre);
    cout << "Durasi (detik): ";
    cin >> x.durasi;
    cout << "Tahun: ";
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

    lg = {1, "Bohemian Rhapsody", "Queen", "A Night at Opera", "Rock", 354, 1975};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {2, "Shape of You", "Ed Sheeran", "Divide", "Pop", 233, 2017};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {3, "Blinding Lights", "The Weeknd", "After Hours", "Synthwave", 200, 2019};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {4, "Starboy", "The Weeknd", "Starboy", "R&B", 230, 2016};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {5, "Someone Like You", "Adele", "21", "Pop", 285, 2011};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {6, "Bad Guy", "Billie Eilish", "When We All Fall", "Pop", 194, 2019};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {7, "Levitating", "Dua Lipa", "Future Nostalgia", "Pop", 203, 2020};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {8, "Stay", "Justin Bieber", "Justice", "Pop", 141, 2021};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {9, "As It Was", "Harry Styles", "Harry's House", "Pop", 167, 2022};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {10, "Anti-Hero", "Taylor Swift", "Midnights", "Pop", 200, 2022};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {11, "Hotel California", "Eagles", "Hotel California", "Rock", 391, 1976};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {12, "Wonderwall", "Oasis", "Morning Glory", "Rock", 258, 1995};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {13, "Rolling in Deep", "Adele", "21", "Soul", 228, 2010};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {14, "Lose Yourself", "Eminem", "8 Mile", "Hip-Hop", 326, 2002};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {15, "Smells Like Teen", "Nirvana", "Nevermind", "Grunge", 301, 1991};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {16, "Perfect", "Ed Sheeran", "Divide", "Pop", 263, 2017};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {17, "Peaches", "Justin Bieber", "Justice", "Pop", 198, 2021};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {18, "Watermelon Sugar", "Harry Styles", "Fine Line", "Pop", 174, 2019};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {19, "Save Your Tears", "The Weeknd", "After Hours", "Synthwave", 215, 2020};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg = {20, "Happier Than Ever", "Billie Eilish", "Happier Than Ever", "Pop", 298, 2021};
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);
}
