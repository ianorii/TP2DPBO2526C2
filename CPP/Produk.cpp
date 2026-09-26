// Class induk: data dasar sebuah produk
// Atribut: id_produk, merk, harga
class Produk {
    protected:
        string id_produk;
        string merk;
        float harga;

    public:
        // Constructor
        Produk() {}

        Produk(string id_produk, string merk, float harga) {
            this->id_produk = id_produk;
            this->merk = merk;
            this->harga = harga;
        }

        // Setter dan getter for id_produk
        void setId(string id_produk) {this->id_produk = id_produk;}
        string getId() {return id_produk;}

        // Setter dan getter for merk
        void setMerk(string merk) {this->merk = merk;}
        string getMerk() {return merk;}

        // Setter dan getter for harga
        void setHarga(float harga) {this->harga = harga;}
        float getHarga() {return harga;}

        // Destructor
        ~Produk() {}
};
