#include "Player.h"

int abs(int n) { return n > 0 ? n : -n; }
/*
Player::Player(int p_id, int p_t_players, const permutation_t& p_spirit, int p_ability, int p_cards, int p_partial_spirit_on_add,
               bool is_goalkeeper, int games_played): p_id(p_id),
               p_t_players(p_t_players), p_spirit(p_spirit), p_ability(p_ability),
               p_cards(p_cards), p_partial_spirit_on_add(p_partial_spirit_on_add),
               is_goalkeeper(is_goalkeeper), games_played(games_played) {}

Player::Player(int p_id): p_id(p_id),
        p_t_players(0), p_spirit(0), p_ability(0),
        p_cards(0), p_partial_spirit_on_add(0),
        is_goalkeeper(false) {}
*/
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
