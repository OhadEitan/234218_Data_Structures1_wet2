//
// Created by eitan on 20/12/2022.
//

#ifndef WET2_UNION_FIND_H
#define WET2_UNION_FIND_H
#define UF_MAGIC_NUMBER 23 /// this is the min Hash size



/////spirit_addition should be mult
//////game_addition should be add

template <class K, class T>
class UF_Node
{
public:    long long int key;
    long long int size_of_group;
    long long int spirit_addition;
    long long int game_addition;
    K* k;
    T* team_by_id;
    T* team_by_ability;
    UF_Node* father;
    explicit UF_Node(long long int a);
    ~UF_Node()=default;
};
template <class K, class T>
UF_Node<K,T>::UF_Node(long long int a): key(a) , size_of_group(1), spirit_addition(1),
        game_addition(0),  k(nullptr), team_by_id(nullptr),team_by_ability(nullptr), father(nullptr) {

}
/// K must have constractor without parameters


template <class K, class T>
class UF {
public:
    long long int counter;
    long long int size;
    UF_Node<K,T> **array;

    UF();
    explicit UF(long long int size);

    ~UF();

    long long int find_key(long long int val);
    T* find_team_by_id(long long int val);
    T* team_by_ability(long long int val);

    UF_Node<K,T>* find_helper(long long int val);


    void union_function(long long int acquirer_id, long long int target_id);

    long long int make_set();
    ///// make set

    //void printCUF();
};

template<class K,  class T>
UF<K,T>::UF(): counter(0), size(UF_MAGIC_NUMBER), array(new UF_Node<K,T>*[UF_MAGIC_NUMBER]) {
    for(long long int i=0;i<UF_MAGIC_NUMBER;++i)
    {
        array[i] = new UF_Node<K,T>(i+1);
    }

}

template<class K,  class T>
UF<K,T>::UF(long long int size) : counter(0), size(size), array(new UF_Node<K,T>*[size]) {
    for(long long int i=0;i<size;++i)
    {
        array[i] = new UF_Node<K,T>(i+1);
    }

}


template<class K ,class T>
UF<K,T>::~UF() {
    for (long long int i = 0; i < size; i++) {
        while (array[i] != nullptr) {
            UF_Node<K,T> * t = array[i];
            array[i] = array[i]->next;
            delete t;
        }
    }
    delete[] array;
}


template<class K, class T>
UF_Node<K,T>* UF<K,T>::find_helper(long long int val) {
    long long int spirit_addition_mul =1;
    long long int game_addition_sum =0;

    UF_Node<K,T> *temp1 = array[val - 1];
    UF_Node<K,T> *rootA = array[val - 1];
    while (rootA->father != nullptr) {
        rootA = rootA->father;
        spirit_addition_mul *= rootA->spirit_addition;
        game_addition_sum += rootA->game_addition;
    }
    spirit_addition_mul *= rootA->spirit_addition;
    game_addition_sum += rootA->game_addition;
    UF_Node<K,T> *temp2 = temp1;
    while (temp2->father != nullptr) {

        temp2->father = rootA;
        temp1 = temp1->father;
        temp2 = temp1;
        long long int temp_spirit_addition = temp2->spirit_addition;
        long long int temp_game_addition = temp2->game_addition;
        temp2->game_addition= spirit_addition_mul;
        temp2->spirit_addition = game_addition_sum;
        spirit_addition_mul /= temp_spirit_addition;
        game_addition_sum-= temp_game_addition;
    }
    return rootA;
}




template<class K, class T>
long long int UF<K, T>::find_key(long long int val) {
    return find_helper(val)->key;
}

template<class K, class T>
T *UF<K, T>::find_team_by_id(long long int val) {
    return find_helper(val)->team_by_id;
}

template<class K, class T>
T *UF<K, T>::team_by_ability(long long int val) {
    return  find_helper(val)->team_by_ability;
}

template<class K,class T>
void UF<K,T>::union_function(long long int x, long long int y) {
    UF_Node<K,T>* rootA = array[x-1];
    UF_Node<K,T>* rootB = array[y-1];
    if ( x > counter || y > counter || x <= 0 || y <= 0 )
    {
      //  throw StatusType::INVALID_INPUT;
    }
    if (rootA->size_of_group >= rootB->size_of_group)
        {
            rootB->father = rootA;
            rootA->size_of_group += rootB->size_of_group;
            rootB->size_of_group = -1;
        }
        else
        {
            rootA->father = rootB;
            rootB->size_of_group += rootA->size_of_group;
            rootA->size_of_group = -1;
        }
}

template<class K, class T>
long long int UF<K, T>::make_set() {
    long long int to_return = counter;
    counter++;
    return to_return;
}




//template<class K>
//void UnionFind::makeSet(long long int j)
//{
//    array[]
//    long long int key;
//    long long int size_of_group;
//    long long int spirit_addition;
//    long long int game_addition;
//    K* k;
//    UF_Node* father;
//    parents[i] = 0;
//    sizes_arr[i] = 1;
//    return;
//}





#endif //WET2_UNION_FIND_H
