from Jaket import Jaket


#  MAKRO WARNA PADA TERMINAL
RESET = "\033[0m"
RED = "\033[31m"
GREEN = "\033[32m"
CYAN = "\033[36m"
YELLOW = "\033[33m"
BOLD = "\033[1m"

# Jumlah field pada perintah INSERT Jaket
JUMLAH_FIELD_JAKET = 9

# Indeks field yang ditulis polos tanpa tanda kutip (angka dan boolean)
FIELD_TANPA_KUTIP = [2, 7, 8]

# Nama field sesuai urutan pada perintah INSERT
NAMA_FIELD = [
    "id_produk", "merk", "harga", "ukuran", "bahan",
    "warna", "jenis_penutup", "kupluk", "jumlah_saku"
]

# Jumlah kolom pada tabel Jaket
JUMLAH_KOLOM = 9

# Judul kolom tabel Jaket
JUDUL_KOLOM = [
    "ID Produk", "Merk", "Harga", "Ukuran", "Bahan",
    "Warna", "Jenis Penutup", "Kupluk", "Saku"
]

# Lebar tiap kolom, dihitung ulang setiap tabel dicetak
col = [0] * JUMLAH_KOLOM

# Status hasil pembacaan perintah
PERINTAH_LENGKAP = 0
INPUT_KOSONG = 1
TANPA_TITIK_KOMA = 2
BARIS_KOSONG = 3


def print_error(pesan):
    # Menampilkan pesan kesalahan dengan warna merah
    print(RED + "[ERROR] : " + pesan + RESET)


def print_sukses(pesan):
    # Menampilkan pesan berhasil dengan warna hijau
    print(GREEN + "[SUCSESS] : " + pesan + RESET)


def intro():
    # Menampilkan judul program, format INSERT, dan daftar perintah
    print("=" * 54)
    print("        WELCOME TO PRODUK MANAGEMENT")
    print("=" * 54)
    print("DAFTAR PERINTAH :")
    print("  INSERT ... ;   -> Menambah satu produk Jaket")
    print("  SHOW ;         -> Menampilkan semua Jaket yang tersimpan")
    print("  HELP ;         -> Menampilkan daftar perintah ini")
    print("  EXIT ;         -> Keluar dari produt management")
    print()
    print("HOW TO INSERT JAKET :")
    print('  INSERT "id_produk" "merk" harga "ukuran" "bahan" "warna" '
          '"jenis_penutup" kupluk jumlah_saku;')
    print()
    print("Contoh perintah :")
    print('  INSERT "JKT001" "Nike" 250000 "M" "Katon" "Hitam" '
          '"Yukka" true 2;')
    print()
    print("Ketik HELP untuk melihat daftar perintah.")


def bantuan():
    # Menampilkan daftar perintah yang tersedia
    print()
    print("DAFTAR PERINTAH :")
    print("  INSERT ... ;   -> Menambah satu produk Jaket")
    print("  SHOW ;         -> Menampilkan semua Jaket yang tersimpan")
    print("  HELP ;         -> Menampilkan daftar perintah ini")
    print("  EXIT ;         -> Keluar dari produt management")
    print()
    print("HOW TO INSERT JAKET :")
    print('  INSERT "id_produk" "merk" harga "ukuran" "bahan" "warna" '
          '"jenis_penutup" kupluk jumlah_saku;')
    print()
    print("Contoh perintah :")
    print('  INSERT "JKT001" "Nike" 250000 "M" "Katon" "Hitam" '
          '"Yukka" true 2;')
    print()


def rapikan(teks):
    # Memangkas spasi di awal dan akhir teks
    return teks.strip()


def baca_perintah():
    # Membaca satu baris perintah dari user lalu memeriksa penanda titik koma
    # Mengembalikan pasangan (status, perintah) dengan status berupa
    # PERINTAH_LENGKAP, INPUT_KOSONG, TANPA_TITIK_KOMA, atau BARIS_KOSONG
    print("> ", end="", flush=True)

    try:
        baris = input()
    except EOFError:
        # Error handling: input ditutup (Ctrl+D atau EOF), program berhenti
        return (INPUT_KOSONG, "")

    baris = rapikan(baris)
    if baris == "":
        return (BARIS_KOSONG, "")

    # Error handling: user menekan Enter tanpa tanda ; di akhir baris
    if baris[-1] != ";":
        return (TANPA_TITIK_KOMA, "")

    return (PERINTAH_LENGKAP, rapikan(baris[:-1]))


def ubah_besar(teks):
    # Mengubah seluruh huruf pada teks menjadi huruf besar
    return teks.upper()


def tokenisasi(perintah):
    # Memecah perintah menjadi token, tanda kutip tidak ikut memisahkan kata
    # Mengembalikan pasangan (daftar token, pesan galat)
    # Pesan galat berisi teks kosong bila pemecahan berhasil
    hasil = []
    token = ""
    dalam_kutip = False
    sudah_pasangan = False

    # Loop membaca karakter per karakter, spasi hanya menjadi pemisah
    # token ketika sedang di luar tanda kutip
    for karakter in perintah:
        if karakter == '"':
            if dalam_kutip:
                token += karakter
                dalam_kutip = False
                sudah_pasangan = True
            elif sudah_pasangan:
                return (None, "tanda kutip tidak seharusnya muncul di "
                              "tengah field")
            else:
                token += karakter
                dalam_kutip = True
        elif karakter.isspace() and not dalam_kutip:
            # Spasi di luar kutip berarti satu token sudah selesai
            if token != "":
                hasil.append(token)
                token = ""
                sudah_pasangan = False
        else:
            token += karakter

    # Error handling: masih di dalam kutip berarti tanda kutip tidak ditutup
    if dalam_kutip:
        return (None, "tanda kutip pembuka tidak ditutup")

    # Token terakhir tidak dipisahkan spasi, jadi simpan manual
    if token != "":
        hasil.append(token)

    return (hasil, "")


def kutip_sah(token):
    # Memeriksa apakah field teks diapit tanda kutip dengan benar
    # Mengembalikan isi field, atau None bila tidak diapit tanda kutip
    if len(token) < 2 or token[0] != '"' or token[-1] != '"':
        return None

    isi = rapikan(token[1:-1])
    if '"' in isi:
        return None

    return isi


def tanpa_kutip(token):
    # Memeriksa apakah field angka dan boolean ditulis tanpa tanda kutip
    return '"' not in token


def perlu_polos(indeks):
    # Field ini harus ditulis polos, bukan diapit tanda kutip
    return indeks in FIELD_TANPA_KUTIP


def ke_bulat(teks):
    # Mengubah teks menjadi bilangan bulat, gagal bila teks bukan angka penuh
    if teks == "" or not teks.isdigit():
        return None
    # Error handling: tangkapan ValueError menjaga agar konversi gagal
    # tidak menghentikan program
    try:
        return int(teks)
    except ValueError:
        return None


def ke_riil(teks):
    # Mengubah teks menjadi bilangan riil, gagal bila teks bukan angka penuh
    jumlah_angka = 0
    jumlah_titik = 0

    # Loop menolak karakter selain angka dan titik desimal
    for karakter in teks:
        if karakter == ".":
            jumlah_titik += 1
        elif karakter.isdigit():
            jumlah_angka += 1
        else:
            return None

    # Maksimal satu titik desimal dan harus ada minimal satu angka
    if jumlah_titik > 1 or jumlah_angka == 0:
        return None
    try:
        return float(teks)
    except ValueError:
        return None


def ke_bool(teks):
    # Mengubah teks menjadi boolean true atau false
    if teks.upper() == "TRUE":
        return True
    if teks.upper() == "FALSE":
        return False
    return None


def sel_jaket(jaket):
    # Mengubah data Jaket menjadi isi sel tabel
    return [
        jaket.get_id(),
        jaket.get_merk(),
        "{:.2f}".format(jaket.get_harga()),
        jaket.get_ukuran(),
        jaket.get_bahan(),
        jaket.get_warna(),
        jaket.get_jenis_penutup(),
        # Nilai kupluk disimpan sebagai True atau False, saat ditampilkan
        # ditulis dalam bahasa Indonesia
        "ada" if jaket.get_kupluk() else "tidak ada",
        str(jaket.get_jumlah_saku())
    ]


def hitung_lebar_kolom(daftar):
    # Menghitung lebar setiap kolom dari judul kolom dan data tersimpan
    for i in range(JUMLAH_KOLOM):
        col[i] = len(JUDUL_KOLOM[i])

    # Loop dua tingkat: setiap data dibandingkan kolom per kolom, kolom
    # diperlebar bila isi data lebih panjang dari judul kolom
    for jaket in daftar:
        isi = sel_jaket(jaket)
        for i in range(JUMLAH_KOLOM):
            if len(isi[i]) > col[i]:
                col[i] = len(isi[i])


def separator(karakter):
    # Mencetak garis pembatas tabel, contoh karakter "-" atau "="
    print("+" + "+".join(karakter * (col[i] + 2) for i in range(JUMLAH_KOLOM))
          + "+")


def row(cols):
    # Mencetak satu baris data dalam tabel
    print("|" + "|".join(" " + cols[i].ljust(col[i]) + " "
                         for i in range(JUMLAH_KOLOM)) + "|")


def header():
    # Mencetak judul kolom tabel
    row(JUDUL_KOLOM)


def print_table(data):
    # Mencetak satu data Jaket dalam bentuk baris tabel
    row(sel_jaket(data))


def cetak_daftar(daftar):
    # Menampilkan seluruh Jaket yang tersimpan dalam bentuk tabel
    # Error handling: tidak ada data, tabel tidak perlu dicetak
    if len(daftar) == 0:
        print_error("belum ada Jaket yang tersimpan.")
        print()
        return

    hitung_lebar_kolom(daftar)

    print("DAFTAR JAKET ({}) :".format(len(daftar)))
    separator("=")
    header()
    separator("=")
    # Loop mencetak satu baris tabel untuk setiap Jaket yang tersimpan
    for jaket in daftar:
        print_table(jaket)
    separator("-")
    print()


def proses_insert(daftar, token):
    # Memproses perintah INSERT beserta validasi seluruh field
    # Error handling: jumlah field tidak sesuai, insert langsung dibatalkan
    # supaya tidak ada data yang tersimpan setengah jadi
    if len(token) - 1 != JUMLAH_FIELD_JAKET:
        print_error("INSERT Jaket membutuhkan {} field, ditemukan {} field."
                    .format(JUMLAH_FIELD_JAKET, len(token) - 1))
        print_error('Format : INSERT "id_produk" "merk" harga "ukuran" '
                    '"bahan" "warna" "jenis_penutup" kupluk jumlah_saku;')
        print()
        return

    isi = [""] * JUMLAH_FIELD_JAKET
    # Validasi tiap field: field teks wajib diapit kutip, field polos wajib
    # ditulis tanpa kutip. Kalau ada satu saja yang salah, insert dibatalkan.
    for i in range(JUMLAH_FIELD_JAKET):
        bagian = token[i + 1]

        if perlu_polos(i):
            if not tanpa_kutip(bagian):
                print_error('field "{}" ditulis polos tanpa tanda kutip.'
                            .format(NAMA_FIELD[i]))
                print()
                return
            isi[i] = bagian
        else:
            isi[i] = kutip_sah(bagian)
            if isi[i] is None:
                print_error('field "{}" harus teks yang diapit tanda kutip, '
                            'contoh "{}".'.format(NAMA_FIELD[i], NAMA_FIELD[i]))
                print()
                return
            if isi[i] == "":
                print_error('field "{}" tidak boleh kosong.'
                            .format(NAMA_FIELD[i]))
                print()
                return

    # Konversi ke tipe data, tiap kondisi gagal langsung informs ke user
    harga = ke_riil(isi[2])
    if harga is None or harga <= 0:
        print_error('field "harga" harus angka lebih besar dari 0.')
        print()
        return

    kupluk = ke_bool(isi[7])
    if kupluk is None:
        print_error('field "kupluk" harus true atau false.')
        print()
        return

    jumlah_saku = ke_bulat(isi[8])
    if jumlah_saku is None or jumlah_saku < 0:
        print_error('field "jumlah_saku" harus angka bulat 0 atau lebih.')
        print()
        return

    # Loop mengecek id_produk satu per satu, bila ketemu yang sama maka
    # data baru tidak ditambahkan
    id_produk = isi[0]
    for jaket in daftar:
        if jaket.get_id() == id_produk:
            print_error('id_produk "{}" sudah digunakan, gunakan '
                        'id_produk yang lain.'.format(id_produk))
            print()
            return

    daftar.append(Jaket(id_produk, isi[1], harga, isi[3], isi[4], isi[5],
                        isi[6], kupluk, jumlah_saku))

    print_sukses('Jaket "{}" ({}) berhasil ditambahkan. Total {} Jaket.'
                 .format(id_produk, isi[1], len(daftar)))
    print()


def proses_show(daftar):
    # Memproses perintah SHOW
    if len(daftar) == 0:
        print_error("belum ada Jaket yang tersimpan.")
        print()
        return
    cetak_daftar(daftar)


# Program utama
def main():
    intro()

    daftar = [
        Jaket("JKT001", "Nike", 250000.0, "M", "Katon", "Hitam", "Yukka", True, 2),
        Jaket("JKT002", "Adidas", 189500.0, "L", "Denim", "Biru", "Zipper", False, 3),
        Jaket("JKT003", "Uniqlo", 99000.0, "S", "Wol", "Merah", "Mantel", True, 0),
        Jaket("JKT004", "Eiger", 275000.0, "XXL", "Goretex", "Hijau", "Zipper", True, 5),
        Jaket("JKT005", "H&M", 120000.0, "XL", "Flea", "Kuning", "Yukka", True, 4),
    ]
    keluar = False

    # Loop program: membaca perintah berulang sampai user mengetik EXIT
    while not keluar:
        status, perintah = baca_perintah()

        # Error handling: kondisi berikut bukan error, hanya         # Error handling: kondisi berikut bukan error, hanya kondisi yang
        # tidak menghasilkan perintah, jadi lanjut ke iterasi berikutnya
        if status == INPUT_KOSONG:
            break
        if status == BARIS_KOSONG:
            continue
        if status == TANPA_TITIK_KOMA:
            print_error("perintah tidak diakhiri tanda titik koma ;")
            print()
            continue

        # Pecah perintah menjadi token, kegagalan tokenisasi langsung
        # dilewati supaya program tidak berhenti
        token, galat = tokenisasi(perintah)
        if token is None:
            print_error(galat + ".")
            print()
            continue
        if len(token) == 0:
            continue

        # Kata pertama menentukan perintah, huruf besar kecil diabaikan
        kata = ubah_besar(token[0])

        if kata == "INSERT":
            proses_insert(daftar, token)
        elif kata == "SHOW":
            proses_show(daftar)
        elif kata == "HELP":
            bantuan()
        elif kata == "EXIT":
            # Menghentikan loop dengan mengubah nilai penanda keluar
            keluar = True
        else:
            # Error handling: nama perintah tidak ada di daftar
            print_error('perintah "{}" tidak dikenal.'.format(token[0]))
            print()

    print()
    print("Program selesai.")


if __name__ == "__main__":
    main()
