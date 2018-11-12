#include "TTTBot.h"

games::TTTB::TTTB () :
	botD(3), rad(2){}

games::TTTB::TTTB (unsigned _width, unsigned _height, unsigned _winlen,
					   unsigned _botD, unsigned _rad) :
	botD(_botD), rad(_rad){
	ttt = games::TTT(_width, _height, _winlen);
}

games::TTTB::~TTTB (){
}

void games::TTTB::setPos(games::TTT const &other){
	ttt = other;
}

bool games::TTTB::checkCell (unsigned cell){
	std::vector<games::CELL> field = ttt.getField();
	if (field[cell] != games::CELL::EMPTY){
		return false;
	}
	if (ttt.getMoveNum() < 1){
		return true;
	}
	unsigned width = ttt.getWidth();
	unsigned height = ttt.getHeight();
	for (unsigned i = 0; i < width * height; i++){
		if ((i != cell) && (field[i] != games::CELL::EMPTY) &&
		    (i % width <= cell % width + rad &&
			cell % width <= i % width + rad &&
			i / width <= cell / width + rad &&
			cell / width <= i / width + rad)){
			return true;
		}
	}
	return false;
}

unsigned games::TTTB::getMove (){
	std::srand(time(nullptr));
	bool botFig = ttt.getMoveNum() % 2;
	int bestVal = INT_MIN;
	unsigned width = ttt.getWidth();
	unsigned height = ttt.getHeight();
	if (!ttt.getMoveNum() && (width * height) > 25){
		return rand() % (width * height);
	}
	std::vector<unsigned> goodCells;
	for (unsigned i = 0; i < width * height; i++){
		if (checkCell(i)){
			ttt.makeMove(i);
			int tVal = alphaBeta(botFig, botD, i);
			ttt.unmakeMove(i);
			if (tVal > bestVal){
				bestVal = tVal;
				goodCells.clear();
			}
			if (tVal == bestVal){
				goodCells.push_back(i);
			}
		}
	}

	unsigned res = goodCells[rand() % goodCells.size()];
	return res;
}

int games::TTTB::alphaBeta(bool botFig, unsigned depth,
								   unsigned prevMove, int a, int b){
	bool turn = ttt.getMoveNum() % 2;
	unsigned width = ttt.getWidth();
	unsigned height = ttt.getHeight();
	if (ttt.checkWin(prevMove)){
		return (botFig == turn ? -1 : 1) * (depth + 1);
	}
	if (ttt.getMoveNum() == width * height || !depth){
		return 0;
	}
	if (botFig == turn){
		int value = INT_MIN;
		for (unsigned i = 0; i < width * height; i++){
			if (checkCell(i)){
				ttt.makeMove(i);
				value = std::max(value, alphaBeta(botFig, depth - 1, i, a, b));
				ttt.unmakeMove(i);
				a = std::max(a, value);
				if (a >= b){
					break;
				}
			}
		}
		return value;
	}
	else{
		int value = INT_MAX;
		for (unsigned i = 0; i < width * height; i++){
			if (checkCell(i)){//ttt.checkMove(i)
				ttt.makeMove(i);
				value = std::min(value, alphaBeta(botFig, depth - 1, i, a, b));
				ttt.unmakeMove(i);
				b = std::min(b, value);
				if (a >= b){
					break;
				}
			}
		}
		return value;
	}
}