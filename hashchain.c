#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Node structure for linked list
typedef struct Node {
    char key[50];
    int value;
    struct Node* next;
} Node;

// Hash table structure
typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

// Hash function
int hashFunction(const char* key) {
    int hash = 0;
    while (*key) {
        hash = (hash + *key) % TABLE_SIZE;
        key++;
    }
    return hash;
}

// Create a new node
Node* createNode(const char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize the hash table
HashTable* createHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Insert a key-value pair
void insert(HashTable* hashTable, const char* key, int value) {
    int index = hashFunction(key);
    Node* newNode = createNode(key, value);
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        Node* temp = hashTable->table[index];
        while (temp) {
            if (strcmp(temp->key, key) == 0) {
                // Key already exists, update value
                temp->value = value;
                free(newNode);
                return;
            }
            if (temp->next == NULL) break;
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Search for a key
int search(HashTable* hashTable, const char* key) {
    int index = hashFunction(key);
    Node* temp = hashTable->table[index];
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    printf("Key \"%s\" not found!\n", key);
    return -1;
}

// Remove a key
void removeKey(HashTable* hashTable, const char* key) {
    int index = hashFunction(key);
    Node* temp = hashTable->table[index];
    Node* prev = NULL;

    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
                hashTable->table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Key \"%s\" removed.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Key \"%s\" not found!\n", key);
}

// Display the hash table
void display(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = hashTable->table[i];
        while (temp) {
            printf("(%s -> %d) ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Free the hash table
void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = hashTable->table[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(hashTable);
}

// Main function
int main() {
    HashTable* hashTable = createHashTable();

    insert(hashTable, "apple", 10);
    insert(hashTable, "banana", 20);
    insert(hashTable, "cherry", 30);
    insert(hashTable, "date", 40);
    insert(hashTable, "elderberry", 50);

    display(hashTable);

    printf("Searching for \"banana\": %d\n", search(hashTable, "banana"));
    printf("Searching for \"fig\": %d\n", search(hashTable, "fig"));

    removeKey(hashTable, "banana");
    display(hashTable);

    freeHashTable(hashTable);
    return 0;
}