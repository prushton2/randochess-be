#include <string>
#include <map>

using std::string;
using std::map;

// Rule Formats

struct Rule {
	bool requires_los;
	bool first_move_rule;
	string move[32];
	string take[32];
};

Rule pawn_rules;
Rule rook_rules;
Rule knight_rules;
Rule bishop_rules;
Rule queen_rules;
Rule king_rules;

void initialize_rules() {
	pawn_rules.requires_los = true;
	pawn_rules.first_move_rule = true;
	pawn_rules.move[0] = "+2+0";
	pawn_rules.move[1] = "+1+0";
	pawn_rules.take[0] = "+0+0"; //we cant have a rule 0 since that would only work on first move
	pawn_rules.take[1] = "+1+1"; 
	pawn_rules.take[2] = "+1-1";

	rook_rules.requires_los = true;
	rook_rules.move[0] = "+i+0";
	rook_rules.move[1] = "-i+0";
	rook_rules.move[2] = "+0+i";
	rook_rules.move[3] = "+0-i";
	rook_rules.take[0] = "+i+0";
	rook_rules.take[1] = "-i+0";
	rook_rules.take[2] = "+0+i";
	rook_rules.take[3] = "+0-i";

	knight_rules.requires_los = false;
	knight_rules.move[0] = "+2+1";
	knight_rules.move[1] = "+2-1";
	knight_rules.move[2] = "-2+1";
	knight_rules.move[3] = "-2-1";
	knight_rules.move[4] = "+1+2";
	knight_rules.move[5] = "+1-2";
	knight_rules.move[6] = "-1+2";
	knight_rules.move[7] = "-1-2";

	knight_rules.take[0] = "+2+1";
	knight_rules.take[1] = "+2-1";
	knight_rules.take[2] = "-2+1";
	knight_rules.take[3] = "-2-1";
	knight_rules.take[4] = "+1+2";
	knight_rules.take[5] = "+1-2";
	knight_rules.take[6] = "-1+2";
	knight_rules.take[7] = "-1-2";
	
	bishop_rules.requires_los = true;
	bishop_rules.move[0] = "+i+i";
	bishop_rules.move[1] = "-i+i";
	bishop_rules.move[2] = "+i-i";
	bishop_rules.move[3] = "-i-i";
	bishop_rules.take[0] = "+i+i";
	bishop_rules.take[1] = "-i+i";
	bishop_rules.take[2] = "+i-i";
	bishop_rules.take[3] = "-i-i";


	queen_rules.requires_los = true;
	queen_rules.move[0] = "+i+0";
	queen_rules.move[1] = "-i+0";
	queen_rules.move[2] = "+0+i";
	queen_rules.move[3] = "+0-i";
	queen_rules.move[4] = "+i+i";
	queen_rules.move[5] = "-i+i";
	queen_rules.move[6] = "+i-i";
	queen_rules.move[7] = "-i-i";
	queen_rules.take[0] = "+i+0";
	queen_rules.take[1] = "-i+0";
	queen_rules.take[2] = "+0+i";
	queen_rules.take[3] = "+0-i";
	queen_rules.take[4] = "+i+i";
	queen_rules.take[5] = "-i+i";
	queen_rules.take[6] = "+i-i";
	queen_rules.take[7] = "-i-i";

	king_rules.requires_los = true;
	king_rules.move[0] = "+1+0";
	king_rules.move[1] = "-1+0";
	king_rules.move[2] = "+0+1";
	king_rules.move[3] = "+0-1";
	king_rules.move[4] = "+1+1";
	king_rules.move[5] = "-1+1";
	king_rules.move[6] = "+1-1";
	king_rules.move[7] = "-1-1";
	king_rules.take[0] = "+1+0";
	king_rules.take[1] = "-1+0";
	king_rules.take[2] = "+0+1";
	king_rules.take[3] = "+0-1";
	king_rules.take[4] = "+1+1";
	king_rules.take[5] = "-1+1";
	king_rules.take[6] = "+1-1";
	king_rules.take[7] = "-1-1";
}
