void tampilkan_petunjuk_permainan() {
    clear();
    mvprintw(5, 10, "Selamat Datang di Permainan!");
    mvprintw(6, 10, "Gunakan tombol panah untuk bergerak.");
    mvprintw(7, 10, "Tekan spasi untuk menembak.");
    mvprintw(8, 10, "Tekan 'q' untuk keluar dari permainan.");
    mvprintw(10, 10, "Semoga berhasil dan selamat bermain!");
    refresh();
    Sleep(5000);
}

int main() {
    int lebar = 50, tinggi = 20;
    inisialisasi_ncurses(lebar, tinggi);

    for (int y = 0; y < 3; y++) {
        tampilkan_kotak_loading();
        tampilkan_bilah_progres();
        clear();
    }

    bool berhasil_login = false;
    while (!berhasil_login) {
        berhasil_login = login();
    }

    mvprintw(tinggi / 2, lebar / 2 - 10, "Login Berhasil!");
    refresh();
    Sleep(2000);

    tampilkan_riwayat_login();
    tampilkan_petunjuk_permainan();

    endwin();
    return 0;
}
