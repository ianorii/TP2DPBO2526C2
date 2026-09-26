// Class turunan Pakaian: data jaket
// Atribut: jenisPenutup, kupluk, jumlahSaku

public class Jaket extends Pakaian {
    private String jenisPenutup;
    private boolean kupluk;
    private int jumlahSaku;

    // Constructor
    public Jaket() {
        super();
        this.jenisPenutup = "";
        this.kupluk = false;
        this.jumlahSaku = 0;
    }

    public Jaket(String idProduk, String merk, float harga,
                 String ukuran, String bahan, String warna,
                 String jenisPenutup, boolean kupluk, int jumlahSaku) {
        super(idProduk, merk, harga, ukuran, bahan, warna);
        this.jenisPenutup = jenisPenutup;
        this.kupluk = kupluk;
        this.jumlahSaku = jumlahSaku;
    }

    // Setter dan getter for jenisPenutup
    public void setJenisPenutup(String jenisPenutup) {
        this.jenisPenutup = jenisPenutup;
    }

    public String getJenisPenutup() {
        return jenisPenutup;
    }

    // Setter dan getter for kupluk
    public void setKupluk(boolean kupluk) {
        this.kupluk = kupluk;
    }

    public boolean isKupluk() {
        return kupluk;
    }

    // Setter dan getter for jumlahSaku
    public void setJumlahSaku(int jumlahSaku) {
        this.jumlahSaku = jumlahSaku;
    }

    public int getJumlahSaku() {
        return jumlahSaku;
    }

    // Destructor: Java memakai garbage collector, method ini hanya
    // disertakan agar sama dengan versi C++
    @Override
    @SuppressWarnings("removal")
    protected void finalize() throws Throwable {
        super.finalize();
    }
}
