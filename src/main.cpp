#include <iostream>
#include "httplib.h"
#include "game.cpp"

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
	res->set_header("Access-Control-Allow-Headers", "*"); //X-Requested-With, Content-Type, Accept, Origin, Authorization");
}

int main(void)
{
	// Definitions
	std::map<std::string, Game*> gamecodes;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,99999);

	
        Server svr;
	//Init game
	//Send back a join code to a game for the opponent, and a host code for the host
	


	svr.Get("/game/new", [&](const Request &req, Response &res) {
		//create 2 codes, one for host to play and one for guest to play
		cout << distribution(generator) << " was generated" << endl;
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

		gamecodes[host_code]->init_board();

		cout << "Host: " << host_code << endl;
		cout << "Guest: " << guest_code << endl;
		
		set_headers(&res);

		res.set_content(
			"{\"host_code\":"+host_code+",\"guest_code\":"+guest_code+"}", 
		"application/json");
	});

	svr.Get(R"(/game/info/([0-9][0-9]*))", [&](const Request &req, Response &res) {
                string code = req.matches[1];
		set_headers(&res);
		res.set_content("HAHA!", "text/plain");
	});

	//Join game
	//Check if join code is valid	
	svr.Get(R"(/game/exists/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		set_headers(&res);
		res.set_content( std::to_string(gamecodes[req.matches[1]] != NULL), "text/plain");
	});
	
	//Fetch Move
	svr.Get(R"(/game/fetch/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		cout << req.matches[1] << endl;
		cout << gamecodes[req.matches[1]]->board << endl;

		string board_state = "[";
		for(int i = 0; i<64; i++)
			board_state = board_state + std::to_string(gamecodes[req.matches[1]]->board[i]) + ",";
		board_state.pop_back();
		board_state += "]";
		
		res.set_content(board_state, "text/plain");
	});

	//Send Move
	svr.Post(R"(/game/move/([0-9][0-9]*))", [&](const Request &req, Response &res) {
		cout << req.body << endl;
		res.set_content(req.body, "text/plain");
	});

	//GetValidMoves
	//returns the spots the piece at pos1 can move to



        svr.Get("/stop", [&](const Request &req, Response &res)
                { svr.stop(); });

        svr.listen("localhost", 6000);
}
