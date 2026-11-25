#include "bst.h"

void createTree(BinTree &root){
    root = nullptr;
}

bool isEmptyTree(BinTree root){
    return root == nullptr;
}

bool lebihKecil(Infotype a, Infotype b){
    return (a.harga < b.harga) || (a.harga == b.harga && a.kode < b.kode);
}

bool lebihBesar(Infotype a, Infotype b){
    return (a.harga > b.harga) || (a.harga == b.harga && a.kode > b.kode);
}

bool sama(Infotype a, Infotype b){
    return a.harga == b.harga && a.kode == b.kode;
}

Address createNode(Infotype x){
    Address N;

    N = new Node;
    N->info = x;
    N->left = nullptr;
    N->right = nullptr;

    return N;
}

void deallocate(Address &N){
    delete N;
    N = nullptr;
}

void insertBST(Infotype x, BinTree &N){
    if (N == nullptr) {
        N = createNode(x);
    } else if (lebihKecil(x, N->info)) {
        insertBST(x, N->left);
    } else if (lebihBesar(x, N->info)) {
        insertBST(x, N->right);
    } else {
        cout << "duplicate" << endl;
    }
}

Address findNode(Infotype x, BinTree N){
    Address hasil;

    if (N == nullptr || sama(x, N->info)) {
        hasil = N;
    } else if (lebihKecil(x, N->info)) {
        hasil = findNode(x, N->left);
    } else {
        hasil = findNode(x, N->right);
    }

    return hasil;
}

Address findHarga(int harga, BinTree N){
    Address hasil;

    if (N == nullptr || N->info.harga == harga) {
        hasil = N;
    } else if (harga < N->info.harga) {
        hasil = findHarga(harga, N->left);
    } else {
        hasil = findHarga(harga, N->right);
    }

    return hasil;
}

Address findMin(BinTree root){
    Address min;

    min = root;

    if (min != nullptr) {
        while (min->left != nullptr) {
            min = min->left;
        }
    }

    return min;
}

Address findMax(BinTree root){
    Address max;

    max = root;

    if (max != nullptr) {
        while (max->right != nullptr) {
            max = max->right;
        }
    }

    return max;
}

BinTree deleteBST(BinTree root, Infotype x){
    Address temp;

    if (root != nullptr) {
        if (lebihKecil(x, root->info)) {
            root->left = deleteBST(root->left, x);
        } else if (lebihBesar(x, root->info)) {
            root->right = deleteBST(root->right, x);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                deallocate(root);
            } else if (root->right == nullptr) {
                temp = root;
                root = root->left;
                deallocate(temp);
            } else if (root->left == nullptr) {
                temp = root;
                root = root->right;
                deallocate(temp);
            } else {
                temp = findMin(root->right);
                root->info = temp->info;
                root->right = deleteBST(root->right, temp->info);
            }
        }
    }

    return root;
}

void printInfo(Infotype x){
    cout << "   Rp" << x.harga << " | " << x.kode;
    cout << " | " << (x.produk)->info.nama;
    cout << " | " << (x.produk)->info.kategori;
    cout << " | stok: " << (x.produk)->info.stok;
    cout << " | toko: " << (x.toko)->info.nama << endl;
}

void preOrder(BinTree root){
    if (root != nullptr) {
        printInfo(root->info);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(BinTree root){
    if (root != nullptr) {
        inOrder(root->left);
        printInfo(root->info);
        inOrder(root->right);
    }
}

void postOrder(BinTree root){
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        printInfo(root->info);
    }
}

void cariRentangHarga(BinTree root, int hMin, int hMax, int &jumlah){
    if (root != nullptr) {
        if (root->info.harga >= hMin) {
            cariRentangHarga(root->left, hMin, hMax, jumlah);
        }

        if (root->info.harga >= hMin && root->info.harga <= hMax) {
            printInfo(root->info);
            jumlah++;
        }

        if (root->info.harga <= hMax) {
            cariRentangHarga(root->right, hMin, hMax, jumlah);
        }
    }
}

int hitungNode(BinTree root){
    int n;

    if (root == nullptr) {
        n = 0;
    } else {
        n = 1 + hitungNode(root->left) + hitungNode(root->right);
    }

    return n;
}

int tinggiTree(BinTree root){
    int kiri, kanan, t;

    if (root == nullptr) {
        t = -1;
    } else {
        kiri = tinggiTree(root->left);
        kanan = tinggiTree(root->right);

        if (kiri > kanan) {
            t = 1 + kiri;
        } else {
            t = 1 + kanan;
        }
    }

    return t;
}
