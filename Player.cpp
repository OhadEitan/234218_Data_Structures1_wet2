//
// Created by eitan on 23/11/2022.
//

#include "Player.h"

int abs(int n) { return n > 0 ? n : -n; }



//Player::Player(int p_id,int p_teamId, int p_goals, int p_cards, int p_games_played, bool p_goal_keeper)
//        : p_id(p_id),p_teamId(p_teamId), p_goals(p_goals), p_cards(p_cards),p_games_played(p_games_played),
//          p_goal_keeper(p_goal_keeper), p_UF_Node(nullptr)
//{
//    this->p_pteam = nullptr;
//    this->p_pwc_players= nullptr;
//    this->p_pwc_pichichi= nullptr;
//    this->p_pwc_capable= nullptr;
//    this->p_pt_players= nullptr;
//    this->p_pt_pichichi= nullptr;
//    this->p_pwc_list_capable = nullptr;
//    this->p_pcloset_greater = nullptr;
//    this->p_pcloset_lower = nullptr;
//
//}
//
//Player::Player(int p_id): p_id(p_id),p_teamId(0), p_goals(0),
//                          p_cards(0),p_games_played(0),p_goal_keeper(0), p_pteam(nullptr),
//                          p_pwc_players(nullptr), p_pwc_pichichi(nullptr),
//                          p_pwc_capable(nullptr), p_pt_players(nullptr),
//                          p_pt_pichichi(nullptr),p_pcloset_greater(nullptr),
//                          p_pcloset_lower(nullptr){}
//
//Player::Player() : p_id(0),p_teamId(0), p_goals(0),
//                   p_cards(0),p_games_played(0),p_goal_keeper(0), p_pteam(nullptr),
//                   p_pwc_players(nullptr), p_pwc_pichichi(nullptr),
//                   p_pwc_capable(nullptr), p_pt_players(nullptr),
//                   p_pt_pichichi(nullptr),p_pcloset_greater(nullptr),
//                   p_pcloset_lower(nullptr){}
//
//int  Player::calc_closest(Player*& p1, Player*& p2)
//{
//    if (p2 == nullptr && p1 == nullptr)
//    {
//        return -1;
//    }
//    if (p1 == nullptr)
//    {
//        return p2->p_id;
//    }
//    if (p2 == nullptr)
//    {
//        return p1->p_id;
//    }
//    if (abs(this->p_goals- p1->p_goals) < abs(p2->p_goals-this->p_goals))
//    {
//        return  p1->p_id;
//    }
//    else
//    {
//        if (abs(this->p_goals- p1->p_goals) > abs(p2->p_goals-this->p_goals))
//        {
//            return  p2->p_id;
//        }
//        else
//        {
//            if (abs(this->p_cards - p1->p_cards) < abs(p2->p_cards - this->p_cards))
//            {
//                return  p1->p_id;
//            }
//            else
//            {
//                if (abs(this->p_cards - p1->p_cards) > abs(p2->p_cards - this->p_cards))
//                {
//                    return  p2->p_id;
//                }
//                else
//                {
//                    if (abs(this->p_id- p1->p_id) < abs(p2->p_id-this->p_id))
//                    {
//                        return p1->p_id;
//                    }
//                    return p2->p_id;
//                }
//            }
//        }
//    }
//    return -1;
//}
Player::Player(int p_id, int p_t_players, int p_spirit, int p_ability, int p_cards, int p_partial_spirit_on_add,
               bool is_goalkeeper, addition p_addition): p_id(p_id),
               p_t_players(p_t_players), p_spirit(p_spirit), p_ability(p_ability),
               p_cards(p_cards), p_partial_spirit_on_add(p_partial_spirit_on_add),
               is_goalkeeper(is_goalkeeper), p_addition(p_addition) {}

Player::Player(int p_id): p_id(p_id),
        p_t_players(0), p_spirit(0), p_ability(0),
        p_cards(0), p_partial_spirit_on_add(0),
        is_goalkeeper(false), p_addition() {}

bool operator<(Player &a, Player &b) {
    if (a.p_id < b.p_id)
    {
        return false;
    }
    return true;
}

int Player::operator()(Player &player) {
    return player.p_id;
}

Player::operator int() const {
    return p_id;
}
