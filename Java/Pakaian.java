// Class turunan Produk: data pakaian
// Atribut: ukuran, bahan, warna

public class Pakaian extends Produk {
    protected String ukuran;
    protected String bahan;
    protected String warna;

    // Constructor
    public Pakaian() {
        super();
        this.ukuran = "";
        this.bahan = "";
        this.warna = "";
    }

    public Pakaian(String idProduk, String merk, float harga,
                    String ukuran, String bahan, String warna) {
        super(idProduk, merk, harga);
        this.ukuran = ukuran;
        this.bahan = bahan;
        this.warna = warna;
    }

    // Setter dan getter
    public void setUkuran(String ukuran) {
        this.ukuran = ukuran;
    }

    public String getUkuran() {
        return ukuran;
    }

    public void setBahan(String bahan) {
        this.bahan = bahan;
    }

    public String getBahan() {
        return bahan;
    }

    public void setWarna(String warna) {
        this.warna = warna;
    }

    public String getWarna() {
        return warna;
    }

    // Destructor: Java memakai garbage collector, method ini hanya
    // disertakan agar sama dengan versi C++
    @Override
    @SuppressWarnings("removal")
    protected void finalize() throws Throwable {
        super.finalize();
    }
}
