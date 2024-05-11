struct Game {
	// int format: n0000ppp
	// n determines side (0 is white or empty, 1 is black)
	// p determines piece (000 = empty, 001 = pawn, 010 = rook, 011 = knight, 100 = rook, 101 = queen, 110 = king)
	uint8_t[64] board;
	uint8_t turn; //0 for white, 1 for black
	//some thing here for all piece rules idk
	
}
