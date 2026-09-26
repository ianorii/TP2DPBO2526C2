<?php

require_once __DIR__ . '/data.php';

// Error handling: session bisa gagal dibuka bila folder penyimpanan tidak bisa
// ditulis, program tetap berjalan tanpa fitur tambah data
if (!@session_start()) {
    $_SESSION = [];
}

// Mengubah satu baris data tambahan menjadi objek Jaket
$jaketDariBaris = function (array $baris): Jaket {
    return new Jaket(
        $baris["id_produk"],
        $baris["merk"],
        $baris["harga"],
        $baris["ukuran"],
        $baris["bahan"],
        $baris["warna"],
        $baris["jenis_penutup"],
        $baris["kupluk"],
        $baris["jumlah_saku"],
        $baris["foto"]
    );
};

// Data hasil tambah pada sesi ini digabung dengan data hardcode
$daftar = array_merge($daftar, array_map($jaketDariBaris, $_SESSION["tambahan"] ?? []));

// Daftar isi form
$form = [
    "id_produk" => "",
    "merk" => "",
    "harga" => "",
    "ukuran" => "",
    "bahan" => "",
    "warna" => "",
    "jenis_penutup" => "",
    "kupluk" => "true",
    "jumlah_saku" => "",
    "foto" => "",
];

// Kumpulan pesan error dari validasi
$errors = [];
$sukses = "";

// Error handling: form hanya diproses ketika methodnya POST
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    // Mengambil nilai form, dipakai ulang bila validasi gagal
    foreach (array_keys($form) as $nama) {
        $form[$nama] = trim($_POST[$nama] ?? "");
    }

    // Memeriksa field teks, teks tidak boleh kosong
    foreach (["id_produk", "merk", "ukuran", "bahan", "warna", "jenis_penutup"] as $nama) {
        if ($form[$nama] === "") {
            $errors[] = "field \"" . $nama . "\" tidak boleh kosong.";
        }
    }

    // Memeriksa harga, harus angka lebih besar dari 0
    if ($form["harga"] === "" || !is_numeric($form["harga"]) || (float) $form["harga"] <= 0) {
        $errors[] = "field \"harga\" harus angka lebih besar dari 0.";
    }

    // Memeriksa jumlah_saku, harus bilangan bulat 0 atau lebih
    if ($form["jumlah_saku"] === ""
        || !ctype_digit($form["jumlah_saku"])
        || (int) $form["jumlah_saku"] < 0
    ) {
        $errors[] = "field \"jumlah_saku\" harus angka bulat 0 atau lebih.";
    }

    // Memeriksa id_produk, tidak boleh sama dengan data yang sudah ada
    if ($form["id_produk"] !== "") {
        // Loop mencari id_produk yang sama di seluruh data tersimpan
        foreach ($daftar as $jaket) {
            if ($jaket->getIdProduk() === $form["id_produk"]) {
                $errors[] = "id_produk \"" . $form["id_produk"]
                    . "\" sudah digunakan, gunakan id_produk yang lain.";
                break;
            }
        }
    }

    // Error handling: kalau ada satu saja field yang salah, data tidak disimpan
    if (count($errors) > 0) {
        $sukses = "";
    } else {
        $tambahan = [
            "id_produk" => $form["id_produk"],
            "merk" => $form["merk"],
            "harga" => (float) $form["harga"],
            "ukuran" => $form["ukuran"],
            "bahan" => $form["bahan"],
            "warna" => $form["warna"],
            "jenis_penutup" => $form["jenis_penutup"],
            "kupluk" => $form["kupluk"] === "true",
            "jumlah_saku" => (int) $form["jumlah_saku"],
            "foto" => $form["foto"],
        ];

        $_SESSION["tambahan"][] = $tambahan;

        // Data baru langsung dimasukkan ke daftar yang sedang ditampilkan
        // supaya barisnya muncul di response ini juga, tanpa harus refresh
        $daftar[] = $jaketDariBaris($tambahan);

        $sukses = "Jaket \"" . $tambahan["id_produk"] . "\" (" . $tambahan["merk"]
            . ") berhasil ditambahkan. Total " . count($daftar) . " Jaket.";

        // Mengosongkan form karena data sudah tersimpan
        foreach (array_keys($form) as $nama) {
            $form[$nama] = "";
        }
        $form["kupluk"] = "true";
    }
}

// Daftar judul kolom tabel
$judul = ["Foto", "ID Produk", "Merk", "Harga", "Ukuran", "Bahan", "Warna", "Jenis Penutup", "Kupluk", "Saku"];

// Mengubah satu Jaket menjadi isi sel tabel
function selJaket(Jaket $jaket): array
{
    return [
        selFoto($jaket),
        htmlspecialchars($jaket->getIdProduk()),
        htmlspecialchars($jaket->getMerk()),
        number_format($jaket->getHarga(), 2, ".", ""),
        htmlspecialchars($jaket->getUkuran()),
        htmlspecialchars($jaket->getBahan()),
        htmlspecialchars($jaket->getWarna()),
        htmlspecialchars($jaket->getJenisPenutup()),
        // Nilai kupluk disimpan sebagai true atau false, saat ditampilkan
        // ditulis dalam bahasa Indonesia
        $jaket->getKupluk() ? "ada" : "tidak ada",
        (string) $jaket->getJumlahSaku(),
    ];
}

// Menampilkan foto, atau teks pengganti bila file foto belum ada
function selFoto(Jaket $jaket): string
{
    $path = $jaket->getFoto();

    // Path foto dicek dulu supaya tidak muncul gambar rusak
    if ($path !== "" && file_exists(__DIR__ . '/' . $path)) {
        return '<img src="' . htmlspecialchars($path)
            . '" alt="Foto ' . htmlspecialchars($jaket->getMerk()) . '">';
    }
    return '<span class="placeholder">belum ada foto</span>';
}
?>
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Produk Management</title>
    <style>
        /* Warna: indigo sebagai warna utama, slate untuk teks dan garis,
           hijau untuk pesan sukses, merah untuk pesan error */
        * {
            box-sizing: border-box;
        }

        body {
            margin: 0;
            padding: 30px 20px;
            font-family: Arial, Helvetica, sans-serif;
            color: #1e293b;
            background: #f1f5f9;
        }

        .container {
            max-width: 1100px;
            margin: 0 auto;
        }

        /* Judul halaman */
        .header {
            text-align: center;
            margin-bottom: 24px;
        }

        .header h1 {
            margin: 0 0 6px;
            font-size: 24px;
            letter-spacing: 1px;
            color: #0f172a;
        }

        .header p {
            margin: 0;
            font-size: 14px;
            color: #64748b;
        }

        /* Kartu putih pembungkus tiap bagian */
        .card {
            background: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 10px;
            padding: 20px;
            margin-bottom: 22px;
        }

        .card h2 {
            margin: 0 0 16px;
            font-size: 18px;
            color: #0f172a;
        }

        /* Tabel boleh digeser ke samping pada layar kecil */
        .tabel-wrap {
            overflow-x: auto;
        }

        table {
            border-collapse: collapse;
            width: 100%;
            font-size: 14px;
            white-space: nowrap;
        }

        th,
        td {
            border: 1px solid #cbd5e1;
            padding: 8px 10px;
            text-align: left;
        }

        th {
            background: #eef2ff;
            font-weight: bold;
            color: #3730a3;
        }

        tbody tr:nth-child(even) {
            background: #f8fafc;
        }

        tbody tr:hover {
            background: #eef2ff;
        }

        /* Kolom foto */
        td img {
            width: 90px;
            height: 90px;
            object-fit: cover;
            border-radius: 6px;
            display: block;
        }

        .placeholder {
            display: inline-block;
            padding: 4px 8px;
            font-size: 12px;
            color: #64748b;
            background: #f1f5f9;
            border: 1px dashed #cbd5e1;
            border-radius: 6px;
        }

        /* Form tambah data */
        .form-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(210px, 1fr));
            gap: 14px;
        }

        .field label {
            display: block;
            margin-bottom: 5px;
            font-size: 13px;
            color: #334155;
        }

        .field input,
        .field select {
            width: 100%;
            padding: 8px 10px;
            font-size: 14px;
            font-family: inherit;
            color: #0f172a;
            background: #ffffff;
            border: 1px solid #cbd5e1;
            border-radius: 6px;
        }

        .field input:focus,
        .field select:focus {
            outline: none;
            border-color: #6366f1;
            box-shadow: 0 0 0 3px rgba(99, 102, 241, 0.15);
        }

        button {
            margin-top: 16px;
            padding: 10px 20px;
            font-size: 14px;
            font-family: inherit;
            color: #ffffff;
            background: #4f46e5;
            border: none;
            border-radius: 6px;
            cursor: pointer;
        }

        button:hover {
            background: #4338ca;
        }

        /* Pesan error merah dan pesan sukses hijau */
        .pesan {
            margin-bottom: 16px;
            padding: 10px 14px;
            border-radius: 6px;
            font-size: 14px;
        }

        .pesan-error {
            color: #b91c1c;
            background: #fef2f2;
            border: 1px solid #fecaca;
        }

        .pesan-error ul {
            margin: 0;
            padding-left: 18px;
        }

        .pesan-sukses {
            color: #15803d;
            background: #f0fdf4;
            border: 1px solid #bbf7d0;
        }

        .footer {
            text-align: center;
            margin-top: 6px;
        }

        .footer p {
            margin: 0;
            font-size: 13px;
            color: #64748b;
        }
    </style>
</head>
<body>
    <div class="container">
        <header class="header">
            <h1>WELCOME TO PRODUK MANAGEMENT</h1>
            <p>Daftar produk Jaket yang tersimpan</p>
        </header>

        <main class="card">
            <h2>TAMBAH JAKET</h2>

            <?php if (count($errors) > 0): ?>
                <div class="pesan pesan-error">
                    <ul>
<?php foreach ($errors as $pesan): ?>
                        <li><?= htmlspecialchars($pesan) ?></li>
<?php endforeach; ?>
                    </ul>
                </div>
            <?php endif; ?>

            <?php if ($sukses !== ""): ?>
                <div class="pesan pesan-sukses"><?= htmlspecialchars($sukses) ?></div>
            <?php endif; ?>

            <form method="post" action="">
                <div class="form-grid">
                    <div class="field">
                        <label for="id_produk">ID Produk</label>
                        <input type="text" id="id_produk" name="id_produk"
                               value="<?= htmlspecialchars($form["id_produk"]) ?>">
                    </div>
                    <div class="field">
                        <label for="merk">Merk</label>
                        <input type="text" id="merk" name="merk"
                               value="<?= htmlspecialchars($form["merk"]) ?>">
                    </div>
                    <div class="field">
                        <label for="harga">Harga</label>
                        <input type="text" id="harga" name="harga"
                               value="<?= htmlspecialchars($form["harga"]) ?>">
                    </div>
                    <div class="field">
                        <label for="ukuran">Ukuran</label>
                        <input type="text" id="ukuran" name="ukuran"
                               value="<?= htmlspecialchars($form["ukuran"]) ?>">
                    </div>
                    <div class="field">
                        <label for="bahan">Bahan</label>
                        <input type="text" id="bahan" name="bahan"
                               value="<?= htmlspecialchars($form["bahan"]) ?>">
                    </div>
                    <div class="field">
                        <label for="warna">Warna</label>
                        <input type="text" id="warna" name="warna"
                               value="<?= htmlspecialchars($form["warna"]) ?>">
                    </div>
                    <div class="field">
                        <label for="jenis_penutup">Jenis Penutup</label>
                        <input type="text" id="jenis_penutup" name="jenis_penutup"
                               value="<?= htmlspecialchars($form["jenis_penutup"]) ?>">
                    </div>
                    <div class="field">
                        <label for="kupluk">Kupluk</label>
                        <select id="kupluk" name="kupluk">
                            <?php // Nilai yang dikirim tetap true atau false, yang ditampilkan ditulis dalam bahasa Indonesia ?>
                            <option value="true" <?= $form["kupluk"] === "true" ? "selected" : "" ?>>ada</option>
                            <option value="false" <?= $form["kupluk"] === "false" ? "selected" : "" ?>>tidak ada</option>
                        </select>
                    </div>
                    <div class="field">
                        <label for="jumlah_saku">Jumlah Saku</label>
                        <input type="text" id="jumlah_saku" name="jumlah_saku"
                               value="<?= htmlspecialchars($form["jumlah_saku"]) ?>">
                    </div>
                    <div class="field">
                        <label for="foto">Path Foto</label>
                        <input type="text" id="foto" name="foto"
                               value="<?= htmlspecialchars($form["foto"]) ?>"
                               placeholder="assets/image1.png">
                    </div>
                </div>
                <button type="submit">Tambah Data</button>
            </form>
        </main>

        <main class="card">
            <h2>DAFTAR JAKET (<?= count($daftar) ?>)</h2>

            <div class="tabel-wrap">
                <table>
                    <thead>
                        <tr>
<?php foreach ($judul as $kolom): ?>
                            <th><?= htmlspecialchars($kolom) ?></th>
<?php endforeach; ?>
                        </tr>
                    </thead>
                    <tbody>
<?php foreach ($daftar as $jaket): ?>
<?php     $isi = selJaket($jaket); ?>
                        <tr>
<?php     foreach ($isi as $sel): ?>
                            <td><?= $sel ?></td>
<?php     endforeach; ?>
                        </tr>
<?php endforeach; ?>
                    </tbody>
                </table>
            </div>
        </main>

        <footer class="footer">
            <p>Tugas Praktikum DPBO &mdash; Program Management</p>
        </footer>
    </div>
</body>
</html>
