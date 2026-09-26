<?php

require_once __DIR__ . '/Produk.php';

// Class turunan Produk: data pakaian
// Atribut: ukuran, bahan, warna
class Pakaian extends Produk
{
    protected string $ukuran;
    protected string $bahan;
    protected string $warna;

    // Constructor
    public function __construct(
        string $id_produk,
        string $merk,
        float $harga,
        string $ukuran,
        string $bahan,
        string $warna
    ) {
        // Memanggil constructor milik Produk
        parent::__construct($id_produk, $merk, $harga);
        $this->ukuran = $ukuran;
        $this->bahan = $bahan;
        $this->warna = $warna;
    }

    // Setter dan getter for ukuran
    public function setUkuran(string $ukuran): void
    {
        $this->ukuran = $ukuran;
    }

    public function getUkuran(): string
    {
        return $this->ukuran;
    }

    // Setter dan getter for bahan
    public function setBahan(string $bahan): void
    {
        $this->bahan = $bahan;
    }

    public function getBahan(): string
    {
        return $this->bahan;
    }

    // Setter dan getter for warna
    public function setWarna(string $warna): void
    {
        $this->warna = $warna;
    }

    public function getWarna(): string
    {
        return $this->warna;
    }

    // Destructor
    public function __destruct()
    {
    }
}
