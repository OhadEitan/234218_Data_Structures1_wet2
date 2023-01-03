#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "Union_Find.h"



class Team {
public:
    int t_id;
    UF_Node* t_players_root;
    int t_total_players;
    permutation_t t_spirit;
    int t_ability;
    int t_gk_counter;
    int t_points;
    bool t_can_play;
    int t_games_played;


    Team(int teamId) : t_id(teamId), t_players_root(nullptr), t_total_players(0), t_ability(0), t_gk_counter(0), t_points(0),t_can_play(false),
    t_games_played(0) { t_spirit = t_spirit.neutral(); }
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