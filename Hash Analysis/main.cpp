#include <iostream>
#include <cmath>
#include "HashMap.h"

int main() {

    Hash_Map_Open a(50);
    Hash_Map_Open b(75);
    Hash_Map_Open c(100);
    Hash_Map_Linked d(50);
    Hash_Map_Linked e(75);
    Hash_Map_Linked f(100);

    std::cout << "Open Addressing: " << a.getTableSize() << std::endl;
    while (a.getL() < 1.0) {
        int key = rand() % (3 * a.getTableSize());
        a.insert(key);
    }

    std::cout << std::endl;
    std::cout << "Open Addressing: " << b.getTableSize() << std::endl;
    while (b.getL() < 1.0) {
        int key = rand() % (3 * b.getTableSize());
        b.insert(key);
    }

    std::cout << std::endl;
    std::cout << "Open Addressing: " << c.getTableSize() << std::endl;
    while (c.getL() < 1.0) {
        int key = rand() % (3 * c.getTableSize());
        c.insert(key);
    }

    std::cout << std::endl;
    std::cout << "Chaining: " << d.getTableSize() << std::endl;
    while (d.getL() < 1.0) {
        int key = rand() % (3 * d.getTableSize());
        d.insert(key);
    }

    std::cout << std::endl;
    std::cout << "Chaining: " << e.getTableSize() << std::endl;
    while (e.getL() < 1.0) {
        int key = rand() % (3 * e.getTableSize());
        e.insert(key);
    }

    std::cout << std::endl;
    std::cout << "Chaining: " << f.getTableSize() << std::endl;
    while (f.getL() < 1.0) {
        int key = rand() % (3 * f.getTableSize());
        f.insert(key);
    }

    return 0;
}

// Open Addressing Hash Map
Hash_Map_Open::Hash_Map_Open(int tableSize) {
    this->tableSize = tableSize;
    currSize = 0;
    colCount = 0;
    table.resize(tableSize);
    std::fill(table.begin(), table.end(), -1);
}

void Hash_Map_Open::insert(int key) {
    //Hash functions
    int hash = modTable(key, tableSize);
    //int hash = midSquare(key, tableSize);

    //Insert into table
    while (table[hash] != -1) {
        colCount++;
        if (hash == table.size() - 1) hash = 0;
        else hash++;
    }
    table[hash] = key;
    currSize++;

    //Print collision and load factor
    std::printf("%-s %-i \t %-s %-.3f \n", "Collision count: ", colCount, "Load Factor: ", getL());
}

double Hash_Map_Open::getL() {
    return currSize * 1.0 / tableSize;
}

int Hash_Map_Open::getTableSize() {
    return tableSize;
}

// Linked Hash Map
Hash_Map_Linked::Hash_Map_Linked(int tableSize) {
    this->tableSize = tableSize;
    currSize = 0;
    colCount = 0;
    table.resize(tableSize);
}

void Hash_Map_Linked::insert(int key) {
    //Hash functions
    //int hash = modTable(key, tableSize);
    int hash = midSquare(key, tableSize);

    //Insert into table
    if (!table[hash].empty()) {
        colCount++;
    }
    table[hash].emplace_back(key);
    currSize++;

    //Print collision and load factor
    std::printf("%-s %-i \t %-s %-.3f \n", "Collision count: ", colCount, "Load Factor: ", getL());
}

double Hash_Map_Linked::getL() {
    return currSize * 1.0 / tableSize;
}

int Hash_Map_Linked::getTableSize() {
    return tableSize;
}

int modTable(int key, int tableSize) {
    return (key % tableSize);
}

int midSquare(int key, int tableSize) {
    int rangeBits = (int)ceil(log2(pow(tableSize * 3, 2)));
    int tableBits = (int)ceil(log2(tableSize));
    int divBits = (int)pow(2, (rangeBits - tableBits) / 2);

    int hash = (int)pow(key, 2);
    hash /= divBits;
    hash %= tableSize;

    return hash;
}



