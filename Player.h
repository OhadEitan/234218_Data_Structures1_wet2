#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H
#include "RankTree.h"
#include "wet2util.h"


class UF_Node;

class Player {
public:
    int p_id;
    const permutation_t p_spirit;
    int p_ability;
    int p_cards;
    permutation_t p_partial_spirit_on_add;
    bool p_is_goalkeeper;
    int p_games_played;
    UF_Node* player_UF_node;


    Player(int p_id, int p_t_players, const permutation_t& p_spirit, int p_ability,  int p_cards,
           const permutation_t p_partial_spirit_on_add,bool p_is_goalkeeper, int p_games_played):
           p_id(p_id), p_spirit(p_spirit), p_ability(p_ability),
           p_cards(p_cards), p_partial_spirit_on_add(p_partial_spirit_on_add),
           p_is_goalkeeper(p_is_goalkeeper), p_games_played(p_games_played) {};
    Player() = default;
    Player(const Player& p) = default;
    Player& operator=(const Player& p) = default;
    ~Player() = default;
    friend bool operator<(Player& a, Player& b);
    int operator()(Player& player);
    explicit operator int() const;
};


class ConPId{
public:
    Comparison operator()(Player* a, Player* b)
    {
        if (a->p_id < b->p_id)
        {
            return Comparison::LESS_THAN;
        }
        if (a->p_id > b->p_id)
        {
            return Comparison::GREATER_THAN;
        }
        return Comparison::EQUAL;
    }
};



#endif //WET1_PLAYER_H