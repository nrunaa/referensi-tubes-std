#include "marketplace.h"

Infotype buatIndeks(adrProduk P, adrToko T){
    Infotype x;

    x.harga = P->info.harga;
    x.kode = P->info.kode;
    x.produk = P;
    x.toko = T;

    return x;
}

void tambahToko(listToko &L, infotypeToko X){
    adrToko T;

    if (findToko(L, X.idToko) != nullptr) {
        cout << "ID toko " << X.idToko << " sudah dipakai." << endl;
    } else {
        T = alokasiToko(X);
        createListProduk(T->lProduk);
        insertFirstToko(L, T);
        cout << "Toko " << X.nama << " berhasil ditambahkan." << endl;
    }
}

void tambahProduk(listToko &L, BinTree &root, string idToko, infotypeProduk X){
    adrToko T, pemilik;
    adrProduk P;

    T = findToko(L, idToko);

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else if (findProdukMarketplace(L, X.kode, pemilik) != nullptr) {
        cout << "Kode produk " << X.kode << " sudah dipakai oleh toko ";
        cout << pemilik->info.nama << "." << endl;
    } else if (X.harga <= 0 || X.stok < 0) {
        cout << "Harga harus > 0 dan stok tidak boleh negatif." << endl;
    } else {
        P = alokasiProduk(X);
        insertLastProduk(T->lProduk, P);
        insertBST(buatIndeks(P, T), root);
        cout << "Produk " << X.nama << " ditambahkan ke toko ";
        cout << T->info.nama << "." << endl;
    }
}

void hapusProduk(listToko &L, BinTree &root, string kode){
    adrToko T;
    adrProduk P;

    P = findProdukMarketplace(L, kode, T);

    if (P == nullptr) {
        cout << "Produk " << kode << " tidak ditemukan." << endl;
    } else {
        root = deleteBST(root, buatIndeks(P, T));
        lepasProduk(T->lProduk, P);
        cout << "Produk " << P->info.nama << " dihapus." << endl;
        delete P;
    }
}

void hapusToko(listToko &L, BinTree &root, string idToko){
    adrToko T;
    adrProduk P;
    int n;

    T = findToko(L, idToko);
    n = 0;

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else {
        while (!isEmptyProduk(T->lProduk)) {
            P = (T->lProduk).first;
            root = deleteBST(root, buatIndeks(P, T));
            deleteFirstProduk(T->lProduk, P);
            delete P;
            n++;
        }

        lepasToko(L, T);
        cout << "Toko " << T->info.nama << " dan " << n << " produknya dihapus." << endl;
        delete T;
    }
}

void hapusRelasi(listToko &L, BinTree &root, string idToko, string kode){
    adrToko T;
    adrProduk P;

    T = findToko(L, idToko);

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else {
        P = findProduk(T->lProduk, kode);

        if (P == nullptr) {
            cout << "Tidak ada relasi: produk " << kode << " bukan milik toko ";
            cout << T->info.nama << "." << endl;
        } else {
            root = deleteBST(root, buatIndeks(P, T));
            lepasProduk(T->lProduk, P);
            cout << "Relasi toko " << T->info.nama << " - produk " << P->info.nama;
            cout << " diputus. Karena satu produk hanya milik satu toko (MLL-00)," << endl;
            cout << "produknya ikut dihapus dari toko dan dari BST." << endl;
            delete P;
        }
    }
}

void cekRelasi(listToko L, string idToko, string kode){
    adrToko T, pemilik;
    adrProduk P;

    T = findToko(L, idToko);
    P = findProdukMarketplace(L, kode, pemilik);

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else if (P == nullptr) {
        cout << "Produk " << kode << " tidak ditemukan." << endl;
    } else if (pemilik == T) {
        cout << "BERELASI: produk " << P->info.nama << " dijual oleh toko ";
        cout << T->info.nama << "." << endl;
    } else {
        cout << "TIDAK berelasi: produk " << P->info.nama << " dijual oleh toko ";
        cout << pemilik->info.nama << ", bukan oleh " << T->info.nama << "." << endl;
    }
}

void tampilSatuToko(listToko L, string idToko){
    adrToko T;

    T = findToko(L, idToko);

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else {
        printToko(T);
        printListProduk(T->lProduk);
        cout << "   jumlah produk: " << nbProduk(T->lProduk) << endl;
    }
}

void cariProduk(listToko L, string kode){
    adrToko T;
    adrProduk P;

    P = findProdukMarketplace(L, kode, T);

    if (P == nullptr) {
        cout << "Produk " << kode << " tidak ditemukan." << endl;
    } else {
        cout << "Dijual oleh: ";
        printToko(T);
        printProduk(P);
    }
}

void tampilProdukBesertaToko(listToko L){
    adrToko T;
    adrProduk P;
    int n;

    T = L.first;
    n = 0;

    if (isEmptyToko(L)) {
        cout << "Marketplace masih kosong." << endl;
    }

    while (T != nullptr) {
        P = (T->lProduk).first;

        while (P != nullptr) {
            printProduk(P);
            cout << "        dijual oleh: [" << T->info.idToko << "] " << T->info.nama;
            cout << " (" << T->info.kota << ")" << endl;
            n++;
            P = P->next;
        }

        T = T->next;
    }

    if (n == 0 && !isEmptyToko(L)) {
        cout << "Belum ada produk." << endl;
    }
}

void tampilJumlahProdukToko(listToko L, string idToko){
    adrToko T;

    T = findToko(L, idToko);

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else {
        cout << "Toko " << T->info.nama << " memiliki " << nbProduk(T->lProduk);
        cout << " produk." << endl;
    }
}

void tampilJumlahTokoProduk(listToko L, string kode){
    adrToko T;
    int n;

    T = L.first;
    n = 0;

    while (T != nullptr) {
        if (findProduk(T->lProduk, kode) != nullptr) {
            n++;
        }

        T = T->next;
    }

    if (n == 0) {
        cout << "Produk " << kode << " tidak ditemukan di toko mana pun (0 toko)." << endl;
    } else {
        cout << "Produk " << kode << " dijual oleh " << n << " toko." << endl;
    }
}

void tampilInfoBST(BinTree root){
    if (isEmptyTree(root)) {
        cout << "BST kosong." << endl;
    } else {
        cout << "Minimum (termurah) :" << endl;
        printInfo((findMin(root))->info);
        cout << "Maksimum (termahal):" << endl;
        printInfo((findMax(root))->info);
        cout << "Tinggi pohon       : " << tinggiTree(root);
        cout << " (jumlah edge, root di level 0)" << endl;
        cout << "Jumlah node        : " << hitungNode(root) << endl;
    }
}

void cariProdukHarga(BinTree root, int harga){
    int jumlah;

    jumlah = 0;

    if (findHarga(harga, root) == nullptr) {
        cout << "Tidak ada produk dengan harga Rp" << harga << "." << endl;
    } else {
        cout << "Produk dengan harga Rp" << harga << ":" << endl;
        cariRentangHarga(root, harga, harga, jumlah);
        cout << "   ditemukan " << jumlah << " produk." << endl;
    }
}

void cariProdukRentangHarga(BinTree root, int hMin, int hMax){
    int jumlah;

    jumlah = 0;

    if (hMin > hMax) {
        cout << "Harga minimum lebih besar dari harga maksimum." << endl;
    } else {
        cout << "Produk dengan harga Rp" << hMin << " - Rp" << hMax << ":" << endl;
        cariRentangHarga(root, hMin, hMax, jumlah);

        if (jumlah == 0) {
            cout << "   (tidak ada produk pada rentang ini)" << endl;
        } else {
            cout << "   ditemukan " << jumlah << " produk." << endl;
        }
    }
}

void tampilTermurahTermahal(BinTree root){
    Address pMin, pMax;
    int jumlah;

    jumlah = 0;

    if (isEmptyTree(root)) {
        cout << "Belum ada produk di marketplace." << endl;
    } else {
        pMin = findMin(root);
        pMax = findMax(root);

        cout << "Produk TERMURAH (Rp" << pMin->info.harga << "):" << endl;
        cariRentangHarga(root, pMin->info.harga, pMin->info.harga, jumlah);

        jumlah = 0;

        cout << "Produk TERMAHAL (Rp" << pMax->info.harga << "):" << endl;
        cariRentangHarga(root, pMax->info.harga, pMax->info.harga, jumlah);
    }
}

void tampilTokoNilaiStokTertinggi(listToko L){
    adrToko T;

    if (isEmptyToko(L)) {
        cout << "Belum ada toko." << endl;
    } else {
        cout << "Total nilai stok tiap toko:" << endl;
        T = L.first;

        while (T != nullptr) {
            cout << "   " << T->info.nama << ": Rp" << totalNilaiStok(T->lProduk) << endl;
            T = T->next;
        }

        printTokoStokTertinggi(L);
    }
}

void hapusProdukStokNol(listToko &L, BinTree &root, string idToko){
    adrToko T;
    adrProduk P, Q;
    int n;

    T = findToko(L, idToko);
    n = 0;

    if (T == nullptr) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else {
        P = (T->lProduk).first;

        while (P != nullptr) {
            Q = P->next;

            if (P->info.stok == 0) {
                cout << "   menghapus " << P->info.kode << " - " << P->info.nama << endl;
                root = deleteBST(root, buatIndeks(P, T));
                lepasProduk(T->lProduk, P);
                delete P;
                n++;
            }

            P = Q;
        }

        cout << n << " produk ber-stok 0 dihapus dari toko " << T->info.nama << "." << endl;
    }
}

void bersihkanMarketplace(listToko &L, BinTree &root){
    adrToko T;
    adrProduk P;

    while (!isEmptyToko(L)) {
        deleteFirstToko(L, T);

        while (!isEmptyProduk(T->lProduk)) {
            P = (T->lProduk).first;
            root = deleteBST(root, buatIndeks(P, T));
            deleteFirstProduk(T->lProduk, P);
            delete P;
        }

        delete T;
    }

}