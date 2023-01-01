#include "worldcup23a2.h"

world_cup_t::world_cup_t(): wc_teams(), wc_teams_by_ability(),
wc_players(), t_players() {}


world_cup_t::~world_cup_t()
{
    this->wc_players.clear();
    this->wc_teams.AVLTree<Team, ConTId>::erase_data();
    this->wc_teams_by_ability.erase_data();

//    while(this->wc_players_tree_to_delete.head != nullptr) {
//        this->wc_players_tree_to_delete.head->data->erase_data();
//        this->wc_players_tree_to_delete.head = this->wc_players_tree_to_delete.head->next;
//    }
}

StatusType world_cup_t::add_team(int teamId)
{
    if (teamId <=0 ) {
        return StatusType::INVALID_INPUT;
    }
    Team *t1 = new Team(teamId);

    if (this->wc_teams.search(t1 ) != nullptr)
    {
        delete t1;
        return StatusType::FAILURE;
    }
    this->wc_teams.insert(t1 );
    this->wc_teams_by_ability.insert(t1);
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <=0 ) {
        return StatusType::INVALID_INPUT;
    }
    Team *t1 = new Team(teamId);

    if (this->wc_teams.search(t1 ) != nullptr)
    {
        delete t1;
        return StatusType::FAILURE;
    }

	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if (playerId <=0 ֻֻֻֻֻ|| teamId<=0 || gamesPlayed<0 || cards <0 ) {
        return StatusType::INVALID_INPUT;
    }
    Team *t1 = new Team(teamId);
    if (this->wc_teams.search(t1 ) != nullptr)
    {
        delete t1;
        return StatusType::FAILURE;
    }

    Player *p1 = new Player(playerId,0,spirit,ability,cards,goalKeeper,);



    // TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if (teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team *t1 = new Team(teamId1);

    if (this->wc_teams.search(t1 ) != nullptr)
    {
        delete t1;
        return StatusType::FAILURE;
    }
    Team *t2 = new Team(teamId2);

    if (this->wc_teams.search(t2 ) != nullptr)
    {
        delete t1;
        delete t2;
        return StatusType::FAILURE;
    }
    /// so both team are valid


    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    //// here we should check if player was deleted
    if (this->wc_players.find(playerId ) != nullptr || 1<0)
    {
        return StatusType::FAILURE;
    }
    Player *p1 = new Player(playerId);
    /// bla bla bla
    delete p1;
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if (playerId <= 0 || cards < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    //// here we should check if player was deleted
    if (this->wc_players.find(playerId ) != nullptr || 1<0)
    {
        return StatusType::FAILURE;
    }
    Player *p1 = new Player(playerId);
    /// bla bla bla
    delete p1;

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    //// here we should check if player was deleted
    if (this->wc_players.find(playerId ) != nullptr || 1<0)
    {
        return StatusType::FAILURE;
    }
    Player *p1 = new Player(playerId);
    /// bla bla bla
    delete p1;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team *t1 = new Team(teamId);

    ///// how do I search if team was deleted???
    if (this->wc_teams.search(t1 ) != nullptr && 1>0)
    {

        delete t1;
        return StatusType::FAILURE;
    }
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if (i<0 || wc_teams_by_ability.get_num_of_nodes() <=i)
    {
        return  StatusType::FAILURE;
    }
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (this->wc_players.find(playerId ) != nullptr)
    {
        return StatusType::FAILURE;
    }
     Player *p1 = new Player(playerId);
    /// bla bla bla
    delete p1;

    return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if (teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team *t1 = new Team(teamId1);

    if (this->wc_teams.search(t1 ) != nullptr)
    {
        delete t1;
        return StatusType::FAILURE;
    }
    Team *t2 = new Team(teamId2);

    if (this->wc_teams.search(t2 ) != nullptr)
    {
        delete t1;
        delete t2;
        return StatusType::FAILURE;
    }
    /// so both team are valid


	return StatusType::SUCCESS;
}
