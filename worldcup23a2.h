// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
//

#ifndef WORLDCUP23A2_H_
#define WORLDCUP23A2_H_
#include "Team.h"


class world_cup_t {
private:
	AVLTree<Team, ConTId> wc_teams;
    RankTree<Team, ConTAId> wc_teams_by_ability;
    UF wc_players;

    static const int WIN_POINTS = 3;
    static const int TIE_POINTS = 3;
    static const int MATCH_TIE = 0;
    static const int TEAM1_WON_BY_ABILITY = 1;
    static const int TEAM1_WON_BY_SPIRIT = 2;
    static const int TEAM2_WON_BY_ABILITY = 3;
    static const int TEAM2_WON_BY_SPIRIT = 4;

    /** sub function for add_player
     * returns true if input to add_player is of failure
     * returns false if not
     */
    bool add_player_is_failure_input(int playerId, int teamId);

    /** sub function for add_player
     * if player is first - establishes team-players_root connectivity
     * else - updates father of node as root
     */
    void update_player_connections(Player* new_player, Team* team);

    /** sub function for add_player
     * updates team when adding a new player
     */
    void update_team_with_player(Player* new_player, Team* team);

    /** sub function for play_match
     * returns true if input to play_match is invalid
     * returns false if not
     */
    bool play_match_is_failure_input(int teamId1,int  teamId2);

    /** sub function for play_match
     * updates teams according to match results
     */
    void update_teams_after_match(Team*& winner, Team*& loser, bool is_tie);

    /** sub function for play_match
    * calculates result of match and returns corresponding return value
    */
    int calc_match_result(Team* team1, Team* team2);

    /** sub function for buy_team
    * returns true if input to buy_team is invalid
     * returns false if not
    */
    bool buy_team_is_invalid_input(int teamId1,int  teamId2);

    /** sub function for buy_team
     *  makes union with 2 teams
     */
    void make_union(Team* bigger_team, Team* smaller_team, int buyer_teamId);

    /** sub function for buy_team
    *  updates teams fields after union is made
    */
    void update_buying_team(Team* bigger_team, Team* smaller_team, int buyer_teamId);

public:
	// <DO-NOT-MODIFY> {
	
	world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId,
	                      const permutation_t &spirit, int gamesPlayed,
	                      int ability, int cards, bool goalKeeper);
	
	output_t<int> play_match(int teamId1, int teamId2);
	
	output_t<int> num_played_games_for_player(int playerId);
	
	StatusType add_player_cards(int playerId, int cards);
	
	output_t<int> get_player_cards(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	output_t<int> get_ith_pointless_ability(int i);
	
	output_t<permutation_t> get_partial_spirit(int playerId);
	
	StatusType buy_team(int teamId1, int teamId2);
	
	// } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_
