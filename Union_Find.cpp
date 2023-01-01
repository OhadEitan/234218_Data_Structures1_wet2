////
//// Created by eitan on 20/12/2022.
////

#include "Union_Find.h"

UF_Node::UF_Node(Player* p1) : data(p1), father(nullptr), spirit_addition(1), game_addition(0),  size(1), team(nullptr) {}


UF_Node *UF::makeSet(long long int id, Player *p1) {
    my_hash.insert(id,p1);
    UF_Node* node_player = new UF_Node(p1);
    p1->player_UF_node = node_player;
    return  node_player;
}

UF_Node* UF::find(long long int id) {
    long long int spirit_addition_mul =1;
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
        root = root->father;
        spirit_addition_mul *= root->spirit_addition;
        game_addition_sum += root->game_addition;
    }
    UF_Node *temp2 = temp1;
    while (temp2->father != nullptr) {

        temp2->father = root;
        temp1 = temp1->father;
        long long int temp_spirit_addition = temp2->spirit_addition;
        long long int temp_game_addition = temp2->game_addition;
        temp2->game_addition= spirit_addition_mul;
        temp2->spirit_addition = game_addition_sum;
        temp2 = temp1;
        spirit_addition_mul /= temp_spirit_addition;
        game_addition_sum-= temp_game_addition;
    }
    return root;
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
        return  rootA;
    }
    if (rootA->size <  rootB->size)
    {
        rootA->father = rootB;
        rootB->size += rootA->size;
        rootA->size = -1;
        return  rootB;

    }
}




