#include "rules.h"
#include <map>

using std::map;

struct Game {
public:
	// int format: n0000ppp
	// n determines side (0 is white or empty, 1 is black)
	// p determines piece (000 = empty, 001 = pawn, 010 = rook, 011 = knight, 100 = rook, 101 = queen, 110 = king)
	uint8_t board[8][8];
	uint8_t turn; //0 for white, 1 for black
	
	int last_accessed_at;

	int load_rules() { return 0; }
	int init_board() {
		last_accessed_at = std::time(0);

		for(int i = 0; i<8; i++) {
			set_piece( (char) (i+97), 2, 0b00000001 );
			set_piece( (char) (i+97), 7, 0b10000001 );
		}
		return 0;
	}

	int set_piece(char file, int rank, int piece) {
		file -= 97;
		board[file+1][rank+1] = piece;
		return 1;
	}

	int is_valid_move(int piece_pos, int end_pos) {return 0;}
	int play(int start_pos, int end_pos) { return 0;}
};

