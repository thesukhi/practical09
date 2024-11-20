#include <iostream>
#include <vector>
#include <string>

const int TABLE_SIZE = 10; // Define the size of the hash table

class HashTable {
private:
    struct Entry {
        std::string key;
        int value;
        bool isDeleted; // To track if the entry was deleted

        Entry() : key(""), value(0), isDeleted(false) {}
    };

    std::vector<Entry> table;

    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash + static_cast<int>(ch)) % TABLE_SIZE;
        }
        return hash;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const std::string& key, int value) {
        int index = hashFunction(key);
        int startIndex = index;

        while (!table[index].key.empty() && !table[index].isDeleted) {
            if (table[index].key == key) {
                // Update existing key
                table[index].value = value;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                std::cout << "Hash table is full!" << std::endl;
                return;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isDeleted = false;
    }

    void remove(const std::string& key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (!table[index].key.empty()) {
            if (table[index].key == key && !table[index].isDeleted) {
                table[index].isDeleted = true;
                table[index].key = "";
                table[index].value = 0;
                std::cout << "Key \"" << key << "\" removed." << std::endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                break;
            }
        }
        std::cout << "Key \"" << key << "\" not found!" << std::endl;
    }

    int search(const std::string& key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (!table[index].key.empty()) {
            if (table[index].key == key && !table[index].isDeleted) {
                return table[index].value;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                break;
            }
        }

        std::cout << "Key \"" << key << "\" not found!" << std::endl;
        return -1;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted) {
                std::cout << "Index " << i << ": " << table[i].key << " -> " << table[i].value << std::endl;
            } else {
                std::cout << "Index " << i << ": Empty" << std::endl;
            }
        }
    }
};

int main() {
    HashTable hashTable;

    hashTable.insert("apple", 10);
    hashTable.insert("banana", 20);
    hashTable.insert("orange", 30);
    hashTable.insert("grape", 40);

    hashTable.display();

    std::cout << "Searching for \"apple\": " << hashTable.search("apple") << std::endl;
    std::cout << "Searching for \"mango\": " << hashTable.search("mango") << std::endl;

    hashTable.remove("banana");
    hashTable.display();

    return 0;
}