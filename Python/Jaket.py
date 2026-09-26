# Class turunan Pakaian: data jaket
# Atribut: jenis_penutup, kupluk, jumlah_saku
from Pakaian import Pakaian

class Jaket(Pakaian):
    # Memanggil constructor milik Pakaian lewat super()
    def __init__(self, id_produk="", merk="", harga=0.0,
                 ukuran="", bahan="", warna="",
                 jenis_penutup="", kupluk=False, jumlah_saku=0):
        super().__init__(id_produk, merk, harga, ukuran, bahan, warna)
        self.jenis_penutup = jenis_penutup
        self.kupluk = kupluk
        self.jumlah_saku = jumlah_saku

    # Setter dan getter for jenis_penutup
    def set_jenis_penutup(self, jenis_penutup):
        self.jenis_penutup = jenis_penutup

    def get_jenis_penutup(self):
        return self.jenis_penutup

    # Setter dan getter for kupluk
    def set_kupluk(self, kupluk):
        self.kupluk = kupluk

    def get_kupluk(self):
        return self.kupluk

    # Setter dan getter for jumlah_saku
    def set_jumlah_saku(self, jumlah_saku):
        self.jumlah_saku = jumlah_saku

    def get_jumlah_saku(self):
        return self.jumlah_saku

    # Destructor
    def __del__(self):
        pass
