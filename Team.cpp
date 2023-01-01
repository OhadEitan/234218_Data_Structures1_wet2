//
// Created by eitan on 23/11/2022.
//

#include "Team.h"


//Team::Team(int teamId, int points) : t_players(), t_pichichi(), p_twc_list_capable(nullptr),  team_id(teamId), t_total_players(0), t_score(0), t_points(points),
//                                     t_games_played(0), t_pichichi_out(nullptr), t_gk_counter(0), t_is_capable(false) {}

Team::Team(int t_id, LLNode<Player> *t_players, int t_total_players, int t_spirit, int t_strength, int t_ability,
           int t_gk_counter, int t_points, bool t_can_play, int t_games_played) :
        t_id(t_id), t_players(t_players), t_total_players(t_total_players),
        t_spirit(t_spirit), t_strength(t_strength), t_ability(t_ability),
        t_gk_counter(t_gk_counter), t_points(t_points), t_can_play(t_can_play),
        t_games_played(t_games_played){}

Team::Team(int teamId) : t_id(t_id), t_players(0), t_total_players(0), t_spirit(0),
        t_strength(0), t_ability(0), t_gk_counter(0), t_points(0),t_can_play(0),
        t_games_played(0){}


//Team::Team() : t_players(), t_pichichi(), p_twc_list_capable(nullptr),  team_id(0), t_total_players(0), t_score(0), t_points(0),
//               t_games_played(0), t_pichichi_out(nullptr), t_gk_counter(0), t_is_capable(false) {}