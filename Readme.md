# TP2 DPBO 2025/2026 C2

## Janji
Saya Muhammad Rian Anugrah dengan NIM 2507241 mengerjakan Tugas Praktikum 2 pada Mata Kuliah Desain dan Pemrograman Berorientasi Objek (DPBO) untuk keberkahan-Nya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin

## Struktur Folder

```
TP2DPBO2526C2/
├── Readme.md
├── CPP/
│   ├── Produk.cpp
│   ├── Pakaian.cpp
│   ├── Jaket.cpp
│   ├── Main.cpp
│   └── TestCase.txt
├── Java/
│   ├── Produk.java
│   ├── Pakaian.java
│   ├── Jaket.java
│   └── Main.java
├── Python/
│   ├── Produk.py
│   ├── Pakaian.py
│   ├── Jaket.py
│   └── Main.py
├── PHP/
│   ├── Produk.php
│   ├── Pakaian.php
│   ├── Jaket.php
│   ├── data.php
│   ├── Main.php
│   └── assets/
│       ├── image1.png
│       ├── image2.png
│       ├── image3.png
│       ├── image4.png
│       └── image5.png
└── Dokumentasi/
    ├── Diagram/
    │   └── diagram.png
    ├── Error/
    │   ├── error1.png
    │   ├── error2.png
    │   ├── error3.png
    │   ├── error4.png
    │   ├── error5.png
    │   ├── error6.png
    │   ├── error7.png
    │   ├── error8.png
    │   ├── error9.png
    │   ├── error10.png
    │   └── error11.png
    ├── CPP/
    │   ├── image1.png
    │   └── image2.png
    ├── Java/
    │   ├── image1.png
    │   └── image2.png
    └── Python/
        ├── image1.png
        └── image2.png
```

---

## Penjelasan Fitur

Program ini menerapkan **inheritance** (pewarisan) tiga tingkat pada domain produk pakaian, yaitu `Produk` → `Pakaian` → `Jaket`. Setiap kelas turunan mewarisi seluruh atribut kelas induknya lalu menambah atribut khasnya sendiri.

### Fitur Utama

Program CLI (C++, Java, Python) bekerja dengan membaca satu baris perintah per iterasi, setiap perintah wajib diakhiri tanda titik koma `;`.

| Perintah | Deskripsi |
|----------|-----------|
| `INSERT ... ;` | Menambah satu produk Jaket baru beserta validasi seluruh field |
| `SHOW ;` | Menampilkan seluruh Jaket yang tersimpan dalam bentuk tabel |
| `HELP ;` | Menampilkan daftar perintah yang tersedia |
| `EXIT ;` | Keluar dari program produk management |

### Diagram Class

<img src="./Dokumentasi/Diagram/diagram.png" alt="diagram class Produk, Pakaian, Jaket" width=600>

Pada diagram di atas terdapat tiga class yang hubungannya membentuk pewarisan bertingkat tiga, yaitu `Produk` sebagai class induk, `Pakaian` sebagai class turunan dari `Produk`, dan `Jaket` sebagai class turunan dari `Pakaian`.

### Penjelasan Class

- **`Produk`** adalah class induk yang menyimpan atribut dasar sebuah produk, yaitu `id_produk`, `merk`, dan `harga`. Ketiga atribut ini saya letakkan di sini karena segala sesuatu yang dijual di toko pasti memiliki ID, merk, dan harga, serta produk tidak selalu berupa barang fisik saja karena bisa juga berupa jasa. Atribut yang lebih spesifik seperti ukuran, bahan, dan warna tidak saya letakkan di `Produk` karena produk lain seperti voucher, pulsa, atau jasa servis tidak memiliki ukuran maupun warna. `Produk` saya jadikan class paling atas karena ia merupakan class yang paling general sehingga cocok menjadi superclass dari seluruh objek yang diturunkan, sehingga atribut dasar cukup ditulis satu kali saja tanpa diulang pada setiap class turunan (prinsip DRY).
- **`Pakaian`** adalah class turunan `Produk` yang menambah atribut `ukuran`, `bahan`, dan `warna`. `Pakaian` merupakan kategori yang lebih khusus dari `Produk`, karena semua pakaian jelas merupakan produk tetapi tidak semua produk merupakan pakaian. Ketiga atribut tersebut hanya relevan untuk produk yang dipakai pada tubuh seperti kaos, kemeja, dan dress, sedangkan produk non-pakaian seperti TV, rice cooker, atau shampoo tidak memiliki ukuran maupun warna yang punya arti mode. Saya memilih `Pakaian` sebagai class perantara dan tidak langsung menurunkan `Jaket` dari `Produk`, karena jika langsung diturunkan maka `ukuran`, `bahan`, dan `warna` harus ditulis ulang pada `Jaket`.
- **`Jaket`** adalah class turunan `Pakaian` yang menambah atribut `jenis_penutup`, `kupluk`, dan `jumlah_saku`. Saya memilih satu contoh saja yaitu jaket karena ke depannya program ini bisa ditambahkan class lain seperti `Kaos`, `Kemeja`, atau `Celana` yang diturunkan dari `Pakaian`, sehingga otomatis menjadi turunan `Produk` juga tanpa perlu menulis ulang atribut. Ketiga atribut tersebut hanya saya letakkan pada `Jaket` karena benar-benar hanya relevan untuk jaket, yaitu `jenis_penutup` yang hanya ada pada pakaian jenis outer, `kupluk` yang hanya ada pada jaket penutup kepala, dan `jumlah_saku` yang tidak dimiliki kaos, sehingga menaruhnya di `Pakaian` atau `Produk` akan membuat sebagian besar class turunan memiliki atribut kosong yang tidak pernah diisi. Saya memilih tiga tingkat `Produk` → `Pakaian` → `Jaket` dan bukan langsung dua tingkat karena pada tingkat yang sama dapat dibuat class lain yang memiliki ciri serupa, misalnya `Kaos` yang juga memiliki ukuran, bahan, dan warna.

Atribut `foto` sengaja hanya ada pada versi PHP karena pada program CLI tidak ada media yang cukup untuk menampilkan gambar, sedangkan pada program Web foto dapat langsung dirender di dalam tabel.

---

## Error Handling Program CLI

### 1. Perintah Tidak Diakhiri Tanda Titik Koma
<img src="./Dokumentasi/Error/error1.png" width=600>

### 2. Jumlah Field INSERT Tidak Sesuai
<img src="./Dokumentasi/Error/error2.png" width=600>

### 3. Field Teks Tidak Diapit Tanda Kutip
<img src="./Dokumentasi/Error/error3.png" width=600>

### 4. Field Angka atau Boolean Diapit Tanda Kutip
<img src="./Dokumentasi/Error/error4.png" width=600>

### 5. Harga Bukan Angka atau Tidak Lebih Besar dari 0
<img src="./Dokumentasi/Error/error5.png" width=600>

### 6. Nilai Kupluk Bukan true atau false
<img src="./Dokumentasi/Error/error6.png" width=600>

### 7. Jumlah Saku Bukan Bilangan Bulat 0 atau Lebih
<img src="./Dokumentasi/Error/error7.png" width=600>

### 8. Field Teks Kosong
<img src="./Dokumentasi/Error/error8.png" width=600>

### 9. Tanda Kutip Tidak Berpasangan
<img src="./Dokumentasi/Error/error9.png" width=600>

### 10. ID Produk Sudah Digunakan
<img src="./Dokumentasi/Error/error10.png" width=600>

### 11. Perintah Tidak Diketahui
<img src="./Dokumentasi/Error/error11.png" width=600>

---

## Dokumentasi C++
### Compile dan Run
```bash
# Compile
cd CPP/
g++ Main.cpp -o Main

# Run
./Main
```

### 1. Menambahkan dan Menampilkan Data
Format perintah, field teks diapit tanda kutip sedangkan field angka dan boolean ditulis polos.
```bash
INSERT "id_produk" "merk" harga "ukuran" "bahan" "warna" "jenis_penutup" kupluk jumlah_saku;
SHOW;
```
<img src="./Dokumentasi/CPP/image1.png" width=600>

### 2. Menampilkan Bantuan
```bash
HELP;
```
<img src="./Dokumentasi/CPP/image2.png" width=600>

---

## Dokumentasi Java
### Compile dan Run
```bash
# Compile
cd Java/
javac Main.java

# Run
java Main
```

### 1. Menambahkan dan Menampilkan Data
Format perintah, field teks diapit tanda kutip sedangkan field angka dan boolean ditulis polos.
```bash
INSERT "id_produk" "merk" harga "ukuran" "bahan" "warna" "jenis_penutup" kupluk jumlah_saku;
SHOW;
```
<img src="./Dokumentasi/Java/image1.png" width=600>

### 2. Menampilkan Bantuan
```bash
HELP;
```
<img src="./Dokumentasi/Java/image2.png" width=600>

---

## Dokumentasi Python
### Compile dan Run
```bash
# Run
cd Python/
python Main.py
```

### 1. Menambahkan dan Menampilkan Data
Format perintah, field teks diapit tanda kutip sedangkan field angka dan boolean ditulis polos.
```bash
INSERT "id_produk" "merk" harga "ukuran" "bahan" "warna" "jenis_penutup" kupluk jumlah_saku;
SHOW;
```
<img src="./Dokumentasi/Python/image1.png" width=600>

### 2. Menampilkan Bantuan
```bash
HELP;
```
<img src="./Dokumentasi/Python/image2.png" width=600>

---

## Dokumentasi Web PHP

### Cara Menjalankan

1. Buka folder `PHP/`
    ```bash
    cd PHP/
    ```
2. Jalankan perintah:
   ```bash
   php -S localhost:8000
   ```
3. Buka browser dan akses `http://localhost:8000/Main.php`

### Tampilan Website

Halaman ini memuat form penambahan data di atas dan tabel seluruh data Jaket di bawahnya. Foto produk ditampilkan pada kolom pertama, dan otomatis diganti teks `belum ada foto` bila path yang diisi tidak menunjuk ke file yang benar-benar ada.

### Menambahkan Data

Isi seluruh field pada form, lalu tekan tombol `Tambah Data`. Data yang berhasil disimpan langsung muncul di tabel pada halaman yang sama, tanpa perlu refresh. Field `Path Foto` diisi relatif terhadap folder `PHP/`, contoh `assets/image1.png`.

Bila field `Path Foto` dikosongkan atau diisi path yang salah, tabel tetap menampilkan baris tersebut dengan teks pengganti `belum ada foto`, bukan gambar rusak.

### Penyimpanan Data

Lima data Jaket pertama ditulis di `PHP/data.php` sebagai data awal dan selalu muncul saat halaman dibuka. Data hasil penambahan form disimpan di `$_SESSION`, bukan di database, sehingga isinya hanya bertahan selama sesi browser masih hidup. Ketika sesi berakhir, tabel kembali berisi lima data awal.

### Error Handling

Seluruh pesan error ditampilkan sekaligus di atas form dalam bentuk daftar, dan isian form yang sudah diketik tidak ikut terhapus supaya mudah diperbaiki.

1. Field teks dikosongkan
2. `harga` bukan angka atau tidak lebih besar dari 0
3. `jumlah_saku` bukan bilangan bulat 0 atau lebih
4. `id_produk` sudah digunakan

Tidak ada satu pun data yang tersimpan bila ada satu saja field yang tidak valid.
