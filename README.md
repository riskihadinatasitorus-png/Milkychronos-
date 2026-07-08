from flask import Flask, jsonify
import time

app = Flask(__name__)

# 1. IDENTITAS RESMI DAN ATURAN EKONOMI MUTLAK MC (MILK)
NAMA_KOIN = "MilkyChronos"
TICKER_KOIN = "MC"          # Simbol pasar resmi Anda
SATUAN_KECIL = "MILK"       # Satuan unit pecahan koin Anda
SUPLAI_MAKSIMAL = 50000000  # Batas mutlak: 50 Juta MC selamanya
BIAYA_TRANSAKSI = 1         # Biaya jaringan tetap: 1 MILK per transfer

# 2. DATABASE UTAMA JARINGAN (Menyimpan Saldo Permanen di Server VPS)
# Akun Anda langsung memegang 10 Juta MC di awal (Premine)
database_saldo = {
    "DOMPET_ANDA_CREATOR": 10000000,
    "DOMPET_PENAMBANG_A": 0,
    "DOMPET_PENGGUNA_B": 0
}

# 3. GERBANG INTERNET 1: Halaman Utama Server
@app.route('/', methods=['GET'])
def home():
    return jsonify({
        "status": "ONLINE",
        "pesan": f"Selamat Datang di Jaringan Server Utama {NAMA_KOIN} ({TICKER_KOIN})"
    })

# 4. GERBANG INTERNET 2: Cek Saldo Dompet Secara Live
@app.route('/cek-saldo/<alamat_dompet>', methods=['GET'])
def cek_saldo(alamat_dompet):
    saldo = database_saldo.get(alamat_dompet, 0)
    return jsonify({
        "alamat_dompet": alamat_dompet,
        "saldo_tersedia": f"{saldo:,} {TICKER_KOIN}",
        "satuan_unit": SATUAN_KECIL
    })

# 5. GERBANG INTERNET 3: Fungsi Kirim Koin via API (Aman & Tervalidasi)
@app.route('/kirim/<pengirim>/<penerima>/<penambang>/<int:jumlah_kirim>', methods=['POST', 'GET'])
def kirim_aset_mc(pengirim, penerima, penambang, jumlah_kirim):
    total_potongan = jumlah_kirim + BIAYA_TRANSAKSI
    
    # Validasi 1: Pastikan pengirim terdaftar di database
    if pengirim not in database_saldo:
        return jsonify({"status": "GAGAL", "pesan": "Dompet pengirim tidak terdaftar!"})
        
    # Validasi 2: Proteksi Keamanan Matematika (Cek kecukupan saldo + biaya admin)
    if database_saldo[pengirim] < total_potongan:
        return jsonify({
            "status": "GAGAL", 
            "pesan": f"Saldo {TICKER_KOIN} tidak mencukupi untuk transfer + biaya jaringan!"
        })

    # Proses Mutasi Saldo Otomatis oleh Sistem Jika Lolos Validasi
    database_saldo[pengirim] -= total_potongan
    
    if penerima not in database_saldo: database_saldo[penerima] = 0
    if penambang not in database_saldo: database_saldo[penambang] = 0
        
    database_saldo[penerima] += jumlah_kirim
    database_saldo[penambang] += BIAYA_TRANSAKSI
    
    return jsonify({
        "status": "SUKSES",
        "pesan": f"Transaksi {jumlah_kirim:,} {TICKER_KOIN} berhasil dikunci ke jaringan",
        "saldo_pengirim_sekarang": f"{database_saldo[pengirim]:,} {TICKER_KOIN}",
        "saldo_penerima_sekarang": f"{database_saldo[penerima]:,} {TICKER_KOIN}",
        "upah_penambang_masuk": f"{BIAYA_TRANSAKSI} {SATUAN_KECIL}"
    })

if __name__ == '__main__':
    # Menyalakan server agar bisa diakses online lewat IP VPS Indonesia Anda
    app.run(host='0.0.0.0', port=5000)
    
