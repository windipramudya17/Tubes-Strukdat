#ifndef LAGU_H_INCLUDED
#define LAGU_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#define info_lagu(P) (P)->info_lagu
#define next_lagu(P) (P)->next_lagu
#define prev_lagu(P) (P)->prev_lagu
#define first_lagu(L) (L).first_lagu
#define last_lagu(L) (L).last_lagu

struct lagu{
    int id_lagu;
    string judul;
    string artis;
    string album;
    string genre;
    int durasi; // dalam detik
    int tahun;
};

typedef struct elmList_lagu *address_lagu;

struct elmList_lagu{
    lagu info_lagu;
    address_lagu next_lagu;
    address_lagu prev_lagu;
};

struct List_lagu{
    address_lagu first_lagu;
    address_lagu last_lagu;
};

// Primitive functions
void createList_lagu(List_lagu &L);
address_lagu alokasi_lagu(lagu x);
void dealokasi_lagu(address_lagu &P);
void insertFirst_lagu(List_lagu &L, address_lagu P);
void insertLast_lagu(List_lagu &L, address_lagu P);
address_lagu findElm_lagu(List_lagu L, string x);
address_lagu findElmByID_lagu(List_lagu L, int id);
void deleteFirst_lagu(List_lagu &L, address_lagu &P);
void deleteLast_lagu(List_lagu &L, address_lagu &P);
void deleteAfter_lagu(address_lagu Prec, address_lagu &P);
void deleteSearch_lagu(List_lagu &L, address_lagu &P);

// Display functions
void printInfo_lagu(List_lagu L);
void showLagu(address_lagu P);

// Helper functions
address_lagu input_lagu();
void editInfo_lagu(address_lagu &P);
void data_lagu(List_lagu &L);
string formatDurasi(int detik);
int hitungLagu(List_lagu L);

#endif // LAGU_H_INCLUDED
