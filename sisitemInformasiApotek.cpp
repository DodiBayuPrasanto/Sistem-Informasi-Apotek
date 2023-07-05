#include <iostream>
#include <fstream> //berfungsi unutk input/output pada file
#include <cstring> //berfungsi untuk operasi terkait string, mencari substring
#include <vector>  //berfungsi untuk menggunaan container vector
#include <string>  //berfungsi untuk menggunakan tipe data string.

using namespace std;

struct obat{
    char nama_obat[100];
    int stok;
    int harga;
    obat *next;
};

class Stack{
private:
    static const int MAX_SIZE = 100;
    obat *stack[MAX_SIZE];
    int top;

public:
    Stack(){
        top = -1;
    }

    bool isEmpty(){
        return (top == -1);
    }

    bool isFull(){
        return (top == MAX_SIZE - 1);
    }

    void push(obat *data){
        if (isFull()){
            cout << "Stack penuh!" << endl;
        }else{
            stack[++top] = data;
        }
    }

    obat *pop(){
        if (isEmpty()){
            cout << "Stack kosong!" << endl;
            return nullptr;
        }else{
            return stack[top--];
        }
    }

    int getSize(){
        return top + 1;
    }
};

Stack dataStack;

void tampilkan_menu();
void tambahObat();
void tampilkanDataObat();
void ubahObat();
void hapusObat();
void cariObat() ;
void rakObat();
void simpanObat_txt();
void muatDataObat_txt();
void rakObat();

class Graph{
private:
    int vertices;
    vector<vector<int>> graph;
    vector<string> nodeNames;

public:
    Graph(int vertices){
        this->vertices = vertices;
        graph.resize(vertices, vector<int>(vertices, 0));
        nodeNames.resize(vertices);
    }

    void addEdge(int source, int destination, int weight){
        graph[source][destination] = weight;
    }

    void printGraph(){
        cout << "      ";
        for (int i = 0; i < vertices; ++i){
            cout << nodeNames[i] << "     ";
        }
        cout << endl;

        for (int i = 0; i < vertices; ++i){
            cout << nodeNames[i] << "     ";
            for (int j = 0; j < vertices; ++j)
            {
                cout << graph[i][j] << "         ";
            }
            cout << endl;
        }
    }

    void setNodeNames(const vector<string> &names){
        nodeNames = names;
    }
};

int main(){
    muatDataObat_txt();
    tampilkan_menu();
    return 0;
}

void tampilkan_menu(){
    int pilihan;
    do{
        cout << "                SISTEM INFORMASI APOTEK         " << endl;
        cout << "1. Tambah data obat" << endl;
        cout << "2. Tampilkan data obat" << endl;
        cout << "3. Ubah data obat" << endl;
        cout << "4. Hapus data obat" << endl; 
        cout << "5. Cari data obat" << endl;
        cout << "6. Ambil Stok obat" << endl;
        cout << "7. Keluar" << endl;
        cout << "Masukan pilihan: ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan){
        case 1:
            tambahObat();
            simpanObat_txt();
            break;
        case 2:
            tampilkanDataObat();
            simpanObat_txt();
            break;
        case 3:
            ubahObat();
            simpanObat_txt();
            break;
        case 4:
            hapusObat(); 
            simpanObat_txt();
            break;
        case 5:
            cariObat();
            break;
        case 6:
            rakObat();
            break;
        case 7:
            cout << "Terimakasih!  " << endl;
            break;
        default:
            cout << "Pilihan yang dimasukan salah!!!" << endl
                 << endl;
        }
    } while (pilihan != 7);
}

void tambahObat(){
    obat *o = new obat;
    cout << "Masukan nama obat: ";
    cin.ignore();
    cin.getline(o->nama_obat, sizeof(o->nama_obat));
    cout << "Masukan stok obat: ";
    cin >> o->stok;
    cout << "Masukan harga obat: ";
    cin >> o->harga;
    dataStack.push(o);
    cout << "Data obat berhasil ditambahkan!!!" << endl;
    cout << endl;
}

void tampilkanDataObat(){
    if (dataStack.isEmpty()){
        cout << "Belum ada data yang dimasukan!!!" << endl;
    }else{
        cout << "===================== DATA OBAT =======================" << endl;
        cout << "NO.\tNama Obat\t\tStok\t\tHarga" << endl;

        Stack tempStack;
        int nomor = 1;
        while (!dataStack.isEmpty()){
            obat *current = dataStack.pop();
            cout << nomor << "\t" << current->nama_obat << "\t\t\t" << current->stok << "\t\t" << current->harga << endl;
            tempStack.push(current);
            nomor++;
        }

        while (!tempStack.isEmpty()){
            obat *temp = tempStack.pop();
            dataStack.push(temp);
        }
    }
    cout << endl;
}

void ubahObat(){
    if (dataStack.isEmpty()){
        cout << "Belum ada data obat yang dimasukan!!!" << endl;
        return;
    }

    int nomor_obat;
    cout << "Masukan nomor obat yang ingin diubah: ";
    cin >> nomor_obat;

    Stack tempStack;
    obat *current = nullptr;
    int nomor = 1;
    while (!dataStack.isEmpty() && nomor != nomor_obat){
        obat *temp = dataStack.pop();
        tempStack.push(temp);
        nomor++;
    }

    if (!dataStack.isEmpty()){
        current = dataStack.pop();
        cout << "Nama Obat: " << current->nama_obat << endl;
        cout << "Stok Obat: " << current->stok << endl;
        cout << "Harga Obat: " << current->harga << endl;

        cout << "Masukan nama obat baru: ";
        cin.ignore();
        cin.getline(current->nama_obat, sizeof(current->nama_obat));
        cout << "Masukan stok obat baru: ";
        cin >> current->stok;
        cout << "Masukan harga obat baru: ";
        cin >> current->harga;

        cout << "Data obat berhasil diubah!!!" << endl;

        while (!tempStack.isEmpty()){
            obat *temp = tempStack.pop();
            dataStack.push(temp);
        }

        dataStack.push(current);
    }else{
        cout << "Nomor obat yang dimasukan salah!, Coba lagi...." << endl;
    }
    cout << endl;
}

void hapusObat(){
    if (dataStack.isEmpty()){
        cout << "Belum ada data obat yang dimasukan!!!" << endl;
        return;
    }

    Stack tempStack;

    // Pindahkan elemen-elemen dari dataStack ke tempStack
    // sampai hanya satu elemen yang tersisa di dataStack
    while (dataStack.getSize() > 1){
        obat *temp = dataStack.pop();
        tempStack.push(temp);
    }

    obat *current = dataStack.pop(); // Hapus data paling bawah

    cout << "Data obat yang dihapus:" << endl;
    cout << "Nama Obat: " << current->nama_obat << endl;
    cout << "Stok Obat: " << current->stok << endl;
    cout << "Harga Obat: " << current->harga << endl;
    cout << endl;
    cout << "Data obat berhasil dihapus!!!" << endl;

    delete current;

    // Kembalikan elemen-elemen yang sebelumnya dipindahkan ke tempStack ke dataStack
    while (!tempStack.isEmpty()){
        obat *temp = tempStack.pop();
        dataStack.push(temp);
    }

    cout << endl;
}

void cariObat(){
    if (dataStack.isEmpty()){
        cout << "Belum ada data obat yang dimasukan!!!" << endl;
        return;
    }

    char keyword[100];
    cout << "Masukan nama obat yang ingin diacari: ";
    cin.ignore();
    cin.getline(keyword, sizeof(keyword));
    cout << "========== HASIL PENCARIAN ==========" << endl;
    cout << "NO.\tNama Obat\tStok\tHarga" << endl;

    Stack tempStack;
    obat *current = nullptr;
    int count = 0;
    int nomor = 1;
    while (!dataStack.isEmpty()){
        current = dataStack.pop();
        if (strstr(current->nama_obat, keyword)){
            count++;
            cout << nomor << "\t" << current->nama_obat << "\t\t" << current->stok << "\t" << current->harga << endl;
        }
        tempStack.push(current);
        nomor++;
    }

    while (!tempStack.isEmpty()){
        obat *temp = tempStack.pop();
        dataStack.push(temp);
    }

    if (count == 0){
        cout << "Obat tidak ditemukan!!!" << endl;
    }

    cout << endl;
}

void simpanObat_txt(){
    if (dataStack.isEmpty()){
        cout << "Belum ada data obat yang dimasukan!!!" << endl;
        return;
    }

    ofstream fout;
    fout.open("data_obat.txt");
    fout << dataStack.getSize() << endl;

    Stack tempStack;
    while (!dataStack.isEmpty()){
        obat *current = dataStack.pop();
        fout << current->nama_obat << endl;
        fout << current->stok << endl;
        fout << current->harga << endl;
        tempStack.push(current);
    }

    while (!tempStack.isEmpty()){
        obat *temp = tempStack.pop();
        dataStack.push(temp);
    }

    fout.close();
    cout << "Data obat berhasil disimpan ke dalam file data_obat.txt" << endl;

    cout << endl;
}

void rakObat(){
    cout << endl;
    int rak;
    cout << "Masukan jumlah simpul: ";
    cin >> rak;

    Graph graph(rak);
    cout << endl;

    vector<string> nodeNames(rak);
    for(int i = 0; i < rak; i++){
        cout << "Masukan Nama Kota Ke-" << i + 1 << ": ";
        cin >> nodeNames[i];
    }
    graph.setNodeNames(nodeNames);
    cout << endl;

    for(int i = 0; i < rak; i++){
        for(int j = 0; j < rak; j++){
            int jarak;
            cout << "Masukan Jarak " << nodeNames[i] << " ke " << nodeNames[j] << ": ";
            cin >> jarak;
            graph.addEdge(i, j, jarak);
        }
    }
    cout << endl;
    cout << "Rak Obat" <<endl;
    cout << "-----------------------------------------" <<endl;
    graph.printGraph();

    cout << endl;
    cout << endl;
    tampilkan_menu();

    cout << endl;
}

void muatDataObat_txt(){
    ifstream fin;
    fin.open("data_obat.txt");
    if (fin.is_open()){
        int jumlahObat;
        fin >> jumlahObat;
        fin.ignore();

        Stack tempStack;
        for (int i = 0; i < jumlahObat; i++){
            obat *o = new obat;
            fin.getline(o->nama_obat, sizeof(o->nama_obat));
            fin >> o->stok;
            fin >> o->harga;
            fin.ignore();
            o->next = nullptr;
            tempStack.push(o);
        }

        while (!tempStack.isEmpty()){
            obat *temp = tempStack.pop();
            dataStack.push(temp);
        }

        cout << "File data obat ditemukan!!!" << endl;
    }else{
        cout << "File data obat tidak ditemukan!!!" << endl;
    }
    fin.close();

    cout << endl;
}