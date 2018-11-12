#ifndef GAME_LAVEL_H
#define GAME_LEVEL_H
#include "Level.h"
#include "tttIncludes.h"
#include <string>
#include <map>
#include <fstream>
#include "TTT.h"
#include "TTTBot.h"

class Game : public Level{
	SDL_Renderer *rnd = nullptr;
	std::map<std::string, SDL_Texture *> textures;
	TTF_Font *font = nullptr;
	int rndWidth;
	int rndHeight;
	int cellWidth;
	int cellHeight;
	int fieldWidth;
	int fieldHeight;

	int gameWidth = 3;
	int gameHeight = 3;
	int gameWinlen = 3;
	bool againstBot = true;
	bool playerFirst = true;
	int activeCell = -1;
	int activeBtn = 0;

	games::TTT ttt;	//(gameWidth, gameHeight, gameWinlen);
	games::TTTB tttBot;	//(gameWidth, gameHeight, gameWinlen, 3, 2);

public:
	Game (SDL_Renderer *rnd, std::map<std::string, SDL_Texture *> textures,
		  TTF_Font *font) :
		rnd(rnd), textures(textures), font(font){
		SDL_GetRendererOutputSize(rnd, &rndWidth, &rndHeight);
		std::ifstream fin ("res/prefs.tttp");
		fin >> gameWidth >> gameHeight >> gameWinlen
			>> againstBot >> playerFirst;
		fin.close();

		cellWidth = gameWidth ? rndHeight / gameWidth : 0;
		cellHeight = gameHeight ? rndHeight / gameHeight : 0;
		fieldWidth = gameWidth * cellWidth;
		fieldHeight = gameHeight * cellHeight;

		ttt = games::TTT(gameWidth, gameHeight, gameWinlen);
		if (againstBot){
			tttBot = games::TTTB(gameWidth, gameHeight, gameWinlen, 4, 2);
		}
	}


private:
	void checkBtns (int mouseX, int mouseY){
		activeBtn = 0;
		int x = fieldWidth + (rndWidth - fieldWidth) / 6;
		int y = rndHeight / 12 * 10;
		int w = (rndWidth - fieldWidth) / 6 * 4;
		int h = rndHeight / 12;

		if (mouseX >= x && mouseX <= x + w &&
			mouseY >= y && mouseY <= y + h){
				activeBtn = 1;
		}

		y = rndHeight / 12 * 8;
		if (mouseX >= x && mouseX <= x + w &&
			mouseY >= y && mouseY <= y + h){
				activeBtn = 2;
		}
	}

	void checkCells (int mouseX, int mouseY){
		activeCell = -1;

		for (int i = 0; i < gameWidth * gameHeight; i++){
			int x = i % gameWidth * cellWidth;
			int y = i / gameWidth * cellHeight;

			if (mouseX >= x && mouseX < x + cellWidth &&
				mouseY >= y && mouseY < y + cellHeight){
				activeCell = i;
			}
		}
	}

	void drawField (){
		SDL_Rect rect {0, 0, rndWidth, rndHeight};
		SDL_RenderCopy(rnd, textures["MenuBG"], nullptr, &rect);
		rect = {0, 0, fieldWidth, fieldHeight};
		SDL_SetRenderDrawColor(rnd, 77, 77, 77, 255);
		SDL_RenderFillRect(rnd, &rect);

		SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
		for (int i = 1; i < gameWidth; i++){
			int x = i * cellWidth;
			SDL_RenderDrawLine(rnd, x, 0, x, fieldHeight);
		}
		for (int i = 1; i < gameHeight; i++){
			int y = i * cellHeight;
			SDL_RenderDrawLine(rnd, 0, y, fieldHeight, y);
		}

		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, 0,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};

		SDL_Surface *surf = TTF_RenderText_Blended(font, "Prefs",
												   SDL_Color{255, 220, 0, 255});
		SDL_Texture *text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, rndHeight / 12,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};

		surf = TTF_RenderText_Blended(font,
				("Width: " + std::to_string(gameWidth)).c_str(),
				SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, rndHeight / 12 * 2,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};

		surf = TTF_RenderText_Blended(font,
				("Height: " + std::to_string(gameHeight)).c_str(),
				SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, rndHeight / 12 * 3,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};

		surf = TTF_RenderText_Blended(font,
				("Winlen: " + std::to_string(gameWinlen)).c_str(),
				SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, rndHeight / 12 * 4,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};

		surf = TTF_RenderText_Blended(font,
				("Move: " + std::to_string(ttt.getMoveNum())).c_str(),
				SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, rndHeight / 12 * 5,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};
		std::string t = (ttt.getMoveNum() % 2) ? "O" : "X";
		surf = TTF_RenderText_Blended(font,
				("Turn: " + t).c_str(),
				SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);
	}

	void drawFigures (int mouseX, int mouseY){
		std::vector<games::CELL> field = ttt.getField();
		SDL_Rect rect;
		rect.w = cellWidth;
		rect.h = cellHeight;
		for (size_t i = 0; i < field.size(); i++){
			rect.x = i % gameWidth * cellWidth;
			rect.y = i / gameWidth * cellHeight;

			if (field[i] == games::CELL::X){
				SDL_RenderCopy(rnd, textures["xtext"], nullptr, &rect);
			}
			else if (field[i] == games::CELL::O){
				SDL_RenderCopy(rnd, textures["otext"], nullptr, &rect);
			}

			if ((int)i == activeCell){
				SDL_SetRenderDrawColor(rnd, 255, 220, 0, 128);
				SDL_RenderFillRect(rnd, &rect);
			}
		}
	}

	void drawBtns (int mouseX, int mouseY){

		SDL_Rect rect;
		rect = {fieldWidth + (rndWidth - fieldWidth) / 6, rndHeight / 12 * 10,
				(rndWidth - fieldWidth) / 6 * 4, rndHeight / 12};

		if (activeBtn == 1){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["backA"], nullptr, &rect);

		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["back"], nullptr, &rect);
		}

		rect.y = rndHeight / 12 * 8;
		if (activeBtn == 2){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["replayA"], nullptr, &rect);

		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["replay"], nullptr, &rect);
		}
	}

public:
	void update(int mouseX, int mouseY, bool &mouseDown, int &nextLevelNum){
		bool gameEnded = ttt.gameEnded;
		unsigned moveNum = ttt.getMoveNum();

		checkBtns(mouseX, mouseY);
		checkCells(mouseX, mouseY);

		if (againstBot && !gameEnded){
			if (playerFirst == moveNum % 2){
				tttBot.setPos(ttt);
				unsigned bMove = tttBot.getMove();
				ttt.makeMove(bMove);
				ttt.checkWin(bMove);
				gameEnded = ttt.gameEnded;
				moveNum = ttt.getMoveNum();
			}
		}
		if (mouseDown){
			if (activeBtn == 1){
				nextLevelNum = 0;
			}
			else if (activeBtn == 2){
				nextLevelNum = 1;
			}
			else if (!gameEnded && activeCell != -1){
				if (!againstBot || (playerFirst != moveNum % 2)){
					if (ttt.checkMove(activeCell)){
						ttt.makeMove(activeCell);
						ttt.checkWin(activeCell);
					}
				}
			}
			mouseDown = 0;
		}

		drawField();
		drawFigures(mouseX, mouseY);
		drawBtns(mouseX, mouseY);

		if (gameEnded){
			if (ttt.winner == games::CELL::X){
				SDL_Rect rect {0, fieldHeight / 3, fieldWidth, fieldHeight / 3};
				SDL_RenderCopy(rnd, textures["xWin"], nullptr, &rect);
			}
			else if (ttt.winner == games::CELL::O){
				SDL_Rect rect {0, fieldHeight / 3, fieldWidth, fieldHeight / 3};
				SDL_RenderCopy(rnd, textures["oWin"], nullptr, &rect);
			}
			else if (ttt.winner == games::CELL::EMPTY){
				SDL_Rect rect {0, fieldHeight / 3, fieldWidth, fieldHeight / 3};
				SDL_RenderCopy(rnd, textures["draw"], nullptr, &rect);
			}
		}
	}
};

#endif
