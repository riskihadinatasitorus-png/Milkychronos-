import time

# 1. IDENTITAS RESMI KOIN KOSMIK
NAMA_KOIN = "MilkyChronos"
TICKER_KOIN = "MC"          # Simbol pasar resmi Anda
SATUAN_KECIL = "MILK"       # Satuan unit pecahan koin Anda
SUPLAI_MAKSIMAL = 50000000  # Batas mutlak: 50 Juta MC selamanya

# 2. DATABASE SALDO JARINGAN GLOBAL
database_saldo = {
    "DOMPET_ANDA_CREATOR": 10000000,  # Anda langsung memegang 10 Juta MC
    "DOMPET_PENAMBANG_A": 0,
    "DOMPET_PENGGUNA_B": 0
}

BIAYA_TRANSAKSI = 1  # Biaya jaringan tetap: 1 MILK per transfer

# 3. FUNGSI TRANSFER JARINGAN UTAMA
def kirim_aset_mc(pengirim, penerima, penambang, jumlah_kirim):
    total_potongan = jumlah_kirim + BIAYA_TRANSAKSI
    
    print(f"🪐 [{NAMA_KOIN.upper()} NETWORK INTERACTIVE] 🪐")
    print(f"💸 Kirim : {jumlah_kirim:,} {TICKER_KOIN} ({SATUAN_KECIL})")
    print(f"⛽ Biaya : {BIAYA_TRANSAKSI} {SATUAN_KECIL} -> Dialokasikan ke: {penambang}")
    
    # Proteksi Keamanan Matematika
    if database_saldo[pengirim] < total_potongan:
        print(f"❌ Transaksi Ditolak: Saldo {TICKER_KOIN} Anda tidak mencukupi untuk biaya admin!\n")
        return

    # Proses Mutasi Saldo Otomatis oleh Sistem
    database_saldo[pengirim] -= total_potongan
    database_saldo[penerima] += jumlah_kirim
    database_saldo[penambang] += BIAYA_TRANSAKSI
    
    print(f"🟢 STATUS: TRANSAKSI VALID DAN TERCATAT")
    print(f"   -> Saldo Akhir Pengirim : {database_saldo[pengirim]:,} {TICKER_KOIN}")
    print(f"   -> Saldo Akhir Penerima : {database_saldo[penerima]:,} {TICKER_KOIN}")
    print(f"   -> Bonus Upah Penambang : {database_saldo[penambang]:,} {SATUAN_KECIL}")
    print("=" * 65)

# === SIMULASI EKSEKUSI JARINGAN NYATA ===

print(f"🪙 Selamat Datang di Sistem Keuangan {NAMA_KOIN} ({TICKER_KOIN})")
print(f"💰 Saldo Dompet Utama Anda: {database_saldo['DOMPET_ANDA_CREATOR']:,} {TICKER_KOIN}\n")
time.sleep(1.2)

# Simulasi Anda mengirim koin MC pertama Anda
kirim_aset_mc(
    pengirim="DOMPET_ANDA_CREATOR", 
    penerima="DOMPET_PENGGUNA_B", 
    penambang="DOMPET_PENAMBANG_A", 
    jumlah_kirim=250000
)
