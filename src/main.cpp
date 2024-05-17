#include <iostream>
#include "httplib.h"
#include "game.h"
#include "rules.h"

#include <string>
#include <format>
#include <map>
#include <random>

#include <ctime>
using namespace httplib;

using std::cout;
using std::endl;
using std::string;

void set_headers(Response* res) {
	res->set_header("Access-Control-Allow-Origin", "*");
	res->set_header("Access-Control-Allow-Credentials", "true");
	res->set_header("Access-Control-Allow-Methods", "OPTIONS, GET, POST, HEAD");
	res->set_header("Allow", "GET, POST, HEAD, OPTIONS");
	res->set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept, Origin, Authorization");
}

int main(void)
{
	// Definitions
	cout << "init game id map" << endl;
	std::map<std::string, Game*> gamecodes;
	cout << "init groups array" << endl;
	RuleGroup allGroups[32];
	cout << "init rule data" << endl;
	initialize_rules(allGroups);
	cout << "init rng engine" << endl;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,99999);

        Server svr;
	//Init game
	//Send back a join code to a game for the opponent, and a host code for the host

	svr.Get("/game/new", [&](const Request &req, Response &res) {
		//create 2 codes, one for host to play and one for guest to play
		distribution(generator);
		string host_code = std::to_string(distribution(generator));
		string guest_code = std::to_string(distribution(generator));
		

		while(gamecodes[host_code] != 0) {
			host_code = std::to_string(distribution(generator));
		}
		while(gamecodes[guest_code] != 0) {
			guest_code = std::to_string(distribution(generator));
		}
		gamecodes[host_code] = new Game;
		gamecodes[guest_code] = gamecodes[host_code];

		gamecodes[host_code]->init_board(host_code, guest_code, allGroups);

		set_headers(&res);

		res.set_content(
			"{\"host_code\":"+host_code+",\"guest_code\":"+guest_code+"}", 
		"application/json");
	});

	svr.Get(R"(/game/info/([0-9][0-9]*))", [&](const Request &req, Response &res) {
                string code = req.matches[1];
		set_headers(&res);
		res.set_content("", "text/plain");
	});

	//Join game
	//Check if join code is valid	
	svr.Get(R"(/game/exists/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		set_headers(&res);
		res.set_content( std::to_string(gamecodes[req.matches[1]] != NULL), "text/plain");
	});
	
	//Fetch Move
	svr.Get(R"(/game/fetch/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		set_headers(&res);
		Game* pGame = gamecodes[req.matches[1]];
		if(pGame == NULL) {
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}

		string board_state = "[";
		for(int i = 0; i<64; i++)
			board_state = board_state + std::to_string(gamecodes[req.matches[1]]->board[i]) + ",";
		board_state.pop_back();
		board_state += "]";
		
		res.set_content("{\"status\": \"Success\", \"board\":"+board_state+", \"winner\": \""+pGame->winner+"\", \"white_side\": \""+pGame->white_code+"\", \"black_side\": \""+pGame->black_code+"\", \"turn\": \""+pGame->current_turn+"\"}", "application/json");
	});

	//Send Move
	svr.Options(R"(/game/move/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		set_headers(&res);
		res.set_content("", "text/plain");
	});
	svr.Post(R"(/game/move/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		set_headers(&res);
		Game* pGame = gamecodes[req.matches[1]];
		if(pGame == NULL) {
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}


		string temp = "";
		int start = 0;
		int end = 0;

		for(int i = 0; i<req.body.size(); i++) {
			if(req.body.at(i) == '\n') {
				start = atoi(temp.c_str());
				temp = "";
			} else {
				temp += req.body.at(i);
			}
		}
		end = atoi(temp.c_str());
		
		if(start < 0 || start > 63 || end < 0 || end > 63) {
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}

		if(!pGame->is_valid_turn(req.matches[1], start)) {
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}

		if(!pGame->is_valid_move(start, end)) {
			//cout << "Bad Move" << endl;
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}

		int piece = gamecodes[req.matches[1]]->board[start];
		if(pGame->rules[piece&0b00001111]->requires_los && !pGame->check_line_of_sight(start, end)) {
			//cout << "No LOS" << endl;
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}
		
		int checkForWins = (pGame->board[end] & 0b00001111) == 6;

		gamecodes[req.matches[1]]->board[end] = gamecodes[req.matches[1]]->board[start];
		gamecodes[req.matches[1]]->board[start] = 0b00000000;
		gamecodes[req.matches[1]]->board[end] |= 0b00100000;
		
		if(pGame->current_turn == "white")
			pGame->current_turn = "black";
		else
			pGame->current_turn = "white";

		if(checkForWins) 
			pGame->check_for_wins();

		res.set_content("{\"status\": \"Success\"}", "text/plain");
	});
	
	svr.Get(R"(/game/leave/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		set_headers(&res);
		Game* pGame = gamecodes[req.matches[1]];
		if(pGame == NULL) {
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}

		if(pGame->lobby_owner != req.matches[1]) {
			res.set_content("{\"status\": \"Invalid\"}", "application/json");
			return;
		}

		string code1 = pGame->white_code;
		string code2 = pGame->black_code;

		delete gamecodes[code1];
		gamecodes[code1] = NULL;
		gamecodes[code2] = NULL;
		res.set_content("{\"status\": \"Success\"}", "application/json");
		return;
	});
	


        svr.Get("/stop", [&](const Request &req, Response &res) {
		for(int i = 0; i<1; i++) {
			cout << "Deleting ruleset " << i << ".." << endl;
			if(allGroups[i].pawn != 0)
				delete allGroups[i].pawn;
			if(allGroups[i].rook != 0)
				delete allGroups[i].rook;
			if(allGroups[i].knight != 0)
				delete allGroups[i].knight;
			if(allGroups[i].bishop != 0)
				delete allGroups[i].bishop;
			if(allGroups[i].queen != 0)
				delete allGroups[i].queen;
			if(allGroups[i].king != 0)
				delete allGroups[i].king;
		}
		svr.stop(); 
	});

        svr.listen("localhost", 6000);
}
