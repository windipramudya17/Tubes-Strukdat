#ifndef AUTH_H_INCLUDED
#define AUTH_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

// Struktur untuk menyimpan user yang sedang login
struct CurrentUser {
    string username;
    string role; // "admin" atau "user"
    bool isLoggedIn;
};

// Fungsi-fungsi authentication
void tampilkanHeader();
void tampilkanWelcome();
bool login(CurrentUser &current);
void logout(CurrentUser &current);
bool isAdmin(CurrentUser current);
bool isUser(CurrentUser current);

// Admin credentials (hardcoded untuk demo)
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

#endif // AUTH_H_INCLUDED
