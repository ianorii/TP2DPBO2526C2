# Class turunan Produk: data pakaian
# Atribut: ukuran, bahan, warna
from Produk import Produk


class Pakaian(Produk):
    # Memanggil constructor milik Produk lewat super()
    def __init__(self, id_produk="", merk="", harga=0.0,
                 ukuran="", bahan="", warna=""):
        super().__init__(id_produk, merk, harga)
        self.ukuran = ukuran
        self.bahan = bahan
        self.warna = warna

    # Setter dan getter
    def set_ukuran(self, ukuran):
        self.ukuran = ukuran

    def get_ukuran(self):
        return self.ukuran

    def set_bahan(self, bahan):
        self.bahan = bahan

    def get_bahan(self):
        return self.bahan

    def set_warna(self, warna):
        self.warna = warna

    def get_warna(self):
        return self.warna

    # Destructor
    def __del__(self):
        pass
