#include <ncurses/curses.h>
#include <windows.h>
#include <cstring>
#include <cctype>
#include <vector>
#include <string>

using namespace std;

// Struktur untuk menyimpan riwayat login
struct LoginRecord {
    string username;
    string password;
};

vector<LoginRecord> login_history; // Vektor untuk menyimpan riwayat login

// Fungsi untuk animasi teks
void animasi_teks(const char *teks, int y, int x) {
    int panjang = strlen(teks);
    for (int i = 0; i <= panjang; i++) {
        mvprintw(y, x, "%.*s", i, teks);
        refresh();
        Sleep(100);
    }
}

// Fungsi untuk menampilkan kotak loading
void tampilkan_kotak_loading() {
    animasi_teks("Memuat...", 10, 10);
    mvprintw(11, 10, "-------------------");
    mvprintw(12, 10, "|                 |");
    mvprintw(13, 10, "-------------------");
}

// Fungsi untuk menampilkan progress bar
void tampilkan_bilah_progres() {
    for (int f = 1; f < 17; f++) {
        mvprintw(12, 11 + f, ">>");
        refresh();
        Sleep(200);
    }
}

// Fungsi untuk inisialisasi layar ncurses
void inisialisasi_ncurses(int lebar, int tinggi) {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    resize_term(tinggi + 1, lebar);
}
