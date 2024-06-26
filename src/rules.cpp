#include "rules.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

// Rule Formats

void initialize_rules(RuleGroup* AllRules ) {
	AllRules[0].name = "default";
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
	AllRules[0].rook->first_move_rule = false;
	AllRules[0].rook->move[0] = "+i+0";
	AllRules[0].rook->move[1] = "-i+0";
	AllRules[0].rook->move[2] = "+0+i";
	AllRules[0].rook->move[3] = "+0-i";

	copy(AllRules[0].rook->move, AllRules[0].rook->move+4, AllRules[0].rook->take);

	AllRules[0].knight = new Rule;
	AllRules[0].knight->requires_los = false;
	AllRules[0].knight->first_move_rule = false;
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
	AllRules[0].bishop->first_move_rule = false;
	AllRules[0].bishop->requires_los = true;
	AllRules[0].bishop->move[0] = "+i+i";
	AllRules[0].bishop->move[1] = "-i+i";
	AllRules[0].bishop->move[2] = "+i-i";
	AllRules[0].bishop->move[3] = "-i-i";

	copy(AllRules[0].bishop->move, AllRules[0].bishop->move+4, AllRules[0].bishop->take);

	AllRules[0].queen = new Rule;
	AllRules[0].queen->first_move_rule = false;
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
	AllRules[0].king->first_move_rule = false;
	AllRules[0].king->move[0] = "+1+0";
	AllRules[0].king->move[1] = "-1+0";
	AllRules[0].king->move[2] = "+0+1";
	AllRules[0].king->move[3] = "+0-1";
	AllRules[0].king->move[4] = "+1+1";
	AllRules[0].king->move[5] = "-1+1";
	AllRules[0].king->move[6] = "+1-1";
	AllRules[0].king->move[7] = "-1-1";

	//OOPS! All Knights

	AllRules[1].name = "OOPS! All Knights!";
	AllRules[1].pawn = new Rule;
	AllRules[1].rook = new Rule;
	AllRules[1].knight = new Rule;
	AllRules[1].bishop = new Rule;
	AllRules[1].queen = new Rule;
	AllRules[1].king = new Rule;

	AllRules[1].pawn->requires_los = false;
	AllRules[1].pawn->first_move_rule = false;
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].pawn->move);
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].pawn->take);

	AllRules[1].rook->requires_los = false;
	AllRules[1].rook->first_move_rule = false;
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].rook->move);
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].rook->take);

	AllRules[1].knight->requires_los = false;
	AllRules[1].knight->first_move_rule = false;
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].knight->move);
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].knight->take);
	
	AllRules[1].bishop->requires_los = false;
	AllRules[1].bishop->first_move_rule = false;
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].bishop->move);
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].bishop->take);
	
	AllRules[1].queen->requires_los = false;
	AllRules[1].queen->first_move_rule = false;
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].queen->move);
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].queen->take);

	AllRules[1].king->requires_los = false;
	AllRules[1].king->first_move_rule = false;
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].king->move);
	copy(AllRules[0].knight->move, AllRules[0].knight->move+8, AllRules[1].king->take);

	//PREPARE THYSELF
	AllRules[2].name = "PREPARE THYSELF";
	AllRules[2].pawn = new Rule;
	AllRules[2].rook = new Rule;
	AllRules[2].knight = new Rule;
	AllRules[2].bishop = new Rule;
	AllRules[2].queen = new Rule;
	AllRules[2].king = new Rule;

	AllRules[2].pawn->requires_los = true;
	AllRules[2].pawn->first_move_rule = true;
	AllRules[2].pawn->move[0] = "+4+0";
	AllRules[2].pawn->move[1] = "+2+0";
	AllRules[2].pawn->move[1] = "+1+0";
	AllRules[2].pawn->take[0] = "/0/0"; //we cant have a rule 0 since that would only work on first move
	AllRules[2].pawn->take[1] = "+1+1"; 
	AllRules[2].pawn->take[2] = "+1-1";

	AllRules[2].rook->move[0] = "NULL";
	AllRules[2].rook->take[0] = "NULL";

	AllRules[2].knight->move[0] = "NULL";
	AllRules[2].knight->take[0] = "NULL";
	
	AllRules[2].bishop->move[0] = "NULL";
	AllRules[2].bishop->take[0] = "NULL";
	
	AllRules[2].queen->move[0] = "NULL";
	AllRules[2].queen->take[0] = "NULL";
	
	AllRules[2].king->move[0] =  "NULL";
	AllRules[2].king->take[0] =  "NULL";

	
	//Have a plan to kill everyone you meet
	AllRules[3].name = "Have a plan to kill everyone you meet";
	AllRules[3].pawn = new Rule;
	AllRules[3].rook = new Rule;
	AllRules[3].knight = new Rule;
	AllRules[3].bishop = new Rule;
	AllRules[3].queen = new Rule;
	AllRules[3].king = new Rule;

	AllRules[3].pawn->move[0] = "NULL";
	AllRules[3].pawn->take[0] = "NULL";
	
	AllRules[3].rook->move[0] = "NULL";
	AllRules[3].rook->take[0] = "NULL";

	AllRules[3].knight->move[0] = "NULL";
	AllRules[3].knight->take[0] = "NULL";
	
	AllRules[3].bishop->first_move_rule = false;
	AllRules[3].bishop->requires_los = false;
	AllRules[3].bishop->move[0] = "+1+1";
	AllRules[3].bishop->move[1] = "+0+1";
	AllRules[3].bishop->move[2] = "-1+1";
	AllRules[3].bishop->move[3] = "-1+0";
	AllRules[3].bishop->move[4] = "-1-1";
	AllRules[3].bishop->move[5] = "+0-1";
	AllRules[3].bishop->move[6] = "+1-1";
	AllRules[3].bishop->move[7] = "+1+0";
	
	AllRules[3].bishop->take[0] = "+i-i";
	AllRules[3].bishop->take[1] = "+i+i";
	AllRules[3].bishop->take[2] = "-i-i";
	AllRules[3].bishop->take[3] = "-i+i";
	
	AllRules[3].queen->move[0] = "NULL";
	AllRules[3].queen->take[0] = "NULL";
	
	AllRules[3].king->move[0] =  "NULL";
	AllRules[3].king->take[0] =  "NULL";


	AllRules[4].name = "Knook";
	AllRules[4].pawn = new Rule;
	AllRules[4].rook = new Rule;
	AllRules[4].knight = new Rule;
	AllRules[4].bishop = new Rule;
	AllRules[4].queen = new Rule;
	AllRules[4].king = new Rule;

	AllRules[4].pawn->move[0] = "NULL";
	AllRules[4].pawn->take[0] = "NULL";
	
	AllRules[4].rook->first_move_rule = false;
	AllRules[4].rook->requires_los = true;
	
	AllRules[4].rook->move[0] = "+i+0";
	AllRules[4].rook->move[1] = "-i+0";
	AllRules[4].rook->move[2] = "+0+i";
	AllRules[4].rook->move[3] = "+0-i";

	AllRules[4].rook->move[4] = "+2+1";
	AllRules[4].rook->move[5] = "+2-1";
	AllRules[4].rook->move[6] = "-2+1";
	AllRules[4].rook->move[7] = "-2-1";
	AllRules[4].rook->move[8] = "+1+2";
	AllRules[4].rook->move[9] = "+1-2";
	AllRules[4].rook->move[10] = "-1+2";
	AllRules[4].rook->move[11] = "-1-2";

	copy(AllRules[4].rook->move, AllRules[4].rook->move+12, AllRules[4].rook->take);

	AllRules[4].knight->move[0] = "NULL";
	AllRules[4].knight->take[0] = "NULL";
	
	AllRules[4].bishop->move[0] = "NULL";
	AllRules[4].bishop->take[0] = "NULL";
	
	AllRules[4].queen->move[0] = "NULL";
	AllRules[4].queen->take[0] = "NULL";
	
	AllRules[4].king->move[0] =  "NULL";
	AllRules[4].king->take[0] =  "NULL";
}

/*
	AllRules[z].name = "Name";
	AllRules[z].pawn = new Rule;
	AllRules[z].rook = new Rule;
	AllRules[z].knight = new Rule;
	AllRules[z].bishop = new Rule;
	AllRules[z].queen = new Rule;
	AllRules[z].king = new Rule;

	AllRules[z].pawn->move[0] = "NULL";
	AllRules[z].pawn->take[0] = "NULL";
	
	AllRules[z].rook->move[0] = "NULL";
	AllRules[z].rook->take[0] = "NULL";

	AllRules[z].knight->move[0] = "NULL";
	AllRules[z].knight->take[0] = "NULL";
	
	AllRules[z].bishop->move[0] = "NULL";
	AllRules[z].bishop->take[0] = "NULL";
	
	AllRules[z].queen->move[0] = "NULL";
	AllRules[z].queen->take[0] = "NULL";
	
	AllRules[z].king->move[0] =  "NULL";
	AllRules[z].king->take[0] =  "NULL";
	*/
