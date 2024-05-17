#include "rules.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

// Rule Formats

void initialize_rules(RuleGroup* AllRules ) {
	AllRules[0].pawn = new Rule;
	AllRules[0].pawn->requires_los = true;
	AllRules[0].pawn->first_move_rule = true;
	AllRules[0].pawn->move[0] = "+2+0";
	AllRules[0].pawn->move[1] = "+1+0";
	AllRules[0].pawn->take[0] = "/0/0"; //we cant have a rule 0 since that would only work on first move
	AllRules[0].pawn->take[1] = "+1+1"; 
	AllRules[0].pawn->take[2] = "+1-1";

	AllRules[0].rook = new Rule;
	AllRules[0].rook->requires_los = true;
	AllRules[0].rook->move[0] = "+i+0";
	AllRules[0].rook->move[1] = "-i+0";
	AllRules[0].rook->move[2] = "+0+i";
	AllRules[0].rook->move[3] = "+0-i";

	copy(AllRules[0].rook->move, AllRules[0].rook->move+4, AllRules[0].rook->take);

	AllRules[0].knight = new Rule;
	AllRules[0].knight->requires_los = false;
	AllRules[0].knight->move[0] = "+2+1";
	AllRules[0].knight->move[1] = "+2-1";
	AllRules[0].knight->move[2] = "-2+1";
	AllRules[0].knight->move[3] = "-2-1";
	AllRules[0].knight->move[4] = "+1+2";
	AllRules[0].knight->move[5] = "+1-2";
	AllRules[0].knight->move[6] = "-1+2";
	AllRules[0].knight->move[7] = "-1-2";
	
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[0].knight->take);

	AllRules[0].bishop = new Rule;
	AllRules[0].bishop->requires_los = true;
	AllRules[0].bishop->move[0] = "+i+i";
	AllRules[0].bishop->move[1] = "-i+i";
	AllRules[0].bishop->move[2] = "+i-i";
	AllRules[0].bishop->move[3] = "-i-i";

	copy(AllRules[0].bishop->move, AllRules[0].bishop->move+4, AllRules[0].bishop->take);

	AllRules[0].queen = new Rule;
	AllRules[0].queen->requires_los = true;
	AllRules[0].queen->move[0] = "+i+0";
	AllRules[0].queen->move[1] = "-i+0";
	AllRules[0].queen->move[2] = "+0+i";
	AllRules[0].queen->move[3] = "+0-i";
	AllRules[0].queen->move[4] = "+i+i";
	AllRules[0].queen->move[5] = "-i+i";
	AllRules[0].queen->move[6] = "+i-i";
	AllRules[0].queen->move[7] = "-i-i";

	copy(AllRules[0].queen->move, AllRules[0].queen->move+8, AllRules[0].queen->take);

	AllRules[0].king = new Rule;
	AllRules[0].king->requires_los = false; //king doesnt need los
	AllRules[0].king->move[0] = "+1+0";
	AllRules[0].king->move[1] = "-1+0";
	AllRules[0].king->move[2] = "+0+1";
	AllRules[0].king->move[3] = "+0-1";
	AllRules[0].king->move[4] = "+1+1";
	AllRules[0].king->move[5] = "-1+1";
	AllRules[0].king->move[6] = "+1-1";
	AllRules[0].king->move[7] = "-1-1";

	copy(AllRules[0].king->move, AllRules[0].king->move+8, AllRules[0].king->take);
}
