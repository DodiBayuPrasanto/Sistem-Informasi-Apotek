#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct obat {
    char nama_obat[100];
    int stok;
    int harga;
    obat* next;
};

obat* head = nullptr;

void tampilkan_menu();
void tambahObat();
void tampilkanDataObat();
void ubahObat();
void hapusObat();
void cariObat();
void simpanObat_txt();
void muatDataObat_txt();

int main(){
    muatDataObat_txt();
    tampilkan_menu();
    return 0;
}

void tampilkan_menu(){
    int pilihan;
    do{
        cout << "                SISTEM INFORMASI APOTEK         " <<endl;
        cout << "1. Tambah data obat" <<endl;
        cout << "2. Tampilkan data obat" <<endl;
        cout << "3. Ubah data obat" <<endl;
        cout << "4. Hapus data obat" <<endl;
        cout << "5. Cari data obat" <<endl;
        cout << "6. Keluar" <<endl;
        cout << "Masukan pilihan: ";
        cin >> pilihan;
        cout << endl;

        switch(pilihan){
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
            cout << "Terimakasih!  " <<endl;
            break;
            default:
            cout << "Pilihan yang dimasukan salah!!!" <<endl <<endl;
        }
    }while(pilihan != 6);
}

void tambahObat(){
        obat* o = new obat;
        cout << "Masukan nama obat: ";
        cin.ignore();
        cin.getline(o->nama_obat, sizeof(o->nama_obat));
        cout << "Masukan stok obat: ";
        cin >> o->stok;
        cout << "Masukan harga obat: ";
        cin >> o->harga;
        o->next = nullptr;
        if(head == nullptr){
            head = o;
        }else{
            obat* current = head;
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = o;
        }
        cout << "Data obat berhasil ditambahkan!!!" <<endl; 
        cout << endl;
    }

void tampilkanDataObat(){
    if(head == nullptr){  
        cout << "Belum ada data yang dimasukan!!!" <<endl;
    }else{
      cout << "========== DATA OBAT ==========" <<endl;
      cout << "NO.\tNama Obat\tStok\tHarga" <<endl;
      obat* current = head;
      int nomor = 1;
      while(current != nullptr){
        cout << nomor << "\t" << current->nama_obat << "\t\t" << current->stok << "\t" << current->harga << endl;
        current = current->next;
        nomor++;
      }
    }

    cout << endl;
}

void ubahObat(){
    if(head == nullptr){
        cout << "Belum ada data obat yang dimasukan!!!";
        return;
    }
    
        int nomor_obat;
        cout << "Masukan nomor obat yang ingin diubah: ";
        cin >> nomor_obat;
        obat* current = head;
        int nomor = 1;
        while(current != nullptr && nomor != nomor_obat){
            current = current->next;
            nomor++;
        }

        if(current != nullptr){
            cout << "Nama Obat: " << current->nama_obat <<endl; 
            cout << "Stok Obat: " << current->stok <<endl;
            cout << "Harga Obat: " << current->harga <<endl;

            cout << "Masukan nama obat baru: ";
            cin.ignore();
            cin.getline(current->nama_obat, sizeof(current->nama_obat));
            cout << "Masukan stok obat baru: ";
            cin >> current->stok;
            cout << "Masukan harga obat baru: ";
            cin >> current->harga;

            cout << "Data obat berhasil diubah!!!";
        }else{
            cout << "Nomor obat yang dimasukan salah!, Coba lagi....";
        }
        cout << endl;
    }
        
void hapusObat(){
    if(head == nullptr){
        cout << "Belum ada data obat yang dimasukan!!!" <<endl;
        return;
    }

     int nomor_obat;
     cout << "Masukan nomor obat yang ingin dihapus: ";
     cin >> nomor_obat;

    if(nomor_obat == 1){
       obat* temp = head;
       head = head->next;
       delete temp;
       cout << "Data obat berhasil dihapus!!!" << endl;
       return;
    }
    obat* current = head;
    int nomor = 1;
    while(current != nullptr && nomor != nomor_obat - 1){
        current = current->next;
        nomor++;
    }

       if(current != nullptr && current->next != nullptr){
         obat* temp = current->next;
         current->next = current->next->next;
         delete temp;  
         cout << "Data obat berhasil dihapus!!!" << endl;
        }else{
            cout << "Nomor obat yang anda masukan salah!! Cobalagi....." <<endl;
        }
        cout << endl;
    }

void cariObat(){
    if(head == nullptr){
        cout << "Belum ada data obat yang diamasukan!!!" <<endl;
        return;
    }

        char keyword[100];
         cout << "Masukan nama obat yang ingin diacari: ";
         cin.ignore();
         cin.getline(keyword, sizeof(keyword));
         cout << "========== HASIL PENCARIAN ==========" <<endl;
         cout << "NO.\tNama Obat\tStok\tHarga" << endl;
         obat* current = head;
         int count = 0;
         int nomor = 1;
         while(current != nullptr){
            if(strstr(current->nama_obat,keyword)){
                count++;
                cout << nomor << "\t" << current->nama_obat << "\t\t" << current->stok << "\t" << current->harga << endl;
            }
            current = current->next;
            nomor++;
         }

         if(count == 0){
            cout << "Obat tidak ditemukan!!!" << endl;
         }

    cout << endl;
}

void simpanObat_txt(){
    int jumlahObat = 0;
    obat* current = head;
    while(current != nullptr){
        jumlahObat++;
        current = current->next;
    }

    ofstream fout;
    fout.open("data_obat.txt");
    fout << jumlahObat <<endl;
    current = head;
    while(current != nullptr){
        fout << current->nama_obat <<endl;
        fout << current->stok <<endl;
        fout << current->harga <<endl;
        current = current->next;
    }
   
    fout.close();
    cout << "Data obat berhasil disimpan ke dalam file data_Obat.txt" <<endl;

    cout << endl;
}

void muatDataObat_txt(){
    int jumlahObat;
    ifstream fin;
    fin.open("data_obat.txt");
    if(fin.is_open()){
        fin >> jumlahObat;
        fin.ignore();
        obat* previous = nullptr;
        for(int i = 0; i < jumlahObat; i++){
            obat* o = new obat;
            fin.getline(o->nama_obat, sizeof(o->nama_obat));
            fin >> o->stok;
            fin >> o->harga;
            fin.ignore();
            o->next = nullptr;

            if(previous == nullptr){
                head = o;
            }else{
                previous->next = o;
            }
            previous = o;
        }
        cout << "File data obat ditemukan!!!" <<endl;
    }else{
        cout << "File data obat tidak ditemukan!!!" <<endl;
    }
    fin.close();

    cout << endl;
}






