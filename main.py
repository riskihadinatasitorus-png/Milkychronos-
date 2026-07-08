import time

# 1. ATURAN MATEMATIKA UTAMA
SUPLAI_MAKSIMAL = 50000000  # 50 Juta Koin MILK
HADIAH_PENAMBANG = 50       # Penambang dapat 50 MILK per blok

# 2. STATUS AWAL (PREMINE 10 JUTA COIN UNTUK ANDA)
DOMPET_ANDA = "MILKY_CHRONOS_CREATOR_ADDRESS_001"
saldo_anda = 10000000
koin_beredar = saldo_anda  # Memulai jaringan langsung dengan 10 juta beredar

# 3. FUNGSI UNTUK PENAMBANG DUNIA
def penambang_berhasil_pecahkan_blok(alamat_penambang, nomor_blok):
    global koin_beredar
    
    print(f"🪐 [MILKYCHRONOS NETWORK - BLOK #{nomor_blok}] 🪐")
    print(f"⛏️ Komputer {alamat_penambang} berhasil menambang!")
    
    # Memastikan total koin tidak melewati batas 50 juta
    if koin_beredar + HADIAH_PENAMBANG <= SUPLAI_MAKSIMAL:
        koin_beredar += HADIAH_PENAMBANG
        print(f"🎁 Hadiah {HADIAH_PENAMBANG} MILK dikirim ke penambang.")
        print(f"📊 Koin beredar di bumi: {koin_beredar:,} / {SUPLAI_MAKSIMAL:,} MILK")
    else:
        print("❌ Suplai 50 Juta Habis! Jaringan tidak lagi mencetak koin baru.")
    print("-" * 50)

# === SIMULASI JALANNYA JARINGAN ===

# Cek saldo awal Anda dulu
print(f"🔑 Dompet Pencipta: {DOMPET_ANDA}")
print(f"💰 Saldo Awal Anda: {saldo_anda:,} MILK\n")

# Simulasi jika ada komputer orang lain (Penambang_A) mulai bekerja
time.sleep(1)
penambang_berhasil_pecahkan_blok("DOMPET_PENAMBANG_A", nomor_blok=1)

time.sleep(1)
penambang_berhasil_pecahkan_blok("DOMPET_PENAMBANG_B", nomor_blok=2)
  
