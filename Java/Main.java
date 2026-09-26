import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Locale;


//  MAKRO WARNA PADA TERMINAL
public class Main {
    static final String RESET = "\033[0m";
    static final String RED = "\033[31m";
    static final String GREEN = "\033[32m";
    static final String CYAN = "\033[36m";
    static final String YELLOW = "\033[33m";
    static final String BOLD = "\033[1m";


    // Jumlah field pada perintah INSERT Jaket
    static final int JUMLAH_FIELD_JAKET = 9;

    // Indeks field yang ditulis polos tanpa tanda kutip (angka dan boolean)
    static final int[] FIELD_TANPA_KUTIP = {2, 7, 8};

    // Nama field sesuai urutan pada perintah INSERT
    static final String[] NAMA_FIELD = {
        "id_produk", "merk", "harga", "ukuran", "bahan",
        "warna", "jenis_penutup", "kupluk", "jumlah_saku"
    };

    // Jumlah kolom pada tabel Jaket
    static final int JUMLAH_KOLOM = 9;

    // Judul kolom tabel Jaket
    static final String[] JUDUL_KOLOM = {
        "ID Produk", "Merk", "Harga", "Ukuran", "Bahan",
        "Warna", "Jenis Penutup", "Kupluk", "Saku"
    };

    // Lebar tiap kolom, dihitung ulang setiap tabel dicetak
    static int[] col = new int[JUMLAH_KOLOM];

    // Status hasil pembacaan perintah
    static final int PERINTAH_LENGKAP = 0;
    static final int INPUT_KOSONG = 1;
    static final int TANPA_TITIK_KOMA = 2;
    static final int BARIS_KOSONG = 3;
    

    // Menampilkan pesan kesalahan dengan warna merah
    static void printError(String pesan) {
        System.out.println(RED + "[ERROR] : " + pesan + RESET);
    }

    // Menampilkan pesan berhasil dengan warna hijau
    static void printSukses(String pesan) {
        System.out.println(GREEN + "[SUCSESS] : " + pesan + RESET);
    }

    // Menampilkan judul program, format INSERT, dan daftar perintah
    static void intro() {
        System.out.println("======================================================");
        System.out.println("        WELCOME TO PRODUK MANAGEMENT");
        System.out.println("======================================================");
        System.out.println("DAFTAR PERINTAH :");
        System.out.println("  INSERT ... ;   -> Menambah satu produk Jaket");
        System.out.println("  SHOW ;         -> Menampilkan semua Jaket yang tersimpan");
        System.out.println("  HELP ;         -> Menampilkan daftar perintah ini");
        System.out.println("  EXIT ;         -> Keluar dari produt management");
        System.out.println();

        System.out.println("HOW TO INSERT JAKET :");
        System.out.println("  INSERT \"id_produk\" \"merk\" harga \"ukuran\" \"bahan\" "
                + "\"warna\" \"jenis_penutup\" kupluk jumlah_saku;");
        System.out.println();

        System.out.println("Contoh perintah :");
        System.out.println("  INSERT \"JKT001\" \"Nike\" 250000 \"M\" \"Katon\" "
                + "\"Hitam\" \"Yukka\" true 2;");
        System.out.println();

        System.out.println("Ketik HELP untuk melihat daftar perintah.");
    }

    // Menampilkan daftar perintah yang tersedia
    static void bantuan() {
        System.out.println();
        System.out.println("DAFTAR PERINTAH :");
        System.out.println("  INSERT ... ;   -> Menambah satu produk Jaket");
        System.out.println("  SHOW ;         -> Menampilkan semua Jaket yang tersimpan");
        System.out.println("  HELP ;         -> Menampilkan daftar perintah ini");
        System.out.println("  EXIT ;         -> Keluar dari produt management");
        System.out.println();
    }

    // Memangkas spasi di awal dan akhir teks
    static String rapikan(String teks) {
        return teks.trim();
    }

    // Membaca satu baris perintah dari user lalu memeriksa penanda titik koma
    // Mengembalikan nilai status PERINTAH_LENGKAP, INPUT_KOSONG,
    // TANPA_TITIK_KOMA, atau BARIS_KOSONG
    static int bacaPerintah(BufferedReader reader, String[] perintah) {
        System.out.print("> ");
        System.out.flush();

        String baris;
        // Error handling: IOException ditangkap agar program berhenti dengan
        // rapi, bukan keluar karena error
        try {
            baris = reader.readLine();
        } catch (IOException e) {
            baris = null;
        }

        // mencapai EOF atau stream ditutup
        if (baris == null) {
            return INPUT_KOSONG;
        }

        baris = rapikan(baris);
        if (baris.isEmpty()) {
            return BARIS_KOSONG;
        }

        // Error handling: user menekan Enter tanpa tanda ; di akhir baris
        if (baris.charAt(baris.length() - 1) != ';') {
            return TANPA_TITIK_KOMA;
        }

        perintah[0] = rapikan(baris.substring(0, baris.length() - 1));
        return PERINTAH_LENGKAP;
    }
    

    // Mengubah seluruh huruf pada teks menjadi huruf besar
    static String ubahBesar(String teks) {
        return teks.toUpperCase(Locale.ROOT);
    }

    // Memecah perintah menjadi token, tanda kutip tidak ikut memisahkan kata
    // Mengembalikan daftar token, atau null bila tanda kutip tidak berpasangan
    // Dalam hal gagal, alasan kegagalan disimpan pada galat[0]
    static String[] tokenisasi(String perintah, String[] galat) {
        ArrayList<String> hasil = new ArrayList<String>();
        StringBuilder token = new StringBuilder();
        boolean dalamKutip = false;
        boolean sudahPasangan = false;

        // Loop ini membaca karakter demi karakter, spasi hanya dipisah sebagai
        // pemisah token ketika sedang di luar tanda kutip
        for (int i = 0; i < perintah.length(); i++) {
            char karakter = perintah.charAt(i);

            if (karakter == '"') {
                if (dalamKutip) {
                    token.append(karakter);
                    dalamKutip = false;
                    sudahPasangan = true;
                } else if (sudahPasangan) {
                    galat[0] = "tanda kutip tidak seharusnya muncul di tengah field";
                    return null;
                } else {
                    token.append(karakter);
                    dalamKutip = true;
                }
            } else if (Character.isWhitespace(karakter) && !dalamKutip) {
                // Spasi di luar kutip berarti satu token sudah selesai
                if (token.length() > 0) {
                    hasil.add(token.toString());
                    token.setLength(0);
                    sudahPasangan = false;
                }
            } else {
                token.append(karakter);
            }
        }

        // Error handling: loop selesai masih di dalam kutip berarti user lupa
        // menutup tanda kutipnya
        if (dalamKutip) {
            galat[0] = "tanda kutip pembuka tidak ditutup";
            return null;
        }

        // Token terakhir tidak pernah dipisah oleh spasi, jadi simpan manual
        if (token.length() > 0) {
            hasil.add(token.toString());
        }

        return hasil.toArray(new String[hasil.size()]);
    }

    // Memeriksa apakah field teks diapit tanda kutip dengan benar
    // Mengembalikan isi field, atau null bila tidak diapit tanda kutip
    static String kutipSah(String token) {
        if (token.length() < 2 || token.charAt(0) != '"'
                || token.charAt(token.length() - 1) != '"') {
            return null;
        }

        String isi = rapikan(token.substring(1, token.length() - 1));
        if (isi.indexOf('"') >= 0) {
            return null;
        }

        return isi;
    }

    // Memeriksa apakah field angka dan boolean ditulis tanpa tanda kutip
    static boolean tanpaKutip(String token) {
        return token.indexOf('"') < 0;
    }

    // Field ini harus ditulis polos, bukan diapit tanda kutip
    static boolean perluPolos(int indeks) {
        // Loop mencari apakah indeks field ini termasuk field polos
        for (int i = 0; i < FIELD_TANPA_KUTIP.length; i++) {
            if (FIELD_TANPA_KUTIP[i] == indeks) {
                return true;
            }
        }
        return false;
    }
    

    // Mengubah teks menjadi bilangan bulat, gagal bila teks bukan angka penuh
    static int keBulat(String teks, boolean[] valid) {
        if (teks.isEmpty()) {
            valid[0] = false;
            return 0;
        }
        // Loop menolak karakter selain angka
        for (int i = 0; i < teks.length(); i++) {
            if (!Character.isDigit(teks.charAt(i))) {
                valid[0] = false;
                return 0;
            }
        }
        // Error handling: tangkapan NumberFormatException menjaga agar
        // konversi gagal tidak menghentikan program
        try {
            valid[0] = true;
            return Integer.parseInt(teks);
        } catch (NumberFormatException e) {
            valid[0] = false;
            return 0;
        }
    }

    // Mengubah teks menjadi bilangan riil, gagal bila teks bukan angka penuh
    static float keRiil(String teks, boolean[] valid) {
        int jumlahAngka = 0;
        int jumlahTitik = 0;

        // Loop ini menolak karakter selain angka dan titik desimal
        for (int i = 0; i < teks.length(); i++) {
            char karakter = teks.charAt(i);
            if (karakter == '.') {
                jumlahTitik++;
            } else if (Character.isDigit(karakter)) {
                jumlahAngka++;
            } else {
                valid[0] = false;
                return 0.0f;
            }
        }

        // Maksimal satu titik desimal dan harus ada minimal satu angka
        if (jumlahTitik > 1 || jumlahAngka == 0) {
            valid[0] = false;
            return 0.0f;
        }
        try {
            valid[0] = true;
            return Float.parseFloat(teks);
        } catch (NumberFormatException e) {
            valid[0] = false;
            return 0.0f;
        }
    }

    // Mengubah teks menjadi boolean true atau false
    static boolean keBool(String teks, boolean[] valid) {
        if (ubahBesar(teks).equals("TRUE")) {
            valid[0] = true;
            return true;
        }
        if (ubahBesar(teks).equals("FALSE")) {
            valid[0] = true;
            return false;
        }
        valid[0] = false;
        return false;
    }
    

    // Mengubah data Jaket menjadi isi sel tabel
    static String[] selJaket(Jaket jaket) {
        return new String[] {
            jaket.getIdProduk(),
            jaket.getMerk(),
            String.format(Locale.ROOT, "%.2f", jaket.getHarga()),
            jaket.getUkuran(),
            jaket.getBahan(),
            jaket.getWarna(),
            jaket.getJenisPenutup(),
            jaket.isKupluk() ? "true" : "false",
            String.valueOf(jaket.getJumlahSaku())
        };
    }

    // Menghitung lebar setiap kolom dari judul kolom dan data tersimpan
    static void hitungLebarKolom(ArrayList<Jaket> daftar) {
        for (int i = 0; i < JUMLAH_KOLOM; i++) {
            col[i] = JUDUL_KOLOM[i].length();
        }

        // Loop dua tingkat: setiap data dibandingkan kolom per kolom, kolom
        // diperlebar bila isi data lebih panjang dari judul kolom
        for (int k = 0; k < daftar.size(); k++) {
            String[] isi = selJaket(daftar.get(k));
            for (int i = 0; i < JUMLAH_KOLOM; i++) {
                if (isi[i].length() > col[i]) {
                    col[i] = isi[i].length();
                }
            }
        }
    }

    // Mencetak garis pembatas tabel, contoh karakter '-' atau '='
    static void separator(char karakter) {
        StringBuilder baris = new StringBuilder("+");
        for (int i = 0; i < JUMLAH_KOLOM; i++) {
            for (int j = 0; j < col[i] + 2; j++) {
                baris.append(karakter);
            }
            baris.append('+');
        }
        System.out.println(baris.toString());
    }

    // Mencetak satu baris data dalam tabel
    static void row(String[] cols) {
        StringBuilder baris = new StringBuilder("|");
        for (int i = 0; i < JUMLAH_KOLOM; i++) {
            StringBuilder sel = new StringBuilder(cols[i]);
            // Loop ini menambahkan spasi sampai sel selebar kolomnya
            while (sel.length() < col[i]) {
                sel.append(' ');
            }
            baris.append(' ').append(sel.toString()).append(' ').append('|');
        }
        System.out.println(baris.toString());
    }

    // Mencetak judul kolom tabel
    static void header() {
        row(JUDUL_KOLOM);
    }

    // Mencetak satu data Jaket dalam bentuk baris tabel
    static void printTable(Jaket data) {
        row(selJaket(data));
    }

    // Menampilkan seluruh Jaket yang tersimpan dalam bentuk tabel
    static void cetakDaftar(ArrayList<Jaket> daftar) {
        // Error handling: tidak ada data, tabel tidak perlu dicetak
        if (daftar.isEmpty()) {
            printError("belum ada Jaket yang tersimpan.");
            System.out.println();
            return;
        }

        hitungLebarKolom(daftar);

        System.out.println("DAFTAR JAKET (" + daftar.size() + ") :");
        separator('=');
        header();
        separator('=');
        // Loop mencetak satu baris tabel untuk setiap Jaket yang tersimpan
        for (int i = 0; i < daftar.size(); i++) {
            printTable(daftar.get(i));
        }
        separator('-');
        System.out.println();
    }


    // Memproses perintah INSERT beserta validasi seluruh field
    static void prosesInsert(ArrayList<Jaket> daftar, String[] token) {
        // Error handling: jumlah field tidak sesuai, insert langsung dibatalkan
        // supaya tidak ada data yang tersimpan setengah jadi
        if (token.length - 1 != JUMLAH_FIELD_JAKET) {
            printError("INSERT Jaket membutuhkan " + JUMLAH_FIELD_JAKET
                    + " field, ditemukan " + (token.length - 1) + " field.");
            printError("Format : INSERT \"id_produk\" \"merk\" harga \"ukuran\" "
                    + "\"bahan\" \"warna\" \"jenis_penutup\" kupluk jumlah_saku;");
            System.out.println();
            return;
        }

        String[] isi = new String[JUMLAH_FIELD_JAKET];
        // Validasi tiap field: field teks wajib diapit kutip, field polos wajib
        // ditulis tanpa kutip. Kalau ada satu saja yang salah, insert dibatalkan.
        for (int i = 0; i < JUMLAH_FIELD_JAKET; i++) {
            String bagian = token[i + 1];

            if (perluPolos(i)) {
                if (!tanpaKutip(bagian)) {
                    printError("field \"" + NAMA_FIELD[i]
                            + "\" ditulis polos tanpa tanda kutip.");
                    System.out.println();
                    return;
                }
                isi[i] = bagian;
            } else {
                isi[i] = kutipSah(bagian);
                if (isi[i] == null) {
                    printError("field \"" + NAMA_FIELD[i]
                            + "\" harus teks yang diapit tanda kutip, contoh \""
                            + NAMA_FIELD[i] + "\".");
                    System.out.println();
                    return;
                }
                if (isi[i].isEmpty()) {
                    printError("field \"" + NAMA_FIELD[i] + "\" tidak boleh kosong.");
                    System.out.println();
                    return;
                }
            }
        }

        // Konversi ke tipe data, tiap kondisi gagal langsung informs ke user
        boolean[] valid = new boolean[1];
        float harga = keRiil(isi[2], valid);
        if (!valid[0] || harga <= 0) {
            printError("field \"harga\" harus angka lebih besar dari 0.");
            System.out.println();
            return;
        }

        boolean kupluk = keBool(isi[7], valid);
        if (!valid[0]) {
            printError("field \"kupluk\" harus true atau false.");
            System.out.println();
            return;
        }

        int jumlahSaku = keBulat(isi[8], valid);
        if (!valid[0] || jumlahSaku < 0) {
            printError("field \"jumlah_saku\" harus angka bulat 0 atau lebih.");
            System.out.println();
            return;
        }

        // Loop mengecek id_produk satu per satu, bila ketemu yang sama maka
        // data baru tidak ditambahkan
        String idProduk = isi[0];
        for (int i = 0; i < daftar.size(); i++) {
            if (daftar.get(i).getIdProduk().equals(idProduk)) {
                printError("id_produk \"" + idProduk
                        + "\" sudah digunakan, gunakan id_produk yang lain.");
                System.out.println();
                return;
            }
        }

        daftar.add(new Jaket(idProduk, isi[1], harga, isi[3], isi[4], isi[5],
                isi[6], kupluk, jumlahSaku));

        printSukses("Jaket \"" + idProduk + "\" (" + isi[1]
                + ") berhasil ditambahkan. Total " + daftar.size() + " Jaket.");
        System.out.println();
    }

    // Memproses perintah SHOW
    static void prosesShow(ArrayList<Jaket> daftar) {
        if (daftar.isEmpty()) {
            printError("belum ada Jaket yang tersimpan.");
            System.out.println();
            return;
        }
        cetakDaftar(daftar);
    }
    

    public static void main(String[] args) throws IOException {
        intro();

        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        ArrayList<Jaket> daftar = new ArrayList<Jaket>();
        String[] perintah = new String[1];
        boolean keluar = false;

        // Data awal yang sudah tersimpan sebelum program dijalankan
        daftar.add(new Jaket("JKT001", "Nike", 250000.0f, "M", "Katon", "Hitam", "Yukka", true, 2));
        daftar.add(new Jaket("JKT002", "Adidas", 189500.0f, "L", "Denim", "Biru", "Zipper", false, 3));
        daftar.add(new Jaket("JKT003", "Uniqlo", 99000.0f, "S", "Wol", "Merah", "Mantel", true, 0));
        daftar.add(new Jaket("JKT004", "Eiger", 275000.0f, "XXL", "Goretex", "Hijau", "Zipper", true, 5));
        daftar.add(new Jaket("JKT005", "H&M", 120000.0f, "XL", "Flea", "Kuning", "Yukka", true, 4));

        // Loop program: membaca perintah berulang sampai user mengetik EXIT
        while (!keluar) {
            int status = bacaPerintah(reader, perintah);

            // Error handling: kondisi berikut bukan error, hanya kondisi yang
            // tidak menghasilkan perintah, jadi lanjut ke iterasi berikutnya
            if (status == INPUT_KOSONG) {
                break;
            }
            if (status == BARIS_KOSONG) {
                continue;
            }
            if (status == TANPA_TITIK_KOMA) {
                printError("perintah tidak diakhiri tanda titik koma ;");
                System.out.println();
                continue;
            }

            // Pecah perintah menjadi token, kegagalan tokenisasi langsung
            // dilewati supaya program tidak berhenti
            String[] galat = new String[1];
            String[] token = tokenisasi(perintah[0], galat);
            if (token == null) {
                printError(galat[0] + ".");
                System.out.println();
                continue;
            }
            if (token.length == 0) {
                continue;
            }

            // Kata pertama menentukan perintah, huruf besar kecil diabaikan
            String kata = ubahBesar(token[0]);

            if (kata.equals("INSERT")) {
                prosesInsert(daftar, token);
            } else if (kata.equals("SHOW")) {
                prosesShow(daftar);
            } else if (kata.equals("HELP")) {
                bantuan();
            } else if (kata.equals("EXIT")) {
                // Menghentikan loop dengan mengubah nilai penanda keluar
                keluar = true;
            } else {
                // Error handling: nama perintah tidak ada di daftar
                printError("perintah \"" + token[0] + "\" tidak dikenal.");
                System.out.println();
            }
        }

        System.out.println();
        System.out.println("Program selesai.");
    }
}
