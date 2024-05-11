#include <iostream>
#include "httplib.h"

using namespace httplib;

int main(void)
{
	//Init game
	//Send back a join code to a game for the opponent, and a host code for the host
	
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

        Server svr;

        svr.Get(R"(/numbers/(\d+))", [&](const Request &req, Response &res)
                {
                auto numbers = req.matches[1];
                res.set_content(numbers, "text/plain");
            });

        svr.Get("/stop", [&](const Request &req, Response &res)
                { svr.stop(); });

        svr.listen("localhost", 6000);
}
