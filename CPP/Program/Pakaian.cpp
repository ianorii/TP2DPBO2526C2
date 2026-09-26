// Class Pakaian
class Pakaian {
    protected:
        // Atribut
        string ukuran;
        string bahan;
        string warna;
    
    public:
        // Empty constructor
        Pakaian() {}

        // Constructor with parameter
        Pakaian(string ukuran, string bahan, string warna) {
            this->ukuran = ukuran;
            this->bahan = bahan;
            this->warna = warna;
        }

        // Setter and getter for ukuran
        void setUkuran(string ukuran) {this->ukuran = ukuran;}
        string getUkuran() {return ukuran;}
        
        // Setter and getter for bahan
        void setBahan(string bahan) {this->bahan = bahan;}
        string getBahan() {return bahan;}
        
        // Setter and getter for warna
        void setWarna(string warna) {this->warna = warna;}
        string getWarna() {return warna;}

        // Destructor
        ~Pakaian() {}
}