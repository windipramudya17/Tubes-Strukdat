#ifndef LAGU_H_INCLUDED
#define LAGU_H_INCLUDED

#include <iostream>

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
    int durasi;
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

void createList_lagu(List_lagu &L);
address_lagu alokasi_lagu(lagu x);
void insertLast_lagu(List_lagu &L, address_lagu P);
address_lagu findElm_lagu(List_lagu L, string judul);
address_lagu findLaguByID(List_lagu L, int id);
void deleteSearch_lagu(List_lagu &L, address_lagu &P);
void printInfo_lagu(List_lagu L);
void showLagu(address_lagu P);
address_lagu input_lagu();
void editInfo_lagu(address_lagu &P);
void data_lagu(List_lagu &L);
string formatDurasi(int detik);
int hitungLagu(List_lagu L);

#endif
