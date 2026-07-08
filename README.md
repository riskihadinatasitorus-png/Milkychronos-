import hashlib
import time
import sys
import json
import urllib.request as urllib2

# =====================================================================
# CONFIGURASI MAINNET ASLI MILKYCHRONOS (MC)
# =====================================================================
IP_VPS_ANDA = "202.155.13.221"  
PORT_SERVER = "80"  # Jalur port 80 standar web, dijamin anti-blokir provider

ALAMAT_DOMPET_SAYA = "DOMPET_SAYA_MAINNET_ASLI"
# =====================================================================

URL_SERVER_MC = f"http://{IP_VPS_ANDA}:{PORT_SERVER}"

print("=" * 65)
print("⛏️  MEMULAI PERANGKAT TAMBANG MILKYCHRONOS (MC) ASLI DI PYDROID 3  ⛏️")
print(f"💰 Semua hadiah 50 MC akan dicetak ke: {ALAMAT_DOMPET_SAYA}")
print(f"🌐 Terhubung ke Server Jantung Utama VPS: {URL_SERVER_MC}")
print("=" * 65)

while True:
    try:
        req_job = urllib2.Request(f"{URL_SERVER_MC}/request-mining-job")
        respon = urllib2.urlopen(req_job, timeout=10)
        tugas = json.loads(respon.read().decode())
        
        target_blok = tugas["target_blok"]
        hash_sebelumnya = tugas["hash_sebelumnya"]
        kesulitan = tugas["tingkat_kesulitan"]
        
        print(f"🚀 Memulai pencarian kecocokan matematika untuk Blok #{target_blok}...")
        awalan_sah = "0" * kesulitan
        nonce = 0
        waktu_mulai = time.time()
        
        while True:
            teks_kombinasi = f"{target_blok}{hash_sebelumnya}{nonce}{ALAMAT_DOMPET_SAYA}"
            hash_hasil = hashlib.sha256(teks_kombinasi.encode()).hexdigest()
            
            if hash_hasil.startswith(awalan_sah):
                waktu_habis = round(time.time() - waktu_mulai, 2)
                print(f"\n🎉 SUKSES BESAR! Menemukan Nonce Valid: {nonce} dalam {waktu_habis} detik!")
                print(f"✨ Hasil Bukti Kerja Hash SHA-256: {hash_hasil}")
                
                data_kirim = json.dumps({"alamat_penambang": ALAMAT_DOMPET_SAYA, "nonce": nonce}).encode('utf-8')
                req_submit = urllib2.Request(
                    f"{URL_SERVER_MC}/submit-block", 
                    data=data_kirim, 
                    headers={'Content-Type': 'application/json'}
                )
                
                respon_kirim = urllib2.urlopen(req_submit, timeout=10)
                hasil_vps = json.loads(respon_kirim.read().decode())
                
                print(f"📨 Respon Server VPS Indonesia: {hasil_vps['pesan']}")
                print("=" * 65)
                time.sleep(3)
                break
                
            nonce += 1
            if nonce % 100000 == 0:
                print(f"⏳ Sedang menghitung... Mencoba {nonce:,} kombinasi angka nonce...", end="\r")
            
    except Exception as e:
        print(f"\n🚨 Gangguan jaringan: Gagal kontak dengan server VPS! Periksa IP atau pastikan server MC di VPS sudah menyala. ({e})")
        time.sleep(10)
