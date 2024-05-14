#include "rules.h"

using std::map;

struct Game {
public:
	uint8_t board[8][8];
	uint8_t turn; //0 for white, 1 for black
	
	int last_accessed_at;

	int load_rules();
	int init_board();

	int set_piece(char file, int rank, int piece);

	int is_valid_move(int piece_pos, int end_pos);
	int play(int start_pos, int end_pos);

	uint8_t* get_board_state();
};

