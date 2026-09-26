#include "Pakaian.cpp"

// Class turunan Pakaian: data jaket
// Atribut: jenis_penutup, kupluk, jumlah_saku
class Jaket : public Pakaian{
    private:
        string jenis_penutup;
        bool kupluk;
        int jumlah_saku;

    public:
        // Constructor
        Jaket() {}
        
        // Constructor with parameter
        Jaket(string id_produk, string merk, float harga, string ukuran, string bahan, string warna, 
            string jenis_penutup, bool kupluk, int jumlah_saku) : Pakaian(id_produk, merk, harga, ukuran, bahan, warna) {
            this->jenis_penutup = jenis_penutup;
            this->kupluk = kupluk;
            this->jumlah_saku = jumlah_saku;
        }

        // Setter dan getter for jenis_penutup
        void setJenisPenutup(string jenis_penutup) {this->jenis_penutup = jenis_penutup;}
        string getJenisPenutup() {return jenis_penutup;}

        // Setter dan getter for kupluk
        void setKupluk(bool kupluk) {this->kupluk = kupluk;}
        bool getJenisKupluk() {return kupluk;}

        // Setter dan getter for jumlah_saku
        void setJumlahSaku(int jumlah_saku) {this->jumlah_saku = jumlah_saku;}
        int getJumlahSaku() {return jumlah_saku;}

        // Destructor
        ~Jaket() {}
};
