#include "rules.h"
#include <map>

using std::map;
using std::cout;
using std::endl;

struct Game {
public:
	// int format: n0000ppp
	// n determines side (0 is white or empty, 1 is black)
	// p determines piece (000 = empty, 001 = pawn, 010 = rook, 011 = knight, 100 = bishop, 101 = queen, 110 = king)
	uint8_t board[64];
	uint8_t turn; //0 for white, 1 for black
	
	int last_accessed_at;

	int load_rules() { return 0; }
	int init_board() {
		uint8_t init_board[64] = {130,131,132,133,134,132,131,130,129,129,129,129,129,129,129,129,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,3,4,5,6,4,3,2};
		last_accessed_at = std::time(0);
		for(int i = 0; i<64; i++) {
			board[i] = init_board[i];
		}
		return 0;
	}

	int rf_to_i(char file, int rank) {
		rank = 8 - rank;
		file -= 97;
		return rank*8+file;
	}

	int set_piece(char file, int rank, int piece) {
		board[rf_to_i(file, rank)] = piece;
		return 1;
	}

	int is_valid_move(int piece_pos, int end_pos) {return 0;}
	int play(int start_pos, int end_pos) { return 0;}
};

