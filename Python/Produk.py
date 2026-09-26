# Class induk: data dasar sebuah produk
# Atribut: id_produk, merk, harga

class Produk:
    # Parameter default membuat class ini bisa dibuat tanpa parameter
    def __init__(self, id_produk="", merk="", harga=0.0):
        self.id_produk = id_produk
        self.merk = merk
        self.harga = harga

    # Setter dan getter
    def set_id(self, id_produk):
        self.id_produk = id_produk

    def get_id(self):
        return self.id_produk

    def set_merk(self, merk):
        self.merk = merk

    def get_merk(self):
        return self.merk

    def set_harga(self, harga):
        self.harga = harga

    def get_harga(self):
        return self.harga

    # Destructor
    def __del__(self):
        pass
