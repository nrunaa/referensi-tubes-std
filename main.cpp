#include <iostream>
#include "MLL.h"
#include "bst.h"
#include "marketplace.h"

using namespace std;

void isiDataContoh(listToko &L, BinTree &root){
    infotypeToko T;
    infotypeProduk P;

    T.idToko = "T01"; T.nama = "Toko_Maju"; T.kota = "Bandung"; T.rating = 4.8;
    tambahToko(L, T);
    T.idToko = "T02"; T.nama = "Gadget_Kita"; T.kota = "Jakarta"; T.rating = 4.5;
    tambahToko(L, T);
    T.idToko = "T03"; T.nama = "Rumah_Buku"; T.kota = "Kuningan"; T.rating = 4.9;
    tambahToko(L, T);

    P.kode = "P01"; P.nama = "Kemeja_Flanel"; P.kategori = "Fashion"; P.harga = 150000; P.stok = 20;
    tambahProduk(L, root, "T01", P);
    P.kode = "P02"; P.nama = "Sepatu_Lari"; P.kategori = "Fashion"; P.harga = 450000; P.stok = 0;
    tambahProduk(L, root, "T01", P);
    P.kode = "P03"; P.nama = "Topi_Baseball"; P.kategori = "Fashion"; P.harga = 75000; P.stok = 35;
    tambahProduk(L, root, "T01", P);
    P.kode = "P04"; P.nama = "Earphone_TWS"; P.kategori = "Elektronik"; P.harga = 350000; P.stok = 15;
    tambahProduk(L, root, "T02", P);
    P.kode = "P05"; P.nama = "Powerbank_10K"; P.kategori = "Elektronik"; P.harga = 200000; P.stok = 0;
    tambahProduk(L, root, "T02", P);
    P.kode = "P06"; P.nama = "Smartwatch"; P.kategori = "Elektronik"; P.harga = 1250000; P.stok = 8;
    tambahProduk(L, root, "T02", P);
    P.kode = "P07"; P.nama = "Novel_Fiksi"; P.kategori = "Buku"; P.harga = 95000; P.stok = 40;
    tambahProduk(L, root, "T03", P);
    P.kode = "P08"; P.nama = "Buku_Algoritma"; P.kategori = "Buku"; P.harga = 150000; P.stok = 12;
    tambahProduk(L, root, "T03", P);
}

void menu(){
    cout << endl;
    cout << "========== MARKETPLACE TOKO & PRODUK ==========" << endl;
    cout << "--- Fungsionalitas Umum ---" << endl;
    cout << " 1. Tambah toko" << endl;
    cout << " 2. Tambah produk ke toko" << endl;
    cout << " 3. Tampilkan semua toko & produk" << endl;
    cout << " 4. Tampilkan produk dari satu toko" << endl;
    cout << " 5. Cari produk berdasarkan kode" << endl;
    cout << " 6. Hapus produk" << endl;
    cout << " 7. Hapus toko beserta produknya" << endl;
    cout << " 8. Tampilkan isi BST (inorder, preorder, postorder)" << endl;
    cout << "--- Fungsionalitas Khusus ---" << endl;
    cout << " 9. Cari produk dalam rentang harga (BST)" << endl;
    cout << "10. Tampilkan produk termurah & termahal" << endl;
    cout << "11. Hapus semua produk stok 0 dari toko tertentu" << endl;
    cout << " 0. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main(){
    listToko L;
    BinTree root;
    infotypeToko dataToko;
    infotypeProduk dataProduk;
    adrToko T;
    adrProduk P;
    string id, kode;
    int pilihan, hMin, hMax;
    char jawab;

    createListToko(L);
    createTree(root);

    cout << "Catatan: input teks tidak boleh mengandung spasi, gunakan '_' (contoh: Toko_Maju)" << endl;
    cout << "Muat data contoh? (y/n): ";
    cin >> jawab;

    if (jawab == 'y' || jawab == 'Y') {
        isiDataContoh(L, root);
    }

    do {
        menu();
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
        case 1:
            cout << "Masukkan ID toko: ";
            cin >> dataToko.idToko;
            cout << "Masukkan nama toko: ";
            cin >> dataToko.nama;
            cout << "Masukkan kota: ";
            cin >> dataToko.kota;
            cout << "Masukkan rating: ";
            cin >> dataToko.rating;

            tambahToko(L, dataToko);
            break;
        case 2:
            cout << "Masukkan ID toko: ";
            cin >> id;
            cout << "Masukkan kode produk: ";
            cin >> dataProduk.kode;
            cout << "Masukkan nama produk: ";
            cin >> dataProduk.nama;
            cout << "Masukkan kategori: ";
            cin >> dataProduk.kategori;
            cout << "Masukkan harga: ";
            cin >> dataProduk.harga;
            cout << "Masukkan stok: ";
            cin >> dataProduk.stok;

            if (dataProduk.harga <= 0 || dataProduk.stok < 0) {
                cout << "Harga harus lebih dari 0 dan stok tidak boleh negatif." << endl;
            } else {
                tambahProduk(L, root, id, dataProduk);
            }
            break;
        case 3:
            printAll(L);
            cout << "Jumlah produk (node BST): " << hitungNode(root) << endl;
            break;
        case 4:
            cout << "Masukkan ID toko: ";
            cin >> id;

            T = findToko(L, id);

            if (T == nullptr) {
                cout << "Toko " << id << " tidak ditemukan." << endl;
            } else {
                printToko(T);
                printListProduk(T->lProduk);
            }
            break;
        case 5:
            cout << "Masukkan kode produk: ";
            cin >> kode;

            P = findProdukMarketplace(L, kode, T);

            if (P == nullptr) {
                cout << "Produk " << kode << " tidak ditemukan." << endl;
            } else {
                cout << "Dijual oleh: ";
                printToko(T);
                printProduk(P);
            }
            break;
        case 6:
            cout << "Masukkan kode produk: ";
            cin >> kode;

            hapusProduk(L, root, kode);
            break;
        case 7:
            cout << "Masukkan ID toko: ";
            cin >> id;

            hapusToko(L, root, id);
            break;
        case 8:
            if (isEmptyTree(root)) {
                cout << "BST kosong." << endl;
            } else {
                cout << "InOrder (harga naik):" << endl;
                inOrder(root);
                cout << "PreOrder:" << endl;
                preOrder(root);
                cout << "PostOrder:" << endl;
                postOrder(root);
            }
            break;
        case 9:
            cout << "Masukkan harga minimum: ";
            cin >> hMin;
            cout << "Masukkan harga maksimum: ";
            cin >> hMax;

            cariProdukRentangHarga(root, hMin, hMax);
            break;
        case 10:
            tampilTermurahTermahal(root);
            break;
        case 11:
            cout << "Masukkan ID toko: ";
            cin >> id;

            hapusProdukStokNol(L, root, id);
            break;
        case 0:
            cout << "Terima kasih." << endl;
            break;
        default:
            cout << "Menu tidak tersedia." << endl;
        }
    } while (pilihan != 0);

    return 0;
}