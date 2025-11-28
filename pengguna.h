#ifndef PENGGUNA_H_INCLUDED
#define PENGGUNA_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

#define info_pengguna(P) (P)->info_pengguna
#define next_pengguna(P) (P)->next_pengguna
#define first_pengguna(L) (L).first_pengguna

struct pengguna{
    string username;
    string nama_lengkap;
    string email;
    string negara;
    string tipe_akun; // Free/Premium
    int umur;
};

typedef struct elmList_pengguna *address_pengguna;

struct elmList_pengguna{
    pengguna info_pengguna;
    address_pengguna next_pengguna;
};

struct List_pengguna{
    address_pengguna first_pengguna;
};

// Primitive functions
void createList_pengguna(List_pengguna &L);
address_pengguna alokasi_pengguna(pengguna x);
void dealokasi_pengguna(address_pengguna &P);
void insertFirst_pengguna(List_pengguna &L, address_pengguna P);
void insertLast_pengguna(List_pengguna &L, address_pengguna P);
address_pengguna findElm_pengguna(List_pengguna L, string x);
void deleteFirst_pengguna(List_pengguna &L, address_pengguna &P);
void deleteLast_pengguna(List_pengguna &L, address_pengguna &P);
void deleteAfter_pengguna(address_pengguna Prec, address_pengguna &P);
void deleteSearch_pengguna(List_pengguna &L, address_pengguna &P);

// Display functions
void printInfo_pengguna(List_pengguna L);
void showPengguna(address_pengguna P);

// Helper functions
void editInfo_pengguna(address_pengguna &P);
address_pengguna input_pengguna();
void data_pengguna(List_pengguna &L);
int hitungPengguna(List_pengguna L);

#endif // PENGGUNA_H_INCLUDED
