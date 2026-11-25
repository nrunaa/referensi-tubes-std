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

    if (findToko(L, X.idToko) != Nil) {
        cout << "ID toko " << X.idToko << " sudah dipakai." << endl;
    } else {
        T = alokasiToko(X);
        insertLastToko(L, T);
        cout << "Toko " << X.nama << " berhasil ditambahkan." << endl;
    }
}

void hapusProduk(listToko &L, BinTree &root, string kode){
    adrToko T;
    adrProduk P;

    P = findProdukMarketplace(L, kode, T);

    if (P == Nil) {
        cout << "Produk " << kode << " tidak ditemukan." << endl;
    } else {
        root = deleteBST(root, buatIndeks(P, T));
        lepasProduk(T->lProduk, P);
        cout << "Produk " << P->info.nama << " dihapus." << endl;
        dealokasiProduk(P);
    }
}

void hapusToko(listToko &L, BinTree &root, string idToko){
    adrToko T;
    adrProduk P;
    int n;

    T = findToko(L, idToko);
    n = 0;

    if (T == Nil) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else {
        while (!isEmptyProduk(T->lProduk)) {
            P = (T->lProduk).first;
            root = deleteBST(root, buatIndeks(P, T));
            deleteFirstProduk(T->lProduk, P);
            dealokasiProduk(P);
            n++;
        }

        lepasToko(L, T);
        cout << "Toko " << T->info.nama << " dan " << n << " produknya dihapus." << endl;
        dealokasiToko(T);
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

void tambahProduk(listToko &L, BinTree &root, string idToko, infotypeProduk X){
    adrToko T, pemilik;
    adrProduk P;

    T = findToko(L, idToko);

    if (T == Nil) {
        cout << "Toko " << idToko << " tidak ditemukan." << endl;
    } else if (findProdukMarketplace(L, X.kode, pemilik) != Nil) {
        cout << "Kode produk " << X.kode << " sudah dipakai oleh toko ";
        cout << pemilik->info.nama << "." << endl;
    } else {
        P = alokasiProduk(X);
        insertLastProduk(T->lProduk, P);
        insertBST(buatIndeks(P, T), root);
        cout << "Produk " << X.nama << " ditambahkan ke toko ";
        cout << T->info.nama << "." << endl;
    }
}

void hapusProdukStokNol(){
    adrToko T;
    adrProduk P, Q;
    int n;

    T = findToko(listToko L, string idToko);

    if (T == nullptr) {
        cout<<"Toko " << idToko << "tidak ditemukan"<< endl;
    } else {
        P = (T->1Produk).first;
        while (P != nullptr) {
            Q = P-> next
            if (P->info.stok == 0) {
                cout<< " menghapus " << P->info.kode << " - " << P->info.nama<< endl;
                root = deleteBST(root, buatIndeks(P, T));
                lepasProduk(T->lProduk, P);
                dealokasiProduk(P);
                n++; 
            }
            P = Q;   
        }
        cout << n << " produk ber-stok 0 dihapus dari toko " << T->info.nama << "." << endl;
    }
}

