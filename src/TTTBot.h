#ifndef TTTB_DEF
#define TTTB_DEF
#include "TTT.h"
#include <algorithm>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>


namespace games{
	
	class TTTB{
		unsigned botD = 0;
		unsigned rad = 0;
		games::TTT ttt;
		
		int alphaBeta (bool botFig, unsigned depth, unsigned prevMove,
					   int a = INT_MIN, int b = INT_MAX);
		void unmakeMove (unsigned cell);
		bool checkCell (unsigned cell);
		
	public:
		TTTB ();
		explicit TTTB (unsigned _width, unsigned _height, unsigned _winlen,
						 unsigned _botD, unsigned _rad);
		~TTTB ();
		unsigned getMove ();
		void setPos (games::TTT const &ttt);
	};
}

#endif