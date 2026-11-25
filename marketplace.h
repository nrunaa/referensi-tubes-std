#ifndef MARKETPLACE_H_INCLUDED
#define MARKETPLACE_H_INCLUDED

#include "MLL.h"
#include "bst.h"

Infotype buatIndeks(adrProduk P, adrToko T);

void tambahToko(listToko &L, infotypeToko X);

void tambahProduk(listToko &L, BinTree &root, string idToko, infotypeProduk X);

void hapusProduk(listToko &L, BinTree &root, string kode);

void hapusToko(listToko &L, BinTree &root, string idToko);

void hapusRelasi(listToko &L, BinTree &root, string idToko, string kode);

void cekRelasi(listToko L, string idToko, string kode);

void tampilSatuToko(listToko L, string idToko);

void cariProduk(listToko L, string kode);

void tampilProdukBesertaToko(listToko L);

void tampilJumlahProdukToko(listToko L, string idToko);

void tampilJumlahTokoProduk(listToko L, string kode);

void tampilInfoBST(BinTree root);

void cariProdukHarga(BinTree root, int harga);

void cariProdukRentangHarga(BinTree root, int hMin, int hMax);

void tampilTermurahTermahal(BinTree root);

void tampilTokoNilaiStokTertinggi(listToko L);

void hapusProdukStokNol(listToko &L, BinTree &root, string idToko);

void bersihkanMarketplace(listToko &L, BinTree &root);

#endif // MARKETPLACE_H_INCLUDED