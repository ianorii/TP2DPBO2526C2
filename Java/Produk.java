// Class induk: data dasar sebuah produk
// Atribut: idProduk, merk, harga

public class Produk {
    protected String idProduk;
    protected String merk;
    protected float harga;

    // Constructor
    public Produk() {
        this.idProduk = "";
        this.merk = "";
        this.harga = 0.0f;
    }

    public Produk(String idProduk, String merk, float harga) {
        this.idProduk = idProduk;
        this.merk = merk;
        this.harga = harga;
    }

    // Setter dan getter for idProduk
    public void setIdProduk(String idProduk) {
        this.idProduk = idProduk;
    }

    public String getIdProduk() {
        return idProduk;
    }

    // Setter dan getter for merk
    public void setMerk(String merk) {
        this.merk = merk;
    }

    public String getMerk() {
        return merk;
    }

    // Setter dan getter for harga
    public void setHarga(float harga) {
        this.harga = harga;
    }

    public float getHarga() {
        return harga;
    }

    // Destructor: Java memakai garbage collector, method ini hanya
    // disertakan agar sama dengan versi C++
    @Override
    @SuppressWarnings("removal")
    protected void finalize() throws Throwable {
        super.finalize();
    }
}
