#ifndef WET2_UNION_FIND_H
#define WET2_UNION_FIND_H
#include "HashTable.h"
#include "Player.h"


class Team;

class UF_Node
{
public:
    Player* data;
    UF_Node* father;
    long long int size;
    permutation_t spirit_addition;
    long long int game_addition;
    Team* team;

    UF_Node(Player* p1);
    UF_Node()= default;
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

    permutation_t find_spirit(long long int id);

    long long int find_gp(long long int id);
};


#endif //WET2_UNION_FIND_H