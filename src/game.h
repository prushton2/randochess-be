#ifndef GAME_H
#define GAME_H

#include "rules.h"
#include <string>
#include <cstdint>

using std::string;

struct Game {
public:
	uint8_t board[64];
	
	string lobby_owner;
	string current_turn;
	string rule;

	string white_code;
	string black_code;
	
	string winner;

	PRule* rules[8];

	int last_accessed_at;

	int init_board(string white_side, string black_side, RuleGroup* AllRules, int rule);
	int rf_to_i(char file, int rank);
	int set_piece(char file, int rank, int piece);
	int is_valid_turn(string code, int piece_pos);
	int is_valid_move(int piece_pos, int end_pos);
	int check_line_of_sight(int piece, int end);
	int check_for_wins();
};

#endif
