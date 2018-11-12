#include "TTT.h"

games::TTT::TTT () :
	width(3), height(3), winlen(3){
	field = std::vector<games::CELL> (width * height, games::CELL::EMPTY);
}

games::TTT::TTT (unsigned _width, unsigned _height, 
							 unsigned _winlen) :
	width(_width), height(_height), winlen(_winlen){
	field = std::vector<games::CELL> (width * height, games::CELL::EMPTY);
}

games::TTT::~TTT (){
}

void games::TTT::makeMove (unsigned cell){
	field[cell] = turn ? games::CELL::O : games::CELL::X;
	turn = !turn;
	moveNum++;
}

bool games::TTT::checkWin (unsigned cell){
	unsigned lineLen = 1;
	for (unsigned i = 1; (cell / width >= i) &&
		field[cell - width * i] == field[cell]; i++, lineLen++);
	for (unsigned i = 1; (cell / width + i < height) &&
		field[cell + width * i] == field[cell]; i++, lineLen++);
	if (lineLen >= winlen){
		gameEnded = true;
		winner = field[cell];
		return true;
	}
	lineLen = 1;
	for (unsigned i = 1; (cell % width >= i) &&
		field[cell - i] == field[cell]; i++, lineLen++);
	for (unsigned i = 1; (cell % width + i < width) &&
		field[cell + i] == field[cell]; i++, lineLen++);
	if (lineLen >= winlen){
		gameEnded = true;
		winner = field[cell];
		return true;
	}
	lineLen = 1;
	for (unsigned i = 1; (cell % width >= i) &&
		(cell / width >= i) &&
		field[cell - width * i - i] == field[cell]; i++, lineLen++);
	for (unsigned i = 1; (cell % width + i < width) &&
		(cell / width + i < height) &&
		field[cell + width * i + i] == field[cell]; i++, lineLen++);
	if (lineLen >= winlen){
		gameEnded = true;
		winner = field[cell];
		return true;
	}
	lineLen = 1;
	for (unsigned i = 1; (cell % width + i < width) &&
		(cell / width >= i) &&
		field[cell - width * i + i] == field[cell]; i++, lineLen++);
	for (unsigned i = 1; (cell % width >= i) &&
		(cell / width + i < height) &&
		field[cell + width * i - i] == field[cell]; i++, lineLen++);
	if (lineLen >= winlen){
		gameEnded = true;
		winner = field[cell];
		return true;
	}
	if (moveNum >= width * height){
		gameEnded = true;
		winner = games::CELL::EMPTY;
	}
	return false;
}

std::vector<games::CELL> games::TTT::getField () const{
	return field;
}

unsigned games::TTT::getMoveNum () const{
	return moveNum;
}

bool games::TTT::checkMove (unsigned cell) const{
	return field[cell] == games::CELL::EMPTY;
}

void games::TTT::unmakeMove (unsigned cell){
	field[cell] = games::CELL::EMPTY;
	turn = !turn;
	moveNum--;
}

unsigned games::TTT::getWidth () const{
	return width;
}

unsigned games::TTT::getHeight () const{
	return height;
}

unsigned games::TTT::getWinlen () const{
	return winlen;
}