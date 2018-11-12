#ifndef TTT_DEF
#define TTT_DEF
#include <iostream>
#include <vector>

namespace games{
	
	enum class CELL {X, O, EMPTY};
	
	class TTT{
	protected:
		unsigned width = 0;
		unsigned height = 0;
		unsigned winlen = 0;
		bool turn = 0;
		unsigned moveNum = 0;
		std::vector<games::CELL> field;
		
	public:
		TTT ();
		explicit TTT (unsigned _width, unsigned _height, 
							unsigned _winlen);
		~TTT ();
		bool checkMove (unsigned cell) const;
		void makeMove (unsigned cell);
		bool checkWin (unsigned cell);
		std::vector<games::CELL> getField () const;
		unsigned getMoveNum () const;
		void unmakeMove (unsigned cell);
		
		bool gameEnded = false;
		games::CELL winner = games::CELL::EMPTY;
		
		unsigned getWidth () const;
		unsigned getHeight () const;
		unsigned getWinlen () const;
	};
}

#endif