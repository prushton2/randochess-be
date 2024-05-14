#include <string>
#include <map>

using std::string;
using std::map;

// Rule Formats
// Rules are a string of 2 or more characters as follows
// "F2L1", "F1", "B2", "FL1", "FLi", "FLt"
// F, L, R, and B are directions. Directions can be conjoined to make a diagonal
// The number or letter after is the modifier, specifying how many spaces apply to the direction. For example, a pawn movement would be F1 indicating forward one. A knight would be F2L1, indicating forward 2 and left 1. i and t can be used instead, specifying 'infinite' and 'until piece' respectively
// A preceeding 's' to a move indicates it must be the first move of the piece

struct Rule {
	string[32] move;
	string[32] take;
};

Rule pawn_rules;

void initialize_rules() {
	pawn_rules.move = {"F1", "sF2"};
}
	


