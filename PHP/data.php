<?php

require_once __DIR__ . '/Jaket.php';

// Data awal yang langsung tampil saat halaman dibuka
// Path foto menunjuk ke folder assets/
$daftar = [
    new Jaket("JKT001", "Nike", 250000.0, "M", "Katon", "Hitam", "Yukka", true, 2, "assets/image1.png"),
    new Jaket("JKT002", "Adidas", 189500.0, "L", "Denim", "Biru", "Zipper", false, 3, "assets/image2.png"),
    new Jaket("JKT003", "Uniqlo", 99000.0, "S", "Wol", "Merah", "Mantel", true, 0, "assets/image3.png"),
    new Jaket("JKT004", "Eiger", 275000.0, "XXL", "Goretex", "Hijau", "Zipper", true, 5, "assets/image4.png"),
    new Jaket("JKT005", "H&M", 120000.0, "XL", "Flea", "Kuning", "Yukka", true, 4, "assets/image5.png"),
];
