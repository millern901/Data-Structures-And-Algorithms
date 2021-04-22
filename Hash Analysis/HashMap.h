//
// Created by Nicholas Miller on 10/19/18.
//

#ifndef HASHANALYSIS_HASHMAP_H
#define HASHANALYSIS_HASHMAP_H

#include <list>
#include <vector>

int modTable(int key, int tableSize);
int midSquare(int key, int tableSize);

class Hash_Map_Open {
private:
    int tableSize, currSize, colCount;

    // Resolution schema
    std::vector<int> table;

public:
    Hash_Map_Open(int tableSize);
    void insert(int key);
    double getL();
    int getTableSize();
};

class Hash_Map_Linked {
private:
    int tableSize, currSize, colCount;

    // Resolution schema
    std::vector<std::list<int>> table;

public:
    Hash_Map_Linked(int tableSize);
    void insert(int key);
    double getL();
    int getTableSize();
};

#endif //HASHANALYSIS_HASHMAP_H
