#include "worldcup23a2.h"



/***************************************************
 * Constructors and Destructors
 ***************************************************/



world_cup_t::world_cup_t() {}



world_cup_t::~world_cup_t()
{
	wc_teams.erase_data(); // deletes all Team objects, hash table deletes all Player objects automatically
}



/***************************************************
 * Adding and Removing Methods
 ***************************************************/



StatusType world_cup_t::add_team(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team* t1 =  new Team(teamId);
    if (this->wc_teams.search(t1 ) != nullptr)
    {
        delete t1;
        return StatusType::FAILURE;
    }
    try
    {
        wc_teams.insert(t1);
        wc_teams_by_ability.insert(t1);
    }
    catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team t_dummy(teamId);
    AVLNode<Team>* team_node;
    team_node = wc_teams.search(&t_dummy);
    if (team_node == nullptr)
    {
        return StatusType::FAILURE;
    }
    Team* team;
    team = team_node->data;
    if (team->t_total_players > 0)
    {
        team->t_players_root->team = nullptr;
        team->t_players_root->game_addition += team->t_games_played;
    }
    try
    {
        this->wc_teams_by_ability.remove(team);
        this->wc_teams.remove_and_erase(team);
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



bool world_cup_t::add_player_is_failure_input(int playerId, int teamId)
{
     if (wc_players.find(playerId) != nullptr)
     {
         return true;
     }
    Team t1(teamId);
    AVLNode<Team>* team_node;
    team_node = this->wc_teams.search(&t1);
    if (team_node == nullptr)
    {
        return true;
    }
    return false;
}



void world_cup_t::update_team_with_player(Player* new_player, Team* team)
{
    wc_teams_by_ability.remove(team);
    team->t_total_players++;
    team->t_ability += new_player->p_ability;
    team->t_spirit = team->t_spirit * new_player->p_spirit;
    if (new_player->p_is_goalkeeper == true)
    {
        team->t_gk_counter++;
        team->t_can_play = true;
    }
    wc_teams_by_ability.insert(team);
    new_player->p_partial_spirit_on_add = team->t_spirit;
}


void world_cup_t::update_player_connections(Player* new_player, Team* team)
{
    UF_Node* new_player_node;
    new_player_node = wc_players.makeSet(new_player->p_id, new_player);
    // ohad adds pointer to player_UF_node in player object
    if (team->t_total_players == 0)
    {
        new_player_node->team = team;
        team->t_players_root = new_player_node;
    }
    else
    {
        new_player_node->father = team->t_players_root;
    }
}


StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {
    if (playerId <= 0 || cards < 0 || teamId <= 0 || gamesPlayed < 0 || !spirit.isvalid())
    {
        return StatusType::INVALID_INPUT;
    }
    if (add_player_is_failure_input(playerId, teamId))
    {
        return StatusType::FAILURE;
    }
    Team *team;
    Team t1(teamId);
    team = wc_teams.search(&t1)->data;
    Player* new_player;
    try
    {
        new_player = new Player(playerId, teamId, spirit, ability,
                                cards, spirit.neutral(), goalKeeper, gamesPlayed);
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    update_player_connections(new_player, team);
    update_team_with_player(new_player, team);
    return StatusType::SUCCESS;
}



/***************************************************
 * Play Match
 ***************************************************/



bool world_cup_t::play_match_is_failure_input(int teamId1,int  teamId2)
{
    Team t_dummy1(teamId1);
    Team t_dummy2(teamId2);
    AVLNode<Team>* team1_node;
    AVLNode<Team>* team2_node;
    team1_node = wc_teams.search(&t_dummy1);
    team2_node = wc_teams.search(&t_dummy2);
    if (team1_node == nullptr || team2_node == nullptr)
    {
        return true;
    }
    if (team1_node->data->t_can_play != true || team2_node->data->t_can_play != true)
    {
        return true;
    }
    return false;
}




void world_cup_t::update_teams_after_match(Team*& winner, Team*& loser, bool is_tie)
{
    if (is_tie)
    {
        winner->t_points += TIE_POINTS;
        loser->t_points += TIE_POINTS;
    }
    else
    {
        winner->t_points += WIN_POINTS;
    }
    winner->t_games_played++;
    loser->t_games_played++;
}



int world_cup_t::calc_match_result(Team* team1, Team* team2)
{
    int team1_win_ability = team1->t_ability + team1->t_points;
    int team2_win_ability = team2->t_ability + team2->t_points;
    int team1_strength = team1->t_spirit.strength();
    int team2_strength = team2->t_spirit.strength();
    if (team1_win_ability > team2_win_ability)
    {
        update_teams_after_match(team1, team2, false);
        return TEAM1_WON_BY_ABILITY;
    }
    if (team1_win_ability < team2_win_ability)
    {
        update_teams_after_match(team2, team1, false);
        return TEAM2_WON_BY_ABILITY;
    }
    if (team1_strength > team2_strength)
    {
        update_teams_after_match(team1, team2, false);
        return TEAM1_WON_BY_SPIRIT;
    }
    if (team1_strength < team2_strength)
    {
        update_teams_after_match(team2, team1, false);
        return TEAM2_WON_BY_SPIRIT;
    }
    update_teams_after_match(team1, team2, true);
    return MATCH_TIE;
}



output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if (play_match_is_failure_input(teamId1, teamId2))
    {
        return StatusType::FAILURE;
    }
    if (teamId1 <=0 || teamId2 <=0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    Team t_dummy1(teamId1);
    Team t_dummy2(teamId2);
    Team* team1;
    Team* team2;
    team1 = wc_teams.search(&t_dummy1)->data;
    team2 = wc_teams.search(&t_dummy2)->data;
    int result = calc_match_result(team1, team2);
    return result;
}



/***************************************************
 * Team Points and Ability Methods
 ***************************************************/



output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    AVLNode<Team>* team_node;
    Team t_dummy(teamId);
    team_node = wc_teams.search(&t_dummy);
    if (team_node == nullptr)
    {
        return StatusType::INVALID_INPUT;
    }
    return team_node->data->t_points;
}



output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if (i < 0)
    {
        return StatusType::FAILURE;
    }
    Team* team;
    team = wc_teams_by_ability.search_by_index(i+1);
    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }
    return team->t_id;
}



/***************************************************
 * Get Player's Number of Played Games
 ***************************************************/



output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player;
    player = wc_players.my_hash.find(playerId);
    if (player == nullptr)
    {
        return StatusType::FAILURE;
    }
    int games_played_additions = 0;
    int games_played_of_team = 0;
    Team* team;
    team = wc_players.find(playerId)->team;
    if (team != nullptr)
    {
        games_played_of_team = team->t_games_played;
    }
    games_played_additions = wc_players.find_gp(playerId);
	return games_played_additions + games_played_of_team;
}



/***************************************************
 * Player Cards Methods
 ***************************************************/



StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if (playerId <= 0 || cards < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player;
    player = wc_players.my_hash.find(playerId);
    if (player == nullptr || wc_players.find(playerId)->team == nullptr)
    {
        return StatusType::FAILURE;
    }
    player->p_cards += cards;
	return StatusType::SUCCESS;
}


output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player;
    player = wc_players.my_hash.find(playerId);
    if (player == nullptr)
    {
        return StatusType::FAILURE;
    }
	return player->p_cards;
}



/***************************************************
 * Get Partial Spirit
 ***************************************************/



output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player;
    player = wc_players.my_hash.find(playerId);
    if (player == nullptr)
    {
        return StatusType::FAILURE;
    }
    permutation_t spirit_additions = player->p_spirit.neutral();
    spirit_additions = wc_players.find_spirit(playerId);
    return spirit_additions * player->p_partial_spirit_on_add;
}



/***************************************************
 * Buy Team
 ***************************************************/



bool world_cup_t::buy_team_is_invalid_input(int teamId1,int  teamId2)
{
    Team t_dummy1(teamId1);
    Team t_dummy2(teamId2);
    AVLNode<Team>* team1_node;
    AVLNode<Team>* team2_node;
    team1_node = wc_teams.search(&t_dummy1);
    team2_node = wc_teams.search(&t_dummy2);
    if (team1_node == nullptr || team2_node == nullptr)
    {
        return true;
    }
    return false;
}



void world_cup_t::make_union(Team* bigger_team, Team* smaller_team, int buyer_teamId)
{
    // TODO: check execution again with one empty team or 2 empty teams
    wc_teams_by_ability.remove(bigger_team);
    wc_teams.remove(bigger_team);
    if (bigger_team->t_total_players != 0 && smaller_team->t_total_players != 0)
    {
        smaller_team->t_players_root->spirit_addition = bigger_team->t_spirit * smaller_team->t_players_root->spirit_addition;
        smaller_team->t_players_root->game_addition += smaller_team->t_games_played - bigger_team->t_games_played;
        wc_players.union_function(bigger_team->t_players_root->data, smaller_team->t_players_root->data);
    }
    update_buying_team(bigger_team, smaller_team, buyer_teamId);
    wc_teams_by_ability.remove(smaller_team);
    wc_teams.remove_and_erase(smaller_team);
    wc_teams.insert(bigger_team);
    wc_teams_by_ability.insert(bigger_team);
}



void world_cup_t::update_buying_team(Team* bigger_team, Team* smaller_team, int buyer_teamId)
{
    bigger_team->t_points += smaller_team->t_points;
    bigger_team->t_total_players += smaller_team->t_total_players;
    bigger_team->t_ability += smaller_team->t_ability;
    bigger_team->t_gk_counter += smaller_team->t_gk_counter;
    if (bigger_team->t_gk_counter > 0)
    {
        bigger_team->t_can_play = true;
    }
    bigger_team->t_id = buyer_teamId;
    bigger_team->t_spirit = bigger_team->t_spirit * smaller_team->t_spirit; // update new team to new spirit
}



StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    if (buy_team_is_invalid_input(teamId1, teamId2) == true)
    {
        return StatusType::FAILURE;
    }
    Team t_dummy1(teamId1);
    Team t_dummy2(teamId2);
    Team* team1;
    Team* team2;
    team1 = wc_teams.search(&t_dummy1)->data;
    team2 = wc_teams.search(&t_dummy2)->data;
    Team* smaller_team;
    Team* bigger_team;
    if (team1->t_total_players > team2->t_total_players)
    {
        smaller_team = team2;
        bigger_team = team1;
    }
    if (team1->t_total_players <= team2->t_total_players)
    {
        smaller_team = team1;
        bigger_team = team2;
    }
    make_union(bigger_team, smaller_team, teamId1);
	return StatusType::SUCCESS;
}
