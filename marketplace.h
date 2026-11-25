#ifndef MARKETPLACE_H_INCLUDED
#define MARKETPLACE_H_INCLUDED

#include "mll.h"
#include "bst.h"

#define MAX_KATEGORI 50

Infotype buatIndeks(adrProduk P, adrToko T);
void tambahToko(listToko &L, infotypeToko X);
void hapusProduk(listToko &L, BinTree &root, string kode);
void hapusToko(listToko &L, BinTree &root, string idToko);
void tampilTermurahTermahal(BinTree root);
void cariProdukRentangHarga(BinTree root, int hMin, int hMax);
void tambahProduk(listToko &L, BinTree &root, string idToko, infotypeProduk X);
void hapusProdukStokNol(listToko &L, BinTree &root, string idToko);

#endif // MARKETPLACE_H_INCLUDED
