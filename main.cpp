#include <iostream>
#include "Union_Find.h"
#include <cassert>
#include "Player.h"
#include "wet2util.h"
#include "LinkedList.h"
#include "HashTable.h"


void testHashFunction() {
    HashTable<int> ht(100);
    assert(ht.hashFunction(1) == 1);
    assert(ht.hashFunction(50) == 50);
    assert(ht.hashFunction(99) == 99);
    assert(ht.hashFunction(100) == 0);
    assert(ht.hashFunction(150) == 50);
}

void testFind() {
    HashTable<int> ht(100);
    ht.insert(1,1);
    ht.insert(50,50);
    ht.insert(99,99);
    ht.insert(100,100);
    ht.insert(150,150);
    int node = ht.find(1);
    assert(node == 1);
    node = ht.find(50);
    assert(node == 50);
    node = ht.find(99);
    assert(node == 99);
    node = ht.find(100);
    assert(node == 100);
    node = ht.find(150);
    assert(node == 150);
    node = ht.find(200);
    assert(node != 200);
}

void testInsert() {
    HashTable<int> ht(100);
    assert(ht.insert(1,1) == HashStatus::Hash_OK);
    assert(ht.insert(50,50) == HashStatus::Hash_OK);
    assert(ht.insert(99,99) == HashStatus::Hash_OK);
    assert(ht.insert(100,100) == HashStatus::Hash_OK);
    assert(ht.insert(150,150) == HashStatus::Hash_OK);
    assert(ht.insert(1,1) == HashStatus::ALREADY_IN_HASH);
}

void testRemove() {
    HashTable<int> ht(14);
    ht.insert(1,1);
    ht.insert(50,50);
    ht.insert(99,99);
    ht.insert(100,100);
    ht.insert(150,150);
    assert(ht.remove(1) == HashStatus::Hash_OK);
    assert(ht.remove(50) == HashStatus::Hash_OK);
    assert(ht.remove(99) == HashStatus::Hash_OK);
    assert(ht.remove(100) == HashStatus::Hash_OK);
    assert(ht.remove(150) == HashStatus::Hash_OK);
    assert(ht.remove(200) == HashStatus::NOT_IN_HASH);
}

int main() {
    // Create a UF object with 5 elements
    UF<int> uf(5);

    // Test the find_key function
    std::cout << uf.find_key(1) << std::endl;  // should print 1
    std::cout << uf.find_key(2) << std::endl;  // should print 2
    std::cout << uf.find_key(3) << std::endl;  // should print 3
    std::cout << uf.find_key(4) << std::endl;  // should print 4
    std::cout << uf.find_key(5) << std::endl;  // should print 5

    // Test the union_function function
    uf.union_function(1, 2);
    uf.union_function(3, 4);
    uf.union_function(1, 3);

    // Test the find_key function again
    std::cout << uf.find_key(1) << std::endl;  // should print 1
    std::cout << uf.find_key(2) << std::endl;  // should print 1
    std::cout << uf.find_key(3) << std::endl;  // should print 1
    std::cout << uf.find_key(4) << std::endl;  // should print 1
    std::cout << uf.find_key(5) << std::endl;  // should print 5

    testHashFunction();
    testFind();
    testInsert();
    testRemove();
    return 0;
}
