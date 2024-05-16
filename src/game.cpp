#include "rules.cpp"
#include <map>
#include <cstdlib>
#include <algorithm>
#include <string>

using std::map;
using std::cout;
using std::endl;
using std::string;

struct Game {
public:
	// int format: n0m00ppp
	// n determines side (0 is white or empty, 1 is black)
	// p determines piece (000 = empty, 001 = pawn, 010 = rook, 011 = knight, 100 = bishop, 101 = queen, 110 = king)
	// m means if the piece has moved or not
	uint8_t board[64];
	uint8_t turn; //0 for white, 1 for black
	
	string lobby_owner;

	string white_code;
	string black_code;

	Rule rules[8];

	int last_accessed_at;

	int init_board(string white_side, string black_side) {
		uint8_t init_board[64] = {130,131,132,133,134,132,131,130,129,129,129,129,129,129,129,129,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,3,4,5,6,4,3,2};
		last_accessed_at = std::time(0);
		for(int i = 0; i<64; i++) {
			board[i] = init_board[i];
		}
		lobby_owner = white_side;

		white_code = white_side;
		black_code = black_side;

		initialize_rules();
		rules[1] = pawn_rules;
		rules[2] = rook_rules;
		rules[3] = knight_rules;
		rules[4] = bishop_rules;
		rules[5] = queen_rules;
		rules[6] = king_rules;

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
	
	int is_valid_turn(string code, int piece_pos) {
		return 1;
		if(code == white_code && ((board[piece_pos] >> 7) & 1) == 0) {
			return 1;
		}
		if(code == black_code && ((board[piece_pos] >> 7) & 1) == 1) {
			return 1;
		}
		return 0;
	}

	int is_valid_move(int piece_pos, int end_pos) {
		string* active_ruleset;
		if(board[end_pos] == 0b0) {
			active_ruleset = ( (rules[board[piece_pos] & 0b00001111]).move );
		} 
		else {
			if(board[end_pos] >> 7 == board[piece_pos] >> 7)
				return 0;
			active_ruleset = ( (rules[board[piece_pos] & 0b00001111]).take );
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
				if(i == 0 && (rules[board[piece_pos] & 0b00001111]).first_move_rule) {
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

	int check_line_of_sight(int piece, int end) {
		cout << "Running LOS check" << endl;
	//	int dir = (end-piece)/(abs(end-piece));
		int delta_x = end%8 - piece%8; //do note x and y are backwards and i do not plan on fixing it
		int delta_y = (int)(end/8) - (int)(piece/8);
		int dir_1 = 1;
		int dir_2 = -(end%8 - piece%8) / abs(end%8-piece%8) ;
		int n = std::max(abs(delta_x), abs(delta_y));
		int v = (delta_x==0)*(8-1)+1; //this is the vertical or horizontal distance to travel
		int sum = 0;
		cout << "dr1: " << dir_1 << endl;
		cout << "dr2: " << dir_2 << endl;
		cout << "d_x: " << delta_x << endl;
		cout << "d_y: " << delta_y << endl;
		cout << "n:   " << n << endl;

		for(int i = 1; i<n; i++) {
			int index = dir_1 * (
				(i * v) * (delta_x == 0 || delta_y == 0) +
				(i*8+i*dir_2) * (delta_x != 0 && delta_y != 0)
			);
			index += piece;
			sum += board[index];
			cout <<i<<": "<< (delta_x == 0||delta_y == 0) << " : " << (delta_x != 0 && delta_y != 0) << endl;
			cout <<i<<": "<< (i * v) << " : " << (i*8+dir_2) << endl;
			cout <<i<<": piece: "<< piece << ", index: " << index << endl;;
			cout <<i<<": sum: "  << sum << ", addend: " << (int)board[index] << endl;
		}
		return sum == 0;

	}
};

