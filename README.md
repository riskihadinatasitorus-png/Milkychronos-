from flask import Flask, jsonify
import threading
import time
import random

app = Flask(__name__)

# ==========================================
# KONFIGURASI UTAMA JARINGAN MC (MILK)
# ==========================================
NAMA_KOIN = "MilkyChronos"
TICKER = "MC"
SATUAN = "MILK"

SUPLAI_MAKSIMAL = 50000000  # Batas mutlak 50 juta koin
HADIAH_BLOK = 50           # Hadiah tetap 50 MC per blok kosmik
BIAYA_ADMIN = 1            # Biaya transfer tetap 1 MILK

# ==========================================
# LEDGER / DATABASE SALDO JARINGAN
# ==========================================
# Alokasi pencetakan awal (Premine) 10 Juta MC langsung masuk ke dompet saya
database_saldo = {
    "DOMPET_ANDA_CREATOR": 10000000,
    "DOMPET_PENAMBANG_A": 0,
    "DOMPET_PENAMBANG_B": 0,
    "DOMPET_PENGGUNA_C": 0
}

koin_beredar = 10000000  # Total koin beredar awal di bumi
blok_terakhir = 0
catatan_blok = []

# Daftar alamat komputer penambang dunia yang ikut kompetisi
list_penambang = ["DOMPET_PENAMBANG_A", "DOMPET_PENAMBANG_B", "DOMPET_USA_01", "DOMPET_ASIA_99"]

# ==========================================
# SYSTEM PENAMBANGAN OTOMATIS (BACKGROUND THREAD)
# ==========================================
def penambang_otomatis_loop():
    global koin_beredar, blok_terakhir
    
    while True:
        # Menunggu waktu jeda blok kosmik (setiap 60 detik)
        time.sleep(60)
        
        # Proteksi agar pencetakan koin tidak bablas melewati 50 juta
        if koin_beredar + HADIAH_BLOK > SUPLAI_MAKSIMAL:
            print("INFO: Suplai maksimal 50 juta MC sudah habis tercapai!")
            break
            
        blok_terakhir += 1
        
        # Mengacak pemenang kompetisi matematika secara adil
        pemenang_blok = random.choice(list_penambang)
        
        # Daftarkan dompet ke database jika belum ada
        if pemenang_blok not in database_saldo:
            database_saldo[pemenang_blok] = 0
            
        # Kirim hadiah koin baru dari sistem ke dompet pemenang
        database_saldo[pemenang_blok] += HADIAH_BLOK
        koin_beredar += HADIAH_BLOK
        
        info_blok = f"Blok #{blok_terakhir} sukses ditambang oleh {pemenang_blok}. Hadiah: {HADIAH_BLOK} MC."
        catatan_blok.append(info_blok)
        print(f"[LOG] {info_blok} Total Beredar: {koin_beredar:,} MC")

# ==========================================
# ENDPOINT API / GERBANG INTERNET JARINGAN
# ==========================================

# Halaman utama untuk memantau status blockchain MC
@app.route('/', methods=['GET'])
def index():
    return jsonify({
        "jaringan": NAMA_KOIN,
        "ticker_resmi": TICKER,
        "total_koin_beredar": f"{koin_beredar:,} / {SUPLAI_MAKSIMAL:,} {TICKER}",
        "ketinggian_blok": blok_terakhir,
        "riwayat_blok_terakhir": catatan_blok[-10:]
    })

# Jalur API untuk mengecek saldo dompet secara live
@app.route('/cek-saldo/<alamat_dompet>', methods=['GET'])
def cek_saldo_dompet(alamat_dompet):
    saldo = database_saldo.get(alamat_dompet, 0)
    return jsonify({
        "alamat_dompet": alamat_dompet,
        "saldo": f"{saldo:,} {TICKER}"
    })

# Jalur API aman untuk memproses transaksi kirim koin MC
@app.route('/kirim/<pengirim>/<penerima>/<penambang>/<int:jumlah_kirim>', methods=['POST', 'GET'])
def proses_transfer_mc(pengirim, penerima, penambang, jumlah_kirim):
    total_tagihan = jumlah_kirim + BIAYA_ADMIN
    
    if pengirim not in database_saldo:
        return jsonify({"status": "GAGAL", "pesan": "Alamat pengirim tidak terdaftar!"})
        
    if database_saldo[pengirim] < total_tagihan:
        return jsonify({"status": "GAGAL", "pesan": "Saldo Anda kurang untuk membayar koin + biaya admin!"})

    # Process mutasi angka saldo oleh sistem jaringan
    database_saldo[pengirim] -= total_tagihan
    
    if penerima not in database_saldo: database_saldo[penerima] = 0
    if penambang not in database_saldo: database_saldo[penambang] = 0
        
    database_saldo[penerima] += jumlah_kirim
    database_saldo[penambang] += BIAYA_ADMIN
    
    return jsonify({
        "status": "SUKSES",
        "pesan": f"Transaksi kirim {jumlah_kirim:,} {TICKER} berhasil disetujui.",
        "saldo_pengirim": f"{database_saldo[pengirim]:,} {TICKER}",
        "saldo_penerima": f"{database_saldo[penerima]:,} {TICKER}",
        "fee_penambang": f"{BIAYA_ADMIN} {SATUAN}"
    })

if __name__ == '__main__':
    # Aktifkan mesin pencetak koin otomatis di thread terpisah agar berjalan simultan
    threading.Thread(target=penambang_otomatis_loop, daemon=True).start()
    # Nyalakan server utama jaringan internet MC
    app.run(host='0.0.0.0', port=5000)
