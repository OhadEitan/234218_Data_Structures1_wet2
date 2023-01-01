//
// Created by eitan on 20/12/2022.
//

#ifndef WET2_UNION_FIND_H
#define WET2_UNION_FIND_H
#include "HashTable.h"
#include "Player.h"
#include "Team.h"



/////spirit_addition should be mult
//////game_addition should be add



class UF_Node
{
public:
    Player* data;
    UF_Node* father;
    long long int size;
    long long int spirit_addition;
    long long int game_addition;
    Team* team;

    UF_Node(Player* p1);
    ~UF_Node()= default;


    UF_Node(const UF_Node& uf_node) = default;
    UF_Node& operator=(const UF_Node& uf_node) = default;

};


class UF {
public:
    HashTable<Player> my_hash;

    UF_Node* find(long long int id);
    UF_Node* makeSet(long long int id, Player* p1);
    UF_Node* union_function(Player* p1, Player* p2);

};


#endif //WET2_UNION_FIND_H
