#include "Produk.cpp"

// Class turunan Produk: data pakaian
// Atribut: ukuran, bahan, warna
class Pakaian : public Produk{
    protected:
        string ukuran;
        string bahan;
        string warna;

    public:
        // Constructor
        Pakaian() {}

        Pakaian(string id_produk, string merk, float harga, string ukuran, string bahan, string warna) : Produk(id_produk, merk, harga) {
            this->ukuran = ukuran;
            this->bahan = bahan;
            this->warna = warna;
        }

        // Setter dan getter for ukuran
        void setUkuran(string ukuran) {this->ukuran = ukuran;}
        string getUkuran() {return ukuran;}

        // Setter dan getter for bahan
        void setBahan(string bahan) {this->bahan = bahan;}
        string getBahan() {return bahan;}

        // Setter dan getter for warna
        void setWarna(string warna) {this->warna = warna;}
        string getWarna() {return warna;}

        // Destructor
        ~Pakaian() {}
};
