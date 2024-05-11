#include <iostream>
#include "httplib.h"

#include <string>
#include <format>
#include <map>
#include <random>

#include <ctime>
using namespace httplib;

using std::cout;
using std::endl;
using std::string;

int main(void)
{
	// Definitions
	std::map<std::string, int> gamecodes;

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
			gamecodes[host_code] = std::time(0);
			while(gamecodes[guest_code] != 0) {
				guest_code = std::to_string(distribution(generator));
			}
			gamecodes[guest_code] = std::time(0);
		
			cout << "Host: " << host_code << "[" << gamecodes[host_code] << "]" << endl;
			cout << "Guest: " << guest_code << "[" << gamecodes[guest_code] << "]" << endl;

			res.set_content(
				"{'host_code':"+host_code+",'guest_code':"+guest_code+"}", 
			"text/json");
	});

	svr.Get(R"(/game/info/([0-9][0-9]*))", [&](const Request &req, Response &res) {
                string code = req.matches[1];
		int creation_date = gamecodes[code];
		res.set_content(std::to_string(creation_date), "text/plain");
		gamecodes[code] = std::time(0);
	});

	//Join game
	//Check if join code is valid, if so the relevane info of the game is returned
	
	//Send move
	//Sends: start position, end position
	//Receives: Is valid move
	
	//Fetch Move
	//Was there another move played by the opponent (server keeps track of if the move was propogated or not)

	//IsValidMove
	//Since the movable spots can be undetermined, this move takes two spots and determines if the piece at p1 can move to p2

	//GetValidMoves
	//returns the spots the piece at pos1 can move to



        svr.Get("/stop", [&](const Request &req, Response &res)
                { svr.stop(); });

        svr.listen("localhost", 6000);
}
