// Class produk
class Produk {
    protected:
        // Atribut
        string id_produk;
        string merk;
        float harga;
    
    public:
        // Empty constructor
        Produk() {}

        // Constructor with parameter
        Produk(string id_produk, string merk, float harga) {
            this->id_produk = id_produk;
            this->merk = merk;
            this->harga = harga;
        }
        
        // Setter and getter for id
        void setId(string id_produk) {this->id_produk = id_produk;}
        string getId() {return id_produk;}

        // Setter and getter for merk
        void serMerk(string merk) {this->merk = merk;}
        string getMerk() {return merk;}

        // Setter and getter for harga
        void setHarga(float harga) {this->harga = harga;}
        float getHarga() {return harga;}

        // Destructor
        ~Produk() {}
};