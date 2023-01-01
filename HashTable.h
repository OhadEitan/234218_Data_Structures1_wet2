//
// Created by eitan on 19/12/2022.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H
#include "Player.h"
#include "wet2util.h"
#include "LinkedList.h"
#include "iostream"
#define HASH_MAGIC_NUMBER 23 /// this is the min Hash size


typedef enum  {
    expand = 0,
    shrink = 1,
}rehash_style;

typedef enum {
    Hash_OK =0,
    ALREADY_IN_HASH = 1,
    NOT_IN_HASH =2,
    INVALID_INPUT = 3
} HashStatus;


//template <class T1, class T2>



//template <class T1, class T2>
//class Pair
//{
//private:
//    T1 first;
//    T2 second;
//public:
//    Pair(T1& a, T2& b);
//    T1 getFirst();
//    T2 getSecond();
//    ~Pair() = default;
//
//};
//
//template <class T1, class T2>
//Pair<T1,T2>::Pair(T1& a, T2& b)
//        : first(a), second(b) {}
//
//template <class T1, class T2>
//T1 Pair<T1,T2>::getFirst()
//{
//    return first;
//}
//
//template <class T1, class T2>
//T2 Pair<T1,T2>::getSecond()
//{
//    return second;
//}


template<class T>
class hash_node
{
public:
    int key;
    T* value;
    hash_node<T> * next; /// for chain hash

    hash_node(int k, T v) : key(k), value(v), next(nullptr) {};
    hash_node() : key(-1), next(nullptr) {};
    ~hash_node() = default;
};

template<class T>
class HashTable {
public:

    long long int counter;   /// number of elem
    long long int cell_counter; /// return max number array can be inside
    hash_node<T> **table; /// pointer to pairs_list array


HashTable() {
    cell_counter = HASH_MAGIC_NUMBER;
    counter=0;
    table = new hash_node<T> *[HASH_MAGIC_NUMBER];
    for (long long int i = 0; i < cell_counter; i++) {
        table[i] = new hash_node<T>();
        table[i]->key = -1;
    }
}


HashTable(long long int size)
{
    if (size < HASH_MAGIC_NUMBER)
    {
        cell_counter = HASH_MAGIC_NUMBER;
        counter=0;
        table = new hash_node<T> *[HASH_MAGIC_NUMBER];
        for (long long int i = 0; i < cell_counter; i++) {
            table[i] = new hash_node<T>();
            table[i]->key = -1;
        }
    }
    else {
        cell_counter = size;
        counter = 0;
        table = new hash_node<T> *[cell_counter];
        for (long long int i = 0; i < cell_counter; i++) {
            table[i] = new hash_node<T>();
            table[i]->key = -1;
        }
    }
}

~HashTable() {
    for (long long int i = 0; i < cell_counter; i++) {
        while (table[i] != nullptr) {
            hash_node<T> * t = table[i];
            table[i] = table[i]->next;
            delete t->key;
            delete t;
        }
    }
    delete[] table;
}

    long long int hashFunction(long long int value) const;
    T* find(long long int value) const;
    HashStatus insert(long long int key, T* value);
    HashStatus remove(long long int value);

    void clear();
   // void unite(HashTable<K> lower, HashTable<K> bigger);

private:
    void shrink_expand(rehash_style style);
    void rehash(long long int new_size);
};
template<class T>
long long int HashTable<T>::hashFunction(long long int value) const {
    //// here should be something smarter
    return ( value % cell_counter);
}


template<class T>
T* HashTable<T>::find(long long int value) const {

    int place = hashFunction(value);
    hash_node<T>* temp = table[place];
    while( temp != nullptr)
    {
        if(temp->key == value) {
            return temp->value;
        }
        temp = temp->next;
    }
    T t1;
    return t1;
}


template<class T>
HashStatus HashTable<T>::insert(long long int key, T* value) {

    int place = hashFunction(key);
    hash_node<T> *temp = table[place];
    if (temp->key == -1) {
        table[place]->key = key;
        table[place]->value = value;
        table[place]->next = nullptr;
        counter++;
        shrink_expand(expand);
        return Hash_OK;
    } else {
        if (temp->value == value) {
            return ALREADY_IN_HASH;
        }
        while (temp->next != nullptr) // search for key in table[new_key]
        {
            if (temp->value == value) {
                return ALREADY_IN_HASH;
            }
            temp = temp->next;
        }
        hash_node<T> *node_to_add = new hash_node<T>(key, value);
        temp->next = node_to_add;
        counter++;
        shrink_expand(expand);
        return Hash_OK;
    }
}



template<class T>
HashStatus HashTable<T>::remove(long long int value) {
    int place = hashFunction(value);
    hash_node<T> * temp = table[place];
    hash_node<T> * node_to_delete = nullptr;
    if(temp->key == value)
    {
        if(temp->next == nullptr)
        {
            table[place]= new hash_node<T>();
            counter--;
            delete temp;
            shrink_expand(shrink);
            return Hash_OK;
        }
        else {
            table[place] = table[place]->next;
            delete temp;
            counter--;
            shrink_expand(shrink);
            return Hash_OK;
        }
    }
    else {
        while(temp->next != nullptr)
        {
            if(temp->next->key == value)
            {
                node_to_delete = temp->next;
                temp->next = temp->next->next;
                break;
            }
            temp = temp->next;
        }
        if(node_to_delete != nullptr) {
            delete node_to_delete;
            counter--;
            shrink_expand(shrink);
            return Hash_OK;
        }
        else{
            return NOT_IN_HASH;
        }

    }

}





template <class T>
void HashTable<T>::shrink_expand(rehash_style style) {
    long long int new_size = -1;
    if (style == expand) {
        if (counter >= cell_counter) {
            new_size = cell_counter * 2;
        }
    }
    if (style == shrink) {
        if (counter <= cell_counter / 8 && cell_counter > HASH_MAGIC_NUMBER) {
            new_size = cell_counter / 2;
        }
    }
    if (new_size == cell_counter) {
    ;
    }
    if (new_size != -1) {
        rehash(new_size);
    }
}

template <class T>
void HashTable<T>::rehash(long long int new_size) {
    long long int old_size = cell_counter;
    cell_counter = new_size;
    hash_node<T>** old_table = table;
    table = new hash_node<T>*[new_size];
    for (long long int i = 0; i < new_size; i++) {
        table[i] = new hash_node<T>();
        table[i]->key = -1;
    }
    for (long long int i = 0; i < old_size; i++)
    {
        hash_node<T>* current = old_table[i];
        while (current != nullptr )
        {
            if (current->key >0) {
                insert(current->key, current->value);
            }
                current = current->next;

        }
    }

    for (long long int i = 0; i < old_size; i++)
        delete old_table[i];
    delete[] old_table;
}



//    hash_node<T>** old = table;
//    table = new hash_node<T> *[new_size];
//    for (long long int i=0; i< new_size; i++) {
//        table[i] = new hash_node<T>();
//        table[i]->key = -1;
//    }
//    for (long long int i = 0; i < cell_counter; i++)
//    {
//        if (old[i]->key >=0 ) {
//            hash_node<T> *temp = old[i];
//            hash_node<T> * to_delete = temp;
//
//            while (temp) {
//                insert(temp->key, temp->value);
//                to_delete= temp;
//                temp = temp->next;
//                delete to_delete;
//            }
//        }
//    }
//    delete[] old;
//    cell_counter= new_size;
//}







template <class T>
void HashTable<T>::clear()
{
    for(long long int i; i< cell_counter; i++)
    {
        table[i].clear();
        table[i]= nullptr;
    }
}


//template<class K>
//void HashTable<K>::unite(HashTable<K> *lower, HashTable<K>* bigger) {
//    for(long long int i; i< cell_counter; i++)
//    {
//        LLNode<K>* temp_lower = lower->table[i]->head->next;
//        while (temp_lower)
//        {
//            bigger->insert(temp_lower->data);
//            temp_lower= temp_lower->next;
//
//        }
//    }
//    delete[] lower;
//
//}



#endif //WET2_HASHTABLE_H
