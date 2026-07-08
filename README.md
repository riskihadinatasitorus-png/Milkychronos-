import time

# 1. ATURAN MATEMATIKA UTAMA
SUPLAI_MAKSIMAL = 50000000  # 50 Juta Koin MILK

# 2. DATABASE UTAMA JARINGAN (Mencatat Saldo Semua Orang)
# Dompet Anda (pencipta) langsung diisi 10 Juta MILK lewat Premine
database_saldo = {
    "DOMPET_ANDA_CREATOR": 10000000,
    "DOMPET_PENAMBANG_A": 0,
    "DOMPET_PENAMBANG_B": 0
}

# 3. FUNGSI TRANSFER KOIN (AMAN & TERVALIDASI)
def kirim_koin_milky(dompet_pengirim, dompet_penerima, jumlah_kirim):
    print(f"💸 [PERMINTAAN TRANSFER]: {jumlah_kirim:,} MILK dari {dompet_pengirim} ke {dompet_penerima}")
    
    # Validasi 1: Cek apakah dompet pengirim terdaftar
    if dompet_pengirim not in database_saldo:
        print("❌ Eror: Dompet pengirim tidak valid!")
        return

    # Validasi 2: Cek apakah saldo pengirim cukup
    if database_saldo[dompet_pengirim] < jumlah_kirim:
        print(f"❌ Eror: Saldo tidak cukup! Saldo Anda hanya {database_saldo[dompet_pengirim]:,} MILK")
        return

    # Proses Pemotongan dan Penambahan Saldo (Logika Matematika Kripto)
    database_saldo[dompet_pengirim] -= jumlah_kirim
    
    # Jika dompet penerima baru (belum ada di database), daftarkan otomatis
    if dompet_penerima not in database_saldo:
        database_saldo[dompet_penerima] = 0
        
    database_saldo[dompet_penerima] += jumlah_kirim
    
    print("🟢 STATUS TRANSAKSI: 100% SUKSES & SEPAKAT (VALID)")
    print(f"   -> Saldo Pengirim Sekarang: {database_saldo[dompet_pengirim]:,} MILK")
    print(f"   -> Saldo Penerima Sekarang: {database_saldo[dompet_penerima]:,} MILK")
    print("-" * 55)

# === SIMULASI JALANNYA TRANSAKSI DI JARRINGAN ===

print(f"💰 Saldo Awal Anda: {database_saldo['DOMPET_ANDA_CREATOR']:,} MILK\n")
time.sleep(1)

# Uji Coba 1: Anda mengirim 500.000 MILK ke Penambang A (Berhasil)
kirim_koin_milky("DOMPET_ANDA_CREATOR", "DOMPET_PENAMBANG_A", 500000)

time.sleep(1)

# Uji Coba 2: Mencoba kirim 20 Juta MILK (Akan ditolak sistem karena saldo tidak cukup)
kirim_koin_milky("DOMPET_ANDA_CREATOR", "DOMPET_PENAMBANG_B", 20000000)
