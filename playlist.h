#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

#include "lagu.h"
#include "pengguna.h"
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

#define next_playlist(P) (P)->next_playlist
#define first_playlist(L) (L).first_playlist
#define kelagu(P) (P)->kelagu
#define kepengguna(P) (P)->kepengguna

typedef struct elmList_playlist *address_playlist;

struct elmList_playlist{
    address_playlist next_playlist;
    address_lagu kelagu;
    address_pengguna kepengguna;
};

struct List_playlist{
    address_playlist first_playlist;
};

// Primitive functions
void createList_playlist(List_playlist &L);
address_playlist alokasi_playlist(address_pengguna PP, address_lagu PL);
void dealokasi_playlist(address_playlist &P);
void insertFirst_playlist(List_playlist &L, address_playlist P);
void insertLast_playlist(List_playlist &L, address_playlist P);
address_playlist find_playlist(List_playlist L, string username, string judul);
void deleteFirst_playlist(List_playlist &L, address_playlist &P);
void deleteLast_playlist(List_playlist &L, address_playlist &P);
void deleteAfter_playlist(address_playlist Prec, address_playlist &P);
void deleteSearch_playlist(List_playlist &L, address_playlist &P);

// Display functions
void print_playlist(List_playlist L);
void print_playlist_pengguna(List_playlist L, address_pengguna PP);
void print_pendengar_lagu(List_playlist L, address_lagu PL);

// Operations
void input_playlist(List_pengguna LP, List_lagu LL, List_playlist &LPL);
void delete_pengguna_all(List_playlist &LPL, List_pengguna &LP, address_pengguna &PP);
void delete_lagu_all(List_playlist &LPL, List_lagu &LL, address_lagu &PL);
void delete_playlist(List_playlist &L, address_playlist &P);

// Search & Statistics
void search_pengguna(List_pengguna LP, List_playlist LPL, address_pengguna PP);
void search_lagu(List_lagu LL, List_playlist LPL, address_lagu PL);
void statistik_playlist(List_playlist LPL, List_pengguna LP, List_lagu LL);
void lagu_terpopuler(List_playlist LPL, List_lagu LL);
void pengguna_teraktif(List_playlist LPL, List_pengguna LP);
void lagu_berdasarkan_genre(List_lagu LL);
void pengguna_premium_vs_free(List_pengguna LP, List_playlist LPL);
int hitungPlaylist(List_playlist L);
int hitungPlaylistPengguna(List_playlist L, address_pengguna PP);
int hitungPendengarLagu(List_playlist L, address_lagu PL);

// Data & Menu
void data_playlist(List_playlist &L, List_pengguna LP, List_lagu LL);
void menu(List_pengguna &LP, List_lagu &LL, List_playlist &LPL);
void menuAdmin(List_pengguna &LP, List_lagu &LL, List_playlist &LPL, string adminName);
void menuUser(List_pengguna &LP, List_lagu &LL, List_playlist &LPL, string username);

#endif // PLAYLIST_H_INCLUDED
