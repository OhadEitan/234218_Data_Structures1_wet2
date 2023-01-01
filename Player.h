//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "AVLTree.h"
#include "LinkedList.h"
#include "Union_Find.h"


class addition{
public:
    int partial_spirit_addition;
    int games_played_addition;

    addition()= default;
    ~addition() = default;
};

class UF_Node;
class Team;

class Player {
public:
    int p_id;
    int p_t_players;
    int p_spirit;
    int p_ability;
    int p_cards;
    int p_partial_spirit_on_add;
    bool is_goalkeeper;
    UF_Node player_UF_node;
    addition p_addition;

//
//    int p_id;
//    int p_teamId;
//    int p_goals;
//    int p_cards;
//    int p_games_played;
//    bool p_goal_keeper;
//    UF_Node<Player*>* p_UF_Node;

//    AVLNode<Team>* p_pteam;
//    AVLNode<Player>* p_pwc_players;
//    AVLNode<Player>* p_pwc_pichichi;
//    AVLNode<Team>* p_pwc_capable;
//    AVLNode<Player>* p_pt_players;
//    AVLNode<Player>* p_pt_pichichi;
//    LLNode<Team>* p_pwc_list_capable;
//    Player* p_pcloset_greater;
//    Player* p_pcloset_lower;



    Player(int p_id, int p_t_players, int p_spirit, int p_ability,  int p_cards,
           int p_partial_spirit_on_add,bool is_goalkeeper, addition p_addition);
    //Player();
    Player();
    Player(int p_id);
    Player(const Player& p) = default;
    Player& operator=(const Player& p) = default;
   // int calc_closest(Player*& p1, Player*& p2);
    ~Player() = default;
    friend bool operator<(Player& a, Player& b);
    int operator()(Player& player);
    explicit operator int() const;
};

//template<class condition>
//Player** mergeArrays(Player* array1[], Player* array2[], int size1, int size2)
//{
//    if (array1 == nullptr || array2 == nullptr || size1 < 1 || size2 < 1)
//    {
//        return nullptr;
//    }
//    int i=0, j=0, k=0, t=0;
//    Player** united_array = new Player*[size1 + size2];
//    for (t=0; t<(size1+size2); t++)
//    {
//        united_array[t] = nullptr;
//    }
//    condition cond;
//    while (i < size1 && j < size2)
//    {
//        if (cond(array1[i], array2[j]) == Comparison::LESS_THAN)
//        {
//            united_array[k++] = array1[i++];
//        }
//        else
//        {
//            united_array[k++] = array2[j++];
//        }
//    }
//    while (i < size1)
//    {
//        united_array[k++] = array1[i++];
//    }
//    while (j < size2)
//    {
//        united_array[k++] = array2[j++];
//    }
//    return united_array;
//}

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


//class ConPichichi{
//public:
//    Comparison operator()(Player* a, Player* b)
//    {
//        if (a->p_goals < b->p_goals)
//        {
//            return Comparison::LESS_THAN;
//        }
//        if (a->p_goals > b->p_goals)
//        {
//            return Comparison::GREATER_THAN;
//        }
//        if (a->p_cards < b->p_cards)
//        {
//            return Comparison::GREATER_THAN;
//
//        }
//        if (a->p_cards > b->p_cards)
//        {
//            return Comparison::LESS_THAN;
//        }
//        if (a->p_id < b->p_id)
//        {
//            return Comparison::LESS_THAN;
//        }
//        if (a->p_id > b->p_id)
//        {
//            return Comparison::GREATER_THAN;
//        }
//        return Comparison::EQUAL;
//    }
//};







#endif //WET1_PLAYER_H