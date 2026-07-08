#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// 1. ATURAN EKONOMI UTAMA MC (MILK)
const long long SUPLAI_MAKSIMAL = 50000000; // 50 Juta Koin
const int BIAYA_TRANSAKSI = 1;               // 1 MILK

// 2. DATABASE SALDO JARINGAN
map<string, long long> database_saldo;

// Fungsi untuk melakukan transfer koin MC
void kirim_aset_mc(string pengirim, string penerima, string penambang, long long jumlah_kirim) {
    long long total_potongan = jumlah_kirim + BIAYA_TRANSAKSI;
    
    cout << "🪐 [MILKYCHRONOS C++ NETWORK] 🪐" << endl;
    cout << "💸 Kirim : " << jumlah_kirim << " MC" << endl;
    cout << "⛽ Biaya : " << BIAYA_TRANSAKSI << " MILK -> Dialokasikan ke: " << penambang << endl;

    // Proteksi Keamanan Matematika C++
    if (database_saldo[pengirim] < total_potongan) {
        cout << "❌ Transaksi Ditolak: Saldo MC tidak mencukupi!\n" << endl;
        return;
    }

    // Eksekusi Perpindahan Angka di Memori
    database_saldo[pengirim] -= total_potongan;
    database_saldo[penerima] += jumlah_kirim;
    database_saldo[penambang] += BIAYA_TRANSAKSI;

    cout << "🟢 STATUS: TRANSAKSI VALID DAN AMAN (C++)" << endl;
    cout << "   -> Saldo Akhir Pengirim : " << database_saldo[pengirim] << " MC" << endl;
    cout << "   -> Saldo Akhir Penerima : " << database_saldo[penerima] << " MC" << endl;
    cout << "=========================================================" << endl;
}

int main() {
    // 3. PREMINE: Mengisi Saldo Awal Anda 10 Juta Koin MC
    database_saldo["DOMPET_ANDA_CREATOR"] = 10000000;

    cout << "🪙 Selamat Datang di Sistem Inti MilkyChronos (MC)" << endl;
    cout << "💰 Saldo Dompet Utama Anda: " << database_saldo["DOMPET_ANDA_CREATOR"] << " MC\n" << endl;

    // Simulasi transfer pertama di dalam mesin C++
    kirim_aset_mc("DOMPET_ANDA_CREATOR", "DOMPET_PENGGUNA_B", "DOMPET_PENAMBANG_A", 250000);

    return 0;
}
