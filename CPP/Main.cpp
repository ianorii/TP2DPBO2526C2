#include <bits/stdc++.h>
using namespace std;
#include "Jaket.cpp"

// =============================================================================
//  MAKRO WARNA PADA TERMINAL
// =============================================================================
#define RESET               "\033[0m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define CYAN                "\033[36m"
#define YELLOW              "\033[33m"
#define BOLD                "\033[1m"

// Jumlah field pada perintah INSERT Jaket
const int JUMLAH_FIELD_JAKET = 9;

// Indeks field yang ditulis polos tanpa tanda kutip (angka dan boolean)
const int FIELD_TANPA_KUTIP[] = {2, 7, 8};
const int JUMLAH_FIELD_TANPA_KUTIP = 3;

// Nama field sesuai urutan pada perintah INSERT
const string NAMA_FIELD[JUMLAH_FIELD_JAKET] = {
    "id_produk", "merk", "harga", "ukuran", "bahan",
    "warna", "jenis_penutup", "kupluk", "jumlah_saku"
};

// Jumlah kolom pada tabel Jaket
const int JUMLAH_KOLOM = 9;

// Judul kolom tabel Jaket
const string JUDUL_KOLOM[JUMLAH_KOLOM] = {
    "ID Produk", "Merk", "Harga", "Ukuran", "Bahan",
    "Warna", "Jenis Penutup", "Kupluk", "Saku"
};

// Lebar tiap kolom, dihitung ulang setiap tabel dicetak
int col[JUMLAH_KOLOM];

// Status hasil pembacaan perintah
const int PERINTAH_LENGKAP = 0;
const int INPUT_KOSONG = 1;
const int TANPA_TITIK_KOMA = 2;
const int BARIS_KOSONG = 3;

// Menampilkan pesan kesalahan dengan warna merah
void printError(const string& pesan) {
    printf(RED "[ERROR] : %s" RESET "\n", pesan.c_str());
}

// Menampilkan pesan berhasil dengan warna hijau
void printSukses(const string& pesan) {
    printf(GREEN "[SUCSESS] : %s" RESET "\n", pesan.c_str());
}

// Menampilkan judul program, format INSERT, dan keterangan tiap tipe field
void intro() {
    printf("======================================================\n");
    printf("        WELCOME TO PRODUK MANAGEMENT\n");
    printf("======================================================\n");
    printf("DAFTAR PERINTAH :\n");
    printf("  INSERT ... ;   -> Menambah satu produk Jaket\n");
    printf("  SHOW ;         -> Menampilkan semua Jaket yang tersimpan\n");
    printf("  HELP ;         -> Menampilkan daftar perintah ini\n");
    printf("  EXIT ;         -> Keluar dari produt management\n");
    printf("\n");

    printf("HOW TO INSERT JAKET :\n");
    printf("  INSERT \"id_produk\" \"merk\" harga \"ukuran\" \"bahan\" \"warna\" \"jenis_penutup\" kupluk jumlah_saku;\n");
    printf("\n");

    printf("Contoh perintah :\n");
    printf("  INSERT \"JKT001\" \"Nike\" 250000 \"M\" \"Katon\" \"Hitam\" \"Yukka\" true 2;\n");
    printf("\n");

    printf("Ketik HELP untuk melihat daftar perintah.\n");
}

// Menampilkan daftar perintah yang tersedia
void bantuan() {
    printf("\n");
    printf("DAFTAR PERINTAH :\n");
    printf("  INSERT ... ;   -> Menambah satu produk Jaket\n");
    printf("  SHOW ;         -> Menampilkan semua Jaket yang tersimpan\n");
    printf("  HELP ;         -> Menampilkan daftar perintah ini\n");
    printf("  EXIT ;         -> Keluar dari produt management\n");
    printf("\n");
}

// Memangkas spasi di awal dan akhir teks
string rapikan(const string& teks) {
    int panjang = (int)teks.length();
    int awal = 0;
    int akhir = panjang - 1;

    while (awal < panjang && (teks[awal] == ' ' || teks[awal] == '\t')) {
        awal++;
    }
    while (akhir >= awal && (teks[akhir] == ' ' || teks[akhir] == '\t')) {
        akhir--;
    }

    if (akhir < awal) {
        return "";
    }
    return teks.substr(awal, akhir - awal + 1);
}

// Membaca satu baris perintah dari user lalu memeriksa penanda titik koma
// Mengembalikan PERINTAH_LENGKAP, INPUT_KOSONG, TANPA_TITIK_KOMA, atau BARIS_KOSONG
int bacaPerintah(string& perintah) {
    perintah.clear();

    printf("> ");
    fflush(stdout);

    string baris;
    if (!getline(cin, baris)) {
        return INPUT_KOSONG;
    }

    baris = rapikan(baris);
    if (baris.empty()) {
        return BARIS_KOSONG;
    }

    // user menekan Enter tanpa tanda ; di akhir baris
    if (baris[baris.length() - 1] != ';') {
        return TANPA_TITIK_KOMA;
    }

    perintah = rapikan(baris.substr(0, baris.length() - 1));
    return PERINTAH_LENGKAP;
}

// Mengubah seluruh huruf pada teks menjadi huruf besar
void ubahBesar(string& teks) {
    for (int i = 0; i < teks.length(); i++) {
        teks[i] = toupper((unsigned char)teks[i]);
    }
}

// Memecah perintah menjadi token, tanda kutip tidak ikut memisahkan kata
// Gagal bila ada tanda kutip yang tidak berpasangan
bool tokenisasi(const string& perintah, vector<string>& hasil, string& galat) {
    hasil.clear();
    string token;
    bool dalamKutip = false;
    bool sudahPasangan = false;

    // Loop ini membaca karakter demi karakter, spasi hanya dipisah sebagai
    // pemisah token ketika sedang di luar tanda kutip
    for (int i = 0; i < perintah.length(); i++) {
        char karakter = perintah[i];

        if (karakter == '"') {
            if (dalamKutip) {
                token += karakter;
                dalamKutip = false;
                sudahPasangan = true;
            } else if (sudahPasangan) {
                galat = "tanda kutip tidak seharusnya muncul di tengah field";
                return false;
            } else {
                token += karakter;
                dalamKutip = true;
            }
        } else if (isspace((unsigned char)karakter) && !dalamKutip) {
            if (!token.empty()) {
                hasil.push_back(token);
                token.clear();
                sudahPasangan = false;
            }
        } else {
            token += karakter;
        }
    }

    // Error handling: loop selesai masih di dalam kutip berarti user lupa
    // menutup tanda kutipnya
    if (dalamKutip) {
        galat = "tanda kutip pembuka tidak ditutup";
        return false;
    }

    // Token terakhir tidak pernah dipisah oleh spasi, jadi simpan manual
    if (!token.empty()) {
        hasil.push_back(token);
    }

    return true;
}

// Memeriksa apakah field teks diapit tanda kutip dengan benar
bool kutipSah(const string& token, string& isi) {
    if (token.size() < 2 || token.front() != '"' || token.back() != '"') {
        return false;
    }

    isi = rapikan(token.substr(1, token.size() - 2));
    return isi.find('"') == string::npos;
}

// Memeriksa apakah field angka dan boolean ditulis tanpa tanda kutip
bool tanpaKutip(const string& token) {
    return token.find('"') == string::npos;
}

// Field ini harus ditulis polos, bukan diapit tanda kutip
bool perluPolos(int indeks) {
    // Loop mencari apakah indeks field ini termasuk field polos
    for (int i = 0; i < JUMLAH_FIELD_TANPA_KUTIP; i++) {
        if (FIELD_TANPA_KUTIP[i] == indeks) {
            return true;
        }
    }
    return false;
}

// Memeriksa apakah seluruh karakter teks adalah angka
bool semuaAngka(const string& teks) {
    if (teks.empty()) {
        return false;
    }
    for (int i = 0; i < teks.length(); i++) {
        if (!isdigit((unsigned char)teks[i])) {
            return false;
        }
    }
    return true;
}

// Mengubah teks menjadi bilangan bulat, gagal bila teks bukan angka penuh
bool keBulat(const string& teks, int& hasil) {
    if (!semuaAngka(teks)) {
        return false;
    }
    // Error handling: stoi melempar exception bila angka terlalu besar untuk
    // int, ditangkap agar proses INSERT tidak ikut berhenti
    try {
        hasil = stoi(teks);
        return true;
    } catch (...) {
        return false;
    }
}

// Mengubah teks menjadi bilangan riil, gagal bila teks bukan angka penuh
bool keRiil(const string& teks, float& hasil) {
    int jumlahAngka = 0;
    int jumlahTitik = 0;

    // Loop ini menolak karakter selain angka dan titik desimal
    for (int i = 0; i < teks.length(); i++) {
        char karakter = teks[i];
        if (karakter == '.') {
            jumlahTitik++;
        } else if (isdigit((unsigned char)karakter)) {
            jumlahAngka++;
        } else {
            return false;
        }
    }

    // Maksimal satu titik desimal dan harus ada minimal satu angka
    if (jumlahTitik > 1 || jumlahAngka == 0) {
        return false;
    }
    // Error handling: stof melempar exception bila teks tidak valid
    try {
        hasil = stof(teks);
        return true;
    } catch (...) {
        return false;
    }
}

// Mengubah teks menjadi boolean true atau false
bool keBool(const string& teks, bool& hasil) {
    string sementara = teks;
    ubahBesar(sementara);

    if (sementara == "TRUE") {
        hasil = true;
        return true;
    }
    if (sementara == "FALSE") {
        hasil = false;
        return true;
    }
    return false;
}

// Mengubah data Jaket menjadi isi sel tabel
void selJaket(Jaket& jaket, string isi[]) {
    // Harga diformat menjadi 2 angka di belakang koma agar rapi di tabel
    stringstream harga;
    harga << fixed << setprecision(2) << jaket.getHarga();

    isi[0] = jaket.getId();
    isi[1] = jaket.getMerk();
    isi[2] = harga.str();
    isi[3] = jaket.getUkuran();
    isi[4] = jaket.getBahan();
    isi[5] = jaket.getWarna();
    isi[6] = jaket.getJenisPenutup();
    isi[7] = jaket.getJenisKupluk() ? "true" : "false";
    isi[8] = to_string(jaket.getJumlahSaku());
}

// Menghitung lebar setiap kolom dari judul kolom dan data tersimpan
void hitungLebarKolom(vector<Jaket>& daftar) {
    for (int i = 0; i < JUMLAH_KOLOM; i++) {
        col[i] = JUDUL_KOLOM[i].length();
    }

    // Loop dua tingkat: tiap data Jaket dibandingkan kolom per kolom,
    // kolom diperlebar bila isi data lebih panjang dari judul kolom
    string isi[JUMLAH_KOLOM];
    for (int k = 0; k < daftar.size(); k++) {
        selJaket(daftar[k], isi);
        for (int i = 0; i < JUMLAH_KOLOM; i++) {
            if (isi[i].length() > col[i]) {
                col[i] = isi[i].length();
            }
        }
    }
}

// Mencetak garis pembatas tabel (+---+)
void separator() {
    cout << "+";
    for (int i = 0; i < JUMLAH_KOLOM; i++) {
        for (int j = 0; j < col[i] + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;
}

// Mencetak garis pembatas judul tabel (+===+)
void headerSeparator() {
    cout << "+";
    for (int i = 0; i < JUMLAH_KOLOM; i++) {
        for (int j = 0; j < col[i] + 2; j++) {
            cout << "=";
        }
        cout << "+";
    }
    cout << endl;
}

// Mencetak satu baris data dalam tabel
void row(string cols[]) {
    for (int i = 0; i < JUMLAH_KOLOM; i++) {
        cout << "| " << left << setw(col[i]) << cols[i] << " ";
    }
    cout << "|" << endl;
}

// Mencetak judul kolom tabel
void header() {
    string judul[JUMLAH_KOLOM];
    for (int i = 0; i < JUMLAH_KOLOM; i++) {
        judul[i] = JUDUL_KOLOM[i];
    }
    row(judul);
}

// Mencetak satu data Jaket dalam bentuk baris tabel
void printTable(Jaket& data) {
    string isi[JUMLAH_KOLOM];
    selJaket(data, isi);
    row(isi);
}

// Menampilkan seluruh Jaket yang tersimpan dalam bentuk tabel
void cetakDaftar(vector<Jaket>& daftar) {
    // Error handling: tidak ada data, tabel tidak perlu dicetak
    if (daftar.empty()) {
        printError("belum ada Jaket yang tersimpan.");
        printf("\n");
        return;
    }

    hitungLebarKolom(daftar);
    fflush(stdout);

    printf("DAFTAR JAKET (%d) :\n", (int)daftar.size());
    headerSeparator();
    header();
    headerSeparator();
    // Loop mencetak satu baris tabel untuk setiap Jaket yang tersimpan
    for (int i = 0; i < daftar.size(); i++) {
        printTable(daftar[i]);
    }
    separator();
    cout << endl;
}

// Memproses perintah INSERT beserta validasi seluruh field
void prosesInsert(vector<Jaket>& daftar, const vector<string>& token) {
    // Error handling: jumlah field tidak sesuai, langsung batalkan insert
    // supaya tidak ada data yang tersimpan setengah jadi
    if (token.size() - 1 != JUMLAH_FIELD_JAKET) {
        printError("INSERT Jaket membutuhkan " + to_string(JUMLAH_FIELD_JAKET)
            + " field, ditemukan " + to_string((int)token.size() - 1) + " field.");
        printError("Format : INSERT \"id_produk\" \"merk\" harga \"ukuran\" \"bahan\" \"warna\" \"jenis_penutup\" kupluk jumlah_saku;");
        printf("\n");
        return;
    }

    string isi[JUMLAH_FIELD_JAKET];
    // Validasi tiap field: field teks wajib diapit kutip, field polos wajib
    // ditulis tanpa kutip. Kalau ada satu saja yang salah, insert dibatalkan.
    for (int i = 0; i < JUMLAH_FIELD_JAKET; i++) {
        const string& bagian = token[i + 1];

        if (perluPolos(i)) {
            if (!tanpaKutip(bagian)) {
                printError("field \"" + NAMA_FIELD[i] + "\" ditulis polos tanpa tanda kutip.");
                printf("\n");
                return;
            }
            isi[i] = bagian;
        } else {
            if (!kutipSah(bagian, isi[i])) {
                printError("field \"" + NAMA_FIELD[i] + "\" harus teks yang diapit tanda kutip, contoh \"" + NAMA_FIELD[i] + "\".");
                printf("\n");
                return;
            }
            if (isi[i].empty()) {
                printError("field \"" + NAMA_FIELD[i] + "\" tidak boleh kosong.");
                printf("\n");
                return;
            }
        }
    }

    float harga;
    int jumlah_saku;
    bool kupluk;

    // Konversi ke tipe data, tiap kondisi gagal langsung informs ke user
    if (!keRiil(isi[2], harga) || harga <= 0) {
        printError("field \"harga\" harus angka lebih besar dari 0.");
        printf("\n");
        return;
    }
    if (!keBool(isi[7], kupluk)) {
        printError("field \"kupluk\" harus true atau false.");
        printf("\n");
        return;
    }
    if (!keBulat(isi[8], jumlah_saku) || jumlah_saku < 0) {
        printError("field \"jumlah_saku\" harus angka bulat 0 atau lebih.");
        printf("\n");
        return;
    }

    string id_produk = isi[0];
    for (int i = 0; i < (int)daftar.size(); i++) {
        if (daftar[i].getId() == id_produk) {
            printError("id_produk \"" + id_produk + "\" sudah digunakan, gunakan id_produk yang lain.");
            printf("\n");
            return;
        }
    }

    daftar.push_back(Jaket(id_produk, isi[1], harga, isi[3], isi[4], isi[5], isi[6], kupluk, jumlah_saku));

    printSukses("Jaket \"" + id_produk + "\" (" + isi[1] + ") berhasil ditambahkan. Total " + to_string((int)daftar.size()) + " Jaket.");
    printf("\n");
}

// Memproses perintah SHOW
void prosesShow(vector<Jaket>& daftar) {
    if (daftar.empty()) {
        printError("belum ada Jaket yang tersimpan.");
        printf("\n");
        return;
    }
    cetakDaftar(daftar);
}

int main() {
    intro();

    vector<Jaket> daftar;
    string perintah;
    int exit = 0;

    // Data awal yang sudah tersimpan sebelum program dijalankan
    daftar.push_back(Jaket("JKT001", "Nike", 250000.0f, "M", "Katon", "Hitam", "Yukka", true, 2));
    daftar.push_back(Jaket("JKT002", "Adidas", 189500.0f, "L", "Denim", "Biru", "Zipper", false, 3));
    daftar.push_back(Jaket("JKT003", "Uniqlo", 99000.0f, "S", "Wol", "Merah", "Mantel", true, 0));
    daftar.push_back(Jaket("JKT004", "Eiger", 275000.0f, "XXL", "Goretex", "Hijau", "Zipper", true, 5));
    daftar.push_back(Jaket("JKT005", "H&M", 120000.0f, "XL", "Flea", "Kuning", "Yukka", true, 4));

    // Loop program: membaca perintah berulang sampai user mengetik EXIT
    while (!exit) {
        int status = bacaPerintah(perintah);

        // Error handling: kondisi berikut bukan error, hanya量子 yang tidak
        // menghasilkan perintah, jadi lanjut ke iterasi berikutnya
        if (status == INPUT_KOSONG) {
            break;
        }
        if (status == BARIS_KOSONG) {
            continue;
        }
        if (status == TANPA_TITIK_KOMA) {
            printError("perintah tidak diakhiri tanda titik koma ;");
            printf("\n");
            continue;
        }

        // Pecah perintah menjadi token, kegagalan tokenisasi langsung
        // dilewati supaya program tidak berhenti
        vector<string> token;
        string galat;
        if (!tokenisasi(perintah, token, galat)) {
            printError(galat + ".");
            printf("\n");
            continue;
        }
        if (token.empty()) {
            continue;
        }

        // Kata pertama menentukan perintah, huruf besar kecil diabaikan
        string kata = token[0];
        ubahBesar(kata);

        if (kata == "INSERT") {
            prosesInsert(daftar, token);
        } else if (kata == "SHOW") {
            prosesShow(daftar);
        } else if (kata == "HELP") {
            bantuan();
        } else if (kata == "EXIT") {
            // Menghentikan loop dengan mengubah nilai penanda keluar
            exit = 1;
        } else {
            // Error handling: nama perintah tidak ada di daftar
            printError("perintah \"" + token[0] + "\" tidak dikenal.");
            printf("\n");
        }
    }

    printf("\nProgram selesai.\n");

    return 0;
}
