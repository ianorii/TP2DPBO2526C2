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
│       ├── image5.png
│       └── image6.png
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
    ├── Php/
    │   ├── image1.png
    │   ├── image2.png
    │   └── image3.png
    └── Python/
        ├── image1.png
        └── image2.png
```

---

## Penjelasan Fitur

Program ini menerapkan **inheritance** (pewarisan) tiga tingkat pada domain produk pakaian, yaitu `Produk` → `Pakaian` → `Jaket`. Setiap kelas turunan mewarisi seluruh atribut kelas induknya lalu menambah atribut khasnya sendiri.

### Fitur Utama

- **Data awal**: program sudah memuat 5 data Jaket default sejak dijalankan, sehingga tabel langsung terisi tanpa perlu menambah data terlebih dahulu.
- **Pilihan aksi**: pengguna dapat memilih aksi yang tersedia, yaitu menampilkan data atau menambahkan data baru.
- **Tabel dinamis**: seluruh data yang tersimpan ditampilkan dalam bentuk tabel yang menyesuaikan diri dengan jumlah data, bukan tabel dengan jumlah baris tetap.
- **Input data baru**: pengguna dapat menginput data baru beserta seluruh atributnya.
- **Data unik**: `id_produk` yang sama tidak dapat dipakai untuk menambahkan data lebih dari satu kali.
- **CLI version**: versi C++, Java, dan Python berjalan di terminal dengan perintah `INSERT`, `SHOW`, dan `HELP` yang wajib diakhiri tanda titik koma `;`.
- **WEB version**: versi PHP dengan form untuk memasukkan data dan ada atribut tambahan yaitu foto untuk menyimpan path foto yang digunakan.

### Diagram Class

<img src="./Dokumentasi/Diagram/diagram.png" alt="diagram class Produk, Pakaian, Jaket" width=600>

Pada diagram di atas terdapat tiga class yang hubungannya membentuk pewarisan bertingkat tiga, yaitu `Produk` sebagai class induk, `Pakaian` sebagai class turunan dari `Produk`, dan `Jaket` sebagai class turunan dari `Pakaian`.

### Penjelasan Class

- **`Produk`** adalah class induk yang menyimpan atribut dasar, yaitu `id_produk`, `merk`, dan `harga`. Atribut ini saya letakkan di sini karena semua yang dijual di toko pasti memiliki ID, merk, dan harga, sementara atribut seperti ukuran, bahan, dan warna tidak dimiliki produk berjasa seperti voucher atau pulsa. `Produk` saya jadikan class paling atas karena paling general sehingga cocok menjadi superclass, sehingga atribut dasar cukup ditulis sekali saja (prinsip DRY).
- **`Pakaian`** adalah class turunan `Produk` yang menambah atribut `ukuran`, `bahan`, dan `warna`. Ketiganya hanya relevan untuk produk yang dipakai pada tubuh, sedangkan produk seperti TV atau shampoo tidak memiliki ukuran dan warna yang berarti. Saya menjadikannya class perantara agar `Jaket` memakai atribut tersebut tanpa perlu menyalin ulang kodenya.
- **`Jaket`** adalah class turunan `Pakaian` yang menambah atribut `jenis_penutup`, `kupluk`, dan `jumlah_saku`. Ketiganya hanya relevan untuk jaket sehingga tidak saya letakkan di class atas agar class turunan lain seperti `Kaos` tidak memiliki atribut kosong. Saya memilih jaket karena ke depannya bisa ditambah `Kaos` atau `Kemeja` yang tetap mewarisi seluruh atribut tanpa menulis ulang.

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
<img src="./Dokumentasi/Php/image1.png" width = 600>

### Menambahkan Data
<img src="./Dokumentasi/Php/image2.png" width = 600><br>
<img src="./Dokumentasi/Php/image3.png" width = 600>
