//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "Player.h"
#include "AVLTree.h"
#include "LinkedList.h"

#pragma once




class Team {
public:
    int t_id;
    LLNode<Player>* t_players;
    int t_total_players;
    int t_spirit;
    int t_strength;
    int t_ability;
    int t_gk_counter;
    int t_points;
    bool t_can_play;
    int t_games_played;





//    AVLTree<Player, ConPId > t_players; // this one belong to him
//    AVLTree<Player, ConPichichi > t_pichichi; // this one belong to him
//    LLNode<Team>* p_twc_list_capable;
//    int team_id;
//    int t_total_players;
//    int t_score;
//    int t_points;
//    int t_games_played;
//    Player* t_pichichi_out;
//    int t_gk_counter;
//    bool t_is_capable;


    Team(int t_id, LLNode<Player>* t_players, int t_total_players, int t_spirit, int
        t_strength, int t_ability, int t_gk_counter,int t_points,bool t_can_play,
        int t_games_played);
    Team(int teamId);
    Team(const Team&) = default;
    Team& operator=(const Team& T) = default;
    ~Team() = default;


};

class ConTId {
public:
    Comparison operator()(Team* a, Team* b)
    {
        if (a->t_id < b->t_id)
        {
            return Comparison::LESS_THAN;
        }
        if (a->t_id > b->t_id)
        {
            return Comparison::GREATER_THAN;
        }
        return Comparison::EQUAL;
    }
};

class ConTAId {
public:
    Comparison operator()(Team* a, Team* b)
    {
        if (a->t_ability < b->t_ability)
        {
            return Comparison::LESS_THAN;
        }
        if (a->t_ability > b->t_ability)
        {
            return Comparison::GREATER_THAN;
        }
        if (a->t_id < b->t_id)
        {
            return Comparison::LESS_THAN;
        }
        if (a->t_id > b->t_id)
        {
            return Comparison::GREATER_THAN;
        }
        return Comparison::EQUAL;
    }
};
#endif //WET1_TEAM_H