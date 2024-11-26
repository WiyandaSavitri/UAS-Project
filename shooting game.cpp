#include <ncurses/curses.h>
#include <windows.h>
#include <cstring>
#include <cctype>
#include <vector>
#include <string>

using namespace std;

struct LoginRecord {
    string username;
    string password;
};

vector<LoginRecord> login_history; 

void animasi_teks(const char *teks, int y, int x) {
    int panjang = strlen(teks);
    for (int i = 0; i <= panjang; i++) {
        mvprintw(y, x, "%.*s", i, teks);
        refresh();
        Sleep(100);
    }
}


void tampilkan_kotak_loading() {
    animasi_teks("Memuat...", 10, 10);
    mvprintw(11, 10, "-------------------");
    mvprintw(12, 10, "|                 |");
    mvprintw(13, 10, "-------------------");
}

void tampilkan_bilah_progres() {
    for (int f = 1; f < 17; f++) {
        mvprintw(12, 11 + f, ">>");
        refresh();
        Sleep(200);
    }
}

void inisialisasi_ncurses(int lebar, int tinggi) {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    resize_term(tinggi + 1, lebar);
}

bool login() {
    char username[50], password[50];
    int kursor_x = 5, kursor_y = 5;

    mvprintw(kursor_y, kursor_x, "Nama Pengguna: ");
    refresh();
    int i = 0;
    while (true) {
        char ch = getch();
        if (ch == '\n' || ch == '\r') {
            username[i] = '\0';
            break;
        } else if (ch == 27) {
            username[i] = '\0';
            break;
        } else if (ch == 127 && i > 0) {
            i--;
            mvprintw(kursor_y, kursor_x + i, " ");
            refresh();
        } else if (isprint(ch) && i < 49) {
            username[i++] = ch;
            mvprintw(kursor_y, kursor_x + i - 1, "%c", ch);
            refresh();
        }
    }

    mvprintw(kursor_y + 1, kursor_x, "Kata Sandi: ");
    refresh();
    noecho();
    i = 0;
    while (true) {
        char ch = getch();
        if (ch == '\n' || ch == '\r') {
            password[i] = '\0';
            break;
        } else if (ch == 27) {
            password[i] = '\0';
            break;
        } else if (ch == 127 && i > 0) {
            i--;
            mvprintw(kursor_y + 1, kursor_x + i, " ");
            refresh();
        } else if (isprint(ch) && i < 49) {
            password[i++] = ch;
            mvprintw(kursor_y + 1, kursor_x + i - 1, "*");
            refresh();
        }
    }
    noecho();

    
    for (const auto &record : login_history) {
        if (record.username == username && record.password == password) {
            mvprintw(kursor_y + 2, kursor_x, "Selamat datang kembali, %s!", username);
            refresh();
            Sleep(2000);
            return true;
        }
    }

    login_history.push_back({username, password});
    mvprintw(kursor_y + 2, kursor_x, "Login berhasil! Selamat datang, %s!", username);
    refresh();
    Sleep(2000);
    return true;
}

void tampilkan_riwayat_login() {
    clear();
    mvprintw(2, 5, "Riwayat Login:");
    int y = 4;
    for (const auto &record : login_history) {
        mvprintw(y++, 5, "Nama Pengguna: %s | Kata Sandi: %s", record.username.c_str(), record.password.c_str());
    }
    mvprintw(y + 1, 5, "Tekan tombol apa saja untuk melanjutkan...");
    refresh();
    getch();
}
