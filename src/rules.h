#ifndef RULES_H
#define RULES_H

#include <string>

using std::string;

// Rule Formats

struct Rule {
	bool requires_los;
	bool first_move_rule;
	string move[32];
	string take[32];
};


struct PRule { //rule but it uses pointers
	bool requires_los;
	bool first_move_rule;
	string* move;
	string* take;
};

struct RuleGroup {
	string name;
	Rule* pawn;
	Rule* rook;
	Rule* knight;
	Rule* bishop;
	Rule* queen;
	Rule* king;
};

void initialize_rules(RuleGroup* AllRules); 

#endif
