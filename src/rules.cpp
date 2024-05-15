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
	pawn_rules.take[0] = "+1+1";
	pawn_rules.take[1] = "+1-1";



	rook_rules.requires_los = true;
	rook_rules.move[0] = "+i+0";
	rook_rules.move[1] = "-i+0";
	rook_rules.move[2] = "+0+i";
	rook_rules.move[3] = "+0-i";
	rook_rules.take[0] = "+i+0";
	rook_rules.take[1] = "-i+0";
	rook_rules.take[2] = "+0+i";
	rook_rules.take[3] = "+0-i";
}
