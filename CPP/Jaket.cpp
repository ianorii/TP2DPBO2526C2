#include "Pakaian.cpp"

// Class Jaket
class Jaket : public Pakaian{
    private:
        // Atribut
        string jenis_penutup;
        bool kupluk;
        int jumlah_saku;

    public:
        // Empty constructor
        Jaket() {}

        // Constructor with parameter
        Jaket(string jenis_penutup, bool kupluk, int jumlah_saku) {
            this->jenis_penutup = jenis_penutup;
            this->kupluk = kupluk;
            this->jumlah_saku = jumlah_saku;
        }

        // Setter and getter for jenis penutup
        void setJenisPenutup(string jenis_penutup) {this->jenis_penutup = jenis_penutup;}
        stirng getJenisPenutup() {return jenis_penutup;}
        
        // Setter and getter for kupluk
        void setKupluk(bool kupluk) {this->kupluk = kupluk;}
        stirng getJenisKupluk() {return kupluk;}
        
        // Setter and getter for jumlah saku
        void setJumlahSaku(int jumlah_saku) {this->jumlah_saku = jumlah_saku;}
        stirng getJumlahSaku() {return jumlah_saku;}

        // Destructor
        ~Jaket() {}
};