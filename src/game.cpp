#include "game.h"
#include "rules.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>

using std::cout;
using std::endl;
using std::string;

// Piece Information
// int format: n0m00ppp
// n determines side (0 is white or empty, 1 is black)
// p determines piece (000 = empty, 001 = pawn, 010 = rook, 011 = knight, 100 = bishop, 101 = queen, 110 = king)
// m means if the piece has moved or not

int Game::init_board(string white_side, string black_side, RuleGroup* AllRules, int rule_id) {
	uint8_t init_board[64] = {130,131,132,133,134,132,131,130,129,129,129,129,129,129,129,129,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,3,4,5,6,4,3,2};
	//last_accessed_at = std::time(0);
	for(int i = 0; i<64; i++) {
		board[i] = init_board[i];
	}
	lobby_owner = white_side;
	current_turn = "white";
	rule = AllRules[rule_id].name;
	
	white_code = white_side;
	black_code = black_side;
	
	Rule* default_rules[6] = {AllRules[0].pawn, AllRules[0].rook, AllRules[0].knight, AllRules[0].bishop, AllRules[0].queen, AllRules[0].king};

	Rule* applied_rules[6] = {AllRules[rule_id].pawn, AllRules[rule_id].rook, AllRules[rule_id].knight, AllRules[rule_id].bishop, AllRules[rule_id].queen, AllRules[rule_id].king};

	rules[1] = new PRule;
	rules[2] = new PRule;
	rules[3] = new PRule;
	rules[4] = new PRule;
	rules[5] = new PRule;
	rules[6] = new PRule;

	for(int i = 1; i<7; i++) {
		//cout << i << ": " << endl;
		//cout << "Move: " << applied_rules[i-1]->move[0] << endl;
		if(applied_rules[i-1]->move[0] != "NULL") {
			//cout << "move: apl " << endl;
			rules[i]->move = applied_rules[i-1]->move;
			rules[i]->requires_los = applied_rules[i-1]->requires_los;
			rules[i]->first_move_rule = applied_rules[i-1]->first_move_rule;
		} else {
			//cout << "move: def " << endl;
			rules[i]->move = default_rules[i-1]->move;
			rules[i]->requires_los = default_rules[i-1]->requires_los;
			rules[i]->first_move_rule = default_rules[i-1]->first_move_rule;
		}

		//cout << "Take: " << applied_rules[i-1]->take[0] << endl;
		if(applied_rules[i-1]->take[0] != "NULL") {
			//cout << "take: apl " << endl;
			rules[i]->take =    applied_rules[i-1]->take;
		} else {
			//cout << "take: def " << endl;
			rules[i]->take =    default_rules[i-1]->take;
		}
	}

	winner = "";
	return 0;
}

int Game::rf_to_i(char file, int rank) {
	rank = 8 - rank;
	file -= 97;
	return rank*8+file;
}

int Game::set_piece(char file, int rank, int piece) {
	board[rf_to_i(file, rank)] = piece;
	return 1;
}
	
int Game::is_valid_turn(string code, int piece_pos) {
	if(code == white_code && current_turn == "white" && ((board[piece_pos] >> 7) & 1) == 0) {
		return 1;
	}
	if(code == black_code && current_turn == "black" && ((board[piece_pos] >> 7) & 1) == 1) {
		return 1;
	}
	return 0;
}

int Game::is_valid_move(int piece_pos, int end_pos) {
	string* active_ruleset;
	if((board[end_pos] & (1 << 7)) == (board[piece_pos] & (1<<7)) && ((board[end_pos]&0b00001111) != 0)) {
		return 0;
	}
	if(board[end_pos] == 0b0) {
		active_ruleset = ( (rules[board[piece_pos] & 0b00001111])->move );
	} 
	else {
		active_ruleset = ( (rules[board[piece_pos] & 0b00001111])->take );
	}
	
	int delta_h = (piece_pos/8 - end_pos/8);
	int delta_w = (end_pos%8 - piece_pos%8);

	if(board[piece_pos] >> 7 == 1) { //if the piece is black, invert the deltas since blacks are on the other side of the board
		delta_h *= -1;
		delta_w *= -1;
	}

	//this is a horrid mess please send help
	string compareTo = "";
	if(delta_h >= 0)
		compareTo += "+";
	compareTo += std::to_string(delta_h);
	if(delta_w >= 0)
		compareTo += "+";
	compareTo += std::to_string(delta_w);
	
	string leftCompare = compareTo;
	if(leftCompare.at(3) == leftCompare.at(1))
		leftCompare[3] = 'i';
	leftCompare[1] = 'i';
	//theres no need to check if the numbers are equal, we did that in the step above.
	string rightCompare = compareTo;
	rightCompare[3] = 'i';

	//:vomit emoji:
	
	for(int i = 0; i<32; i++) {
		if(active_ruleset[i] == compareTo || 
		   active_ruleset[i] == rightCompare || 
		   active_ruleset[i] == leftCompare) {
			
			//if we are matching rule 0 and the piece has first move rule
			if(i == 0 && (rules[board[piece_pos] & 0b00001111])->first_move_rule) {
				//make sure its the first move
				if((board[piece_pos] & (1 << 5)) == 0) {
					return 1;
				}
				//if it wasnt then continue
				continue;
			}
			return 1;
		}
	}
	
//		cout << compareTo << " " << leftCompare << " " << rightCompare << endl;

	return 0;
}

int Game::check_line_of_sight(int piece, int end) {
	int delta_x = end%8 - piece%8; //do note x and y are backwards and i do not plan on fixing it
	int delta_y = (int)(end/8) - (int)(piece/8);
	
	if(delta_x != 0 && delta_y != 0)
		if(abs(delta_x) != abs(delta_y))
			return 1;
		

	int end_div = end/8;
	int piece_div = piece/8; //so they are integers
	int dir_1 = -std::clamp(end_div - piece_div, -1, 1);
	int dir_2 = -(end%8 - piece%8) / (abs(end%8-piece%8) == 0 ? 1 : abs(end%8-piece%8)) ;

	dir_1 += dir_1 == 0;
	dir_2 += dir_2 == 0;

	int n = std::max(abs(delta_x), abs(delta_y));
	int v = (delta_x==0)*(8-1)+1; //this is the vertical or horizontal distance to travel
	int sum = 0;

	for(int i = 1; i<n; i++) {
		int index = (
			(dir_1 * i * -v * dir_2) * (delta_x == 0 || delta_y == 0) +
			(-dir_1 * i * 8 + (-dir_2*i)) * (delta_x != 0 && delta_y != 0)
		);
		index += piece;
		sum += board[index];
	}
	return sum == 0;

}

int Game::check_for_wins() {
	int black_king = 0;
	int white_king = 0;
	for(int i = 0; i<64; i++) {
		if( (board[i] & 1<<7) == 1 && (board[i] & 0b00001111) == 0b110)
			white_king = 1;
		else if( (board[i] & 1<<7) == 0 && (board[i] & 0b00001111) == 0b110)
			black_king = 1;
	}
	if(white_king == 0)
		winner = "black";
	if(black_king == 0)
		winner = "white";
	return black_king != white_king;
}
