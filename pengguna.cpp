#include "pengguna.h"

void createList_pengguna(List_pengguna &L){
    first_pengguna(L) = NULL;
}

address_pengguna alokasi_pengguna(pengguna x){
    address_pengguna P = new elmList_pengguna;
    info_pengguna(P) = x;
    next_pengguna(P) = NULL;
    return P;
}

void dealokasi_pengguna(address_pengguna &P){
    delete P;
}

void insertFirst_pengguna(List_pengguna &L, address_pengguna P){
    if(first_pengguna(L) == NULL){
        first_pengguna(L) = P;
    }
    else{
        next_pengguna(P) = first_pengguna(L);
        first_pengguna(L) = P;
    }
}

void insertLast_pengguna(List_pengguna &L, address_pengguna P){
    if(first_pengguna(L) == NULL){
        first_pengguna(L) = P;
    }
    else{
        address_pengguna Q = first_pengguna(L);
        while(next_pengguna(Q) != NULL){
            Q = next_pengguna(Q);
        }
        next_pengguna(Q) = P;
    }
}

address_pengguna findElm_pengguna(List_pengguna L, string x){
    address_pengguna P = first_pengguna(L);
    while(P != NULL){
        if(info_pengguna(P).username == x){
            return P;
        }
        P = next_pengguna(P);
    }
    return NULL;
}

void deleteFirst_pengguna(List_pengguna &L, address_pengguna &P){
    if(first_pengguna(L) != NULL){
        P = first_pengguna(L);
        first_pengguna(L) = next_pengguna(P);
        next_pengguna(P) = NULL;
    }
}

void deleteLast_pengguna(List_pengguna &L, address_pengguna &P){
    if(first_pengguna(L) != NULL){
        if(next_pengguna(first_pengguna(L)) == NULL){
            P = first_pengguna(L);
            first_pengguna(L) = NULL;
        }
        else{
            address_pengguna Q = first_pengguna(L);
            while(next_pengguna(next_pengguna(Q)) != NULL){
                Q = next_pengguna(Q);
            }
            P = next_pengguna(Q);
            next_pengguna(Q) = NULL;
        }
    }
}

void deleteAfter_pengguna(address_pengguna Prec, address_pengguna &P){
    if(Prec != NULL){
        P = next_pengguna(Prec);
        if(P != NULL){
            next_pengguna(Prec) = next_pengguna(P);
            next_pengguna(P) = NULL;
        }
    }
}

void deleteSearch_pengguna(List_pengguna &L, address_pengguna &P){
    if(P != NULL){
        if(P == first_pengguna(L)){
            deleteFirst_pengguna(L, P);
        }
        else{
            address_pengguna Prec = first_pengguna(L);
            while(next_pengguna(Prec) != P && Prec != NULL){
                Prec = next_pengguna(Prec);
            }
            if(Prec != NULL){
                if(next_pengguna(P) == NULL){
                    deleteLast_pengguna(L, P);
                }
                else{
                    deleteAfter_pengguna(Prec, P);
                }
            }
        }
    }
}

void showPengguna(address_pengguna P){
    cout << "Username: " << info_pengguna(P).username << endl;
    cout << "Nama Lengkap: " << info_pengguna(P).nama_lengkap << endl;
    cout << "Email: " << info_pengguna(P).email << endl;
    cout << "Negara: " << info_pengguna(P).negara << endl;
    cout << "Umur: " << info_pengguna(P).umur << " tahun" << endl;
    cout << "Tipe Akun: " << info_pengguna(P).tipe_akun << endl;
}

void printInfo_pengguna(List_pengguna L){
    address_pengguna P = first_pengguna(L);
    if(P == NULL){
        cout << "=====================================================================================" << endl;
        cout << "\t\t\t\tDaftar Pengguna" << endl;
        cout << "=====================================================================================" << endl;
        cout << endl;
        cout << "\t\t\t  Belum Ada Pengguna yang Terdaftar\n" << endl;
    }
    else{
        cout << "=====================================================================================" << endl;
        cout << "\t\t\t\tDaftar Pengguna" << endl;
        cout << "=====================================================================================" << endl;
        cout << "Username\t| Nama Lengkap\t| Email\t\t\t| Negara\t| Umur\t| Tipe Akun" << endl;
        cout << "=====================================================================================" << endl;
        while(P != NULL){
            cout << info_pengguna(P).username << "\t| "
                 << info_pengguna(P).nama_lengkap << "\t| "
                 << info_pengguna(P).email << "\t| "
                 << info_pengguna(P).negara << "\t| "
                 << info_pengguna(P).umur << "\t| "
                 << info_pengguna(P).tipe_akun;
            cout << endl;
            P = next_pengguna(P);
        }
        cout << "\n";
    }
}

void editInfo_pengguna(address_pengguna &P){
    cout << "Username \t: " << info_pengguna(P).username << " (tidak bisa diubah)" << endl;
    cout << "Nama Lengkap \t: ";
    cin.ignore();
    getline(cin, info_pengguna(P).nama_lengkap);
    cout << "Email \t\t: ";
    getline(cin, info_pengguna(P).email);
    cout << "Negara \t\t: ";
    getline(cin, info_pengguna(P).negara);
    cout << "Umur \t\t: ";
    cin >> info_pengguna(P).umur;
    cin.ignore();
    cout << "Tipe Akun \t: ";
    getline(cin, info_pengguna(P).tipe_akun);
}

address_pengguna input_pengguna(){
    pengguna x;
    cin.ignore();
    cout << "Username \t: ";
    getline(cin, x.username);
    cout << "Nama Lengkap \t: ";
    getline(cin, x.nama_lengkap);
    cout << "Email \t\t: ";
    getline(cin, x.email);
    cout << "Negara \t\t: ";
    getline(cin, x.negara);
    cout << "Umur \t\t: ";
    cin >> x.umur;
    cin.ignore();
    cout << "Tipe Akun \t: ";
    getline(cin, x.tipe_akun);

    return alokasi_pengguna(x);
}

int hitungPengguna(List_pengguna L){
    int count = 0;
    address_pengguna P = first_pengguna(L);
    while(P != NULL){
        count++;
        P = next_pengguna(P);
    }
    return count;
}

void data_pengguna(List_pengguna &L){
    pengguna pg;
    address_pengguna P;

    pg.username = "john_doe";
    pg.nama_lengkap = "John Doe";
    pg.email = "john@email.com";
    pg.negara = "USA";
    pg.umur = 25;
    pg.tipe_akun = "Premium";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "jane_smith";
    pg.nama_lengkap = "Jane Smith";
    pg.email = "jane@email.com";
    pg.negara = "UK";
    pg.umur = 28;
    pg.tipe_akun = "Free";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "mike_wilson";
    pg.nama_lengkap = "Mike Wilson";
    pg.email = "mike@email.com";
    pg.negara = "Canada";
    pg.umur = 22;
    pg.tipe_akun = "Premium";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "sarah_lee";
    pg.nama_lengkap = "Sarah Lee";
    pg.email = "sarah@email.com";
    pg.negara = "Australia";
    pg.umur = 30;
    pg.tipe_akun = "Premium";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "david_brown";
    pg.nama_lengkap = "David Brown";
    pg.email = "david@email.com";
    pg.negara = "Indonesia";
    pg.umur = 24;
    pg.tipe_akun = "Free";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "lisa_johnson";
    pg.nama_lengkap = "Lisa Johnson";
    pg.email = "lisa@email.com";
    pg.negara = "Germany";
    pg.umur = 27;
    pg.tipe_akun = "Premium";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "alex_turner";
    pg.nama_lengkap = "Alex Turner";
    pg.email = "alex@email.com";
    pg.negara = "UK";
    pg.umur = 29;
    pg.tipe_akun = "Premium";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);

    pg.username = "emma_watson";
    pg.nama_lengkap = "Emma Watson";
    pg.email = "emma@email.com";
    pg.negara = "USA";
    pg.umur = 26;
    pg.tipe_akun = "Free";
    P = alokasi_pengguna(pg);
    insertLast_pengguna(L, P);
}
