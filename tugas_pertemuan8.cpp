#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
    private:
        vector<pair<int, string>> table;
        vector<int> status;

        int hash1(int key) {
            return key % TABLE_SIZE;
        }
        
        int hash2(int key) {
            return 7 - (key % 7);
        }

    public: 
        HashTable() {
            table.resize(TABLE_SIZE);
            status.resize(TABLE_SIZE, 0);
        }

        void insert(int key, string value) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            int deletedIndex = -1;

            while (true) {
                if (status[index] == 1 && table[index].first == key) {
                    table[index].second = value;
                    cout << "Data NIM " << key << " berhasil diperbarui!\n";
                    return;
                }

                if (status[index] == 2 && deletedIndex == -1) {
                    deletedIndex = index;
                }

                if (status[index] == 0) {
                    if (deletedIndex != -1) {
                        index = deletedIndex;
                    }

                    table[index] = make_pair(key, value);
                    status[index] = 1;
                    cout << "Sukses insert: [" << key << "] " << value << " di indeks " << index << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            if (deletedIndex != -1) {
                table[deletedIndex] = make_pair(key, value);
                status[deletedIndex] = 1;
                cout << "Sukses insert (mengisi slot kosong): [" << key << "] " << value << " di indeks " << deletedIndex << endl;
            } else {
                cout << "Gagal insert: Hash Table sudah penuh!" << endl;
            }
        }

        void search(int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    cout << "Data ditemukan -> NIM: " << table[index].first << ", Nama: " << table[index].second << " (Indeks " << index << ")" << endl;
                    return;
                }  

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Data NIM " << key << " tidak ditemukan!" << endl;
        }

        void remove(int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    status[index] = 2;
                    cout << "Data NIM " << key << " berhasil dihapus dari indeks " << index << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Gagal menghapus: Data NIM " << key << " tidak ditemukan!" << endl;
        }

        void display() {
            cout << "\nISI HASH TABLE\n";
            cout << left << setw(8) << "Indeks" << setw(15) << "NIM" << setw(30) << "Nama" << "Status" << endl <<endl;
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << left << setw(8) << i;

                if (status[i] == 1) {
                    cout << setw(15) << table[i].first << setw(30) << table[i].second << "TERISI";
                } else if (status[i] == 2) {
                    cout << setw(15) << "---" << setw(30) << "---" << "DELETED";
                } else {
                    cout << setw(15) << "---" << setw(30) << "---" << "KOSONG";
                }
                cout << endl;
            }
            cout << endl;
        }
};

int main() {
    HashTable ht;
    int pilihan, nim;
    string nama;

    do {
        cout << "MENU HASH TABLE MAHASISWA\n";
        cout << "1. Insert Data Mahasiswa\n";
        cout << "2. Search Data (berdasarkan NIM)\n";
        cout << "3. Remove Data (berdasarkan NIM)\n";
        cout << "4. Tampilkan Isi Hash Table\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan NIM (angka) : ";
                cin >> nim;
                cin.ignore();
                cout << "Masukkan Nama        : ";
                getline(cin, nama);
                ht.insert(nim, nama);
                cout << endl;
                break;

            case 2:
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                ht.search(nim);
                cout << endl;
                break;

            case 3:
                cout << "Masukkan NIM yang akan dihapus: ";
                cin >> nim;
                ht.remove(nim);
                cout << endl;
                break;

            case 4:
                ht.display();
                break;

            case 5:
                cout << "\nMenampilkan isi akhir Hash Table sebelum keluar:\n";
                ht.display();
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid! Silakan pilih 1-5.\n\n";
        }
    } while (pilihan != 5);

    return 0;
}
