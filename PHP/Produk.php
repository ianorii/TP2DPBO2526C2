<?php

// Class induk: data dasar sebuah produk
// Atribut: id_produk, merk, harga
class Produk
{
    protected string $id_produk;
    protected string $merk;
    protected float $harga;

    // Constructor
    public function __construct(string $id_produk, string $merk, float $harga)
    {
        $this->id_produk = $id_produk;
        $this->merk = $merk;
        $this->harga = $harga;
    }

    // Setter dan getter untuk ID
    public function setIdProduk(string $id_produk): void
    {
        $this->id_produk = $id_produk;
    }

    public function getIdProduk(): string
    {
        return $this->id_produk;
    }

    // Setter dan getter untuk merk
    public function setMerk(string $merk): void
    {
        $this->merk = $merk;
    }

    public function getMerk(): string
    {
        return $this->merk;
    }

    // Setter dan getter untuk harga
    public function setHarga(float $harga): void
    {
        $this->harga = $harga;
    }

    public function getHarga(): float
    {
        return $this->harga;
    }

    // Destructor
    public function __destruct()
    {
    }
}
