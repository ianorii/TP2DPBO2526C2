<?php

require_once __DIR__ . '/Pakaian.php';

// Class turunan Pakaian: data jaket
// Atribut: jenis_penutup, kupluk, jumlah_saku, foto
class Jaket extends Pakaian
{
    private string $jenis_penutup;
    private bool $kupluk;
    private int $jumlah_saku;
    private string $foto;

    // Constructor
    public function __construct(
        string $id_produk,
        string $merk,
        float $harga,
        string $ukuran,
        string $bahan,
        string $warna,
        string $jenis_penutup,
        bool $kupluk,
        int $jumlah_saku,
        string $foto
    ) {
        // Memanggil constructor milik Pakaian
        parent::__construct($id_produk, $merk, $harga, $ukuran, $bahan, $warna);
        $this->jenis_penutup = $jenis_penutup;
        $this->kupluk = $kupluk;
        $this->jumlah_saku = $jumlah_saku;
        $this->foto = $foto;
    }

    // Setter dan getter for jenis penutup
    public function setJenisPenutup(string $jenis_penutup): void
    {
        $this->jenis_penutup = $jenis_penutup;
    }

    public function getJenisPenutup(): string
    {
        return $this->jenis_penutup;
    }

    // Setter dan getter for kupluk
    public function setKupluk(bool $kupluk): void
    {
        $this->kupluk = $kupluk;
    }

    public function getKupluk(): bool
    {
        return $this->kupluk;
    }

    // Setter dan getter for jumlah saku
    public function setJumlahSaku(int $jumlah_saku): void
    {
        $this->jumlah_saku = $jumlah_saku;
    }

    public function getJumlahSaku(): int
    {
        return $this->jumlah_saku;
    }

    // Setter dan getter for foto
    public function setFoto(string $foto): void
    {
        $this->foto = $foto;
    }

    public function getFoto(): string
    {
        return $this->foto;
    }

    // Destructor
    public function __destruct()
    {
    }
}
