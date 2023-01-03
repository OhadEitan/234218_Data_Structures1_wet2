////
//// Created by eitan on 20/12/2022.
////

#include "Union_Find.h"

UF_Node::UF_Node(Player* p1) : data(p1), father(nullptr), size(1), game_addition(0),  team(nullptr)
{
    spirit_addition = spirit_addition.neutral();
}


UF_Node *UF::makeSet(long long int id, Player *p1) {
    my_hash.insert(id,p1);
    UF_Node* node_player = new UF_Node(p1);
    p1->player_UF_node = node_player;
    return node_player;
}

UF_Node* UF::find(long long int id) {
    permutation_t spirit_addition_mul;
    spirit_addition_mul = spirit_addition_mul.neutral();
    long long int game_addition_sum =0;
    UF_Node* root = nullptr;
    if (my_hash.find(id) != nullptr) {
        root = my_hash.find(id)->player_UF_node;
    }
    if (root == nullptr) {
        return nullptr;
    }
    UF_Node* temp1 = root;
    while (root->father != nullptr) {
        spirit_addition_mul = root->spirit_addition * spirit_addition_mul;
        game_addition_sum += root->game_addition;
        root = root->father; // TODO: notify ohad about change, used to be 2 rows up (at the beginning of the loop)
    }
    UF_Node *temp2 = temp1;
    while (temp2->father != nullptr) {

        temp2->father = root;
        temp1 = temp1->father;
        permutation_t temp_spirit_addition = temp2->spirit_addition;
        long long int temp_game_addition = temp2->game_addition;
        temp2->game_addition = game_addition_sum;
        temp2->spirit_addition = spirit_addition_mul;
        temp2 = temp1;
        spirit_addition_mul = spirit_addition_mul * temp_spirit_addition.inv();
        game_addition_sum-= temp_game_addition;
    }
    return root;
}

long long int  UF::find_gp(long long int id) {
    long long int game_addition_sum =0;
    UF_Node* root = nullptr;
    if (my_hash.find(id) != nullptr)
    {
        root = my_hash.find(id)->player_UF_node;
    }
    if (root == nullptr) {
        return -1;
    }
    while (root->father != nullptr) {
        game_addition_sum += root->game_addition;
        root = root->father; // TODO: notify ohad about change, used to be 1 row up (at the beginning of the loop)
    }
    return game_addition_sum;
}

permutation_t  UF::find_spirit(long long int id) {
    permutation_t spirit_addition_mul;
    spirit_addition_mul = spirit_addition_mul.neutral();
    UF_Node* root = nullptr;
    if (my_hash.find(id) != nullptr) {
        root = my_hash.find(id)->player_UF_node;
    }
    if (root == nullptr) {
        return spirit_addition_mul.neutral();
    }
    while (root->father != nullptr) {
        spirit_addition_mul = spirit_addition_mul * root->spirit_addition;
        root = root->father; // TODO: notify ohad about change, used to be 1 row up (at the beginning of the loop)
    }
    return spirit_addition_mul;
}

UF_Node* UF::union_function(Player *p1, Player *p2) {
    UF_Node* rootA = nullptr;
    UF_Node* rootB = nullptr;
    if (my_hash.find(p1->p_id) != nullptr) {
        rootA = my_hash.find(p1->p_id)->player_UF_node;
    }
    if (my_hash.find(p2->p_id) != nullptr) {
        rootB = my_hash.find(p2->p_id)->player_UF_node;
    }
    if (rootA->size >= rootB->size)
    {
        rootB->father = rootA;
        rootA->size += rootB->size;
        rootB->size = -1;
        rootB->team = nullptr;
        return  rootA;
    }
    if (rootA->size <  rootB->size)
    {
        rootA->father = rootB;
        rootB->size += rootA->size;
        rootA->size = -1;
        rootA->team = nullptr;
        return  rootB;
    }
    return nullptr;
}



