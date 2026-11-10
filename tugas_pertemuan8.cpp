#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

const int TABLE_SIZE = 10;

// nim dan nama 

class HashTable {
    private :
        vector <pair<int, string>> table;
        vector <int> status;

        int hash1(int key) {
            return key % TABLE_SIZE;
        }
        
        int hash2 (int key) {
            return 7 - (key % 7);
        }

    public : 
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
                    return;
                }

                if (status[index] == 2 && deletedIndex == -1) {
                    deletedIndex = index; // 9 -> 10, kimmy , HAPUS, 9 -> deleted
                }

                if (status[index] == 0) {
                    if (deletedIndex != -1) {
                        index = deletedIndex;
                    }

                    table[index] = make_pair(key, value);
                    status[index] = 1;
                    cout<< "Sukses insert: [" << key << "] "<<value<<"di indeks "<<index<<endl;
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
                cout<<"Sukses insert (mengisi slot kosong) : ["<<key<<"] "<<value<<"di indeks "<<deletedIndex<<endl;
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
                    cout << "Data ditemukan -> NIM: " << table[index].first<<", Nama: "<<table[index].second << endl;
                    return;
                }  

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Data NIM " << key <<" tidak ditemukan!"<< endl;
        }

        void remove (int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    status[index] = 2;
                    cout << "Data NIM "<< key <<"berhasil dihapus dari indeks "<< index << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Gagal menghapus: Data NIM " << key <<" tidak ditemukan!" << endl;
        }

        void display() {
            cout << "\n================ ISI HASH TABLE ================\n";
            cout << left << setw(8) << "Indeks" << setw(12) << "NIM" << setw(15) << "Nama" << "Status" << endl;
            cout << "------------------------------------------------\n";
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << left << setw(8) << i;

                if (status[i] == 1) {
                    cout << setw(12) << table[i].first << setw(15) << table[i].second << "TERISI";
                } else if (status[i] == 2) {
                    cout << setw(12) << "---" << setw(15) << "---" << "DELETED";
                } else {
                    cout << setw(12) << "---" << setw(15) << "---" << "KOSONG";
                }
                cout << endl;
            }
            cout << "================================================\n\n";
        }
};

int main() {
    HashTable ht;

    cout << "Melakukan Operasi Insert : \n";
    ht.insert(23, "Andi");
    ht.insert(43, "Budi");
    ht.insert(13, "Citra"); //terjadi collision dengan key 23 & 43
    ht.insert(35, "Dewi");

    ht.display();

    cout << "Melakukan Operasi Search : \n";
    ht.search(43);
    ht.search(99); // tes mencari data yang tidak ada
    cout<< endl;

    cout << "Melakukan Operasi Remove : \n";
    ht.remove(43);

    cout << "Menampilkan Hasil Setelah Remove : ";
    ht.display();

    return 0;
}