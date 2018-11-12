#ifndef SETTINGS_LEVEL_H
#define SETTINGS_LEVEL_H
#include "Level.h"
#include <map>
#include <string>
#include <fstream>
#include "tttIncludes.h"

class Settings : public Level{
	SDL_Renderer *rnd = nullptr;
	std::map<std::string, SDL_Texture *> textures;
	TTF_Font *font = nullptr;
	int rndWidth;
	int rndHeight;
	int activeBtn = 0;

	unsigned gameWidth = 3;
	unsigned gameHeight = 3;
	unsigned gameWinlen = 3;
	bool againstBot = true;
	bool playerFirst = true;

public:
	Settings (SDL_Renderer *rnd, std::map<std::string,
			  SDL_Texture *> textures, TTF_Font *font) :
		rnd(rnd), textures(textures), font(font){
		SDL_GetRendererOutputSize(rnd, &rndWidth, &rndHeight);
		std::ifstream fin ("res/prefs.tttp");
		fin >> gameWidth >> gameHeight >> gameWinlen
			>> againstBot >> playerFirst;
		fin.close();
	}

private:
	void savePrefs (){
		std::ofstream fout ("res/prefs.tttp");
		fout << gameWidth << std::endl <<
				gameHeight << std::endl <<
				gameWinlen << std::endl <<
				againstBot << std::endl <<
				playerFirst << std::endl;
		fout.close();
	}

	void drawBG (){
		SDL_RenderCopy(rnd, textures["MenuBG"], nullptr, nullptr);
		SDL_Rect rect;
		rect = {rndWidth / 12 * 4, rndHeight / 12,
				rndWidth / 12 * 4, rndHeight / 12};
		SDL_RenderCopy(rnd, textures["width"], nullptr, &rect);
		rect = {rndWidth / 12 * 4, rndHeight / 12 * 3,
				rndWidth / 12 * 4, rndHeight / 12};
		SDL_RenderCopy(rnd, textures["height"], nullptr, &rect);
		rect = {rndWidth / 12 * 4, rndHeight / 12 * 5,
				rndWidth / 12 * 4, rndHeight / 12};
		SDL_RenderCopy(rnd, textures["winlen"], nullptr, &rect);

		int len = std::to_string(gameWidth).size() * rndWidth / 25;
		rect = {(rndWidth - len) / 2, rndHeight / 12 * 2,
				len, rndHeight / 12};
		SDL_Surface *surf = TTF_RenderText_Blended(font,
			std::to_string(gameWidth).c_str(), SDL_Color{255, 220, 0, 255});
		SDL_Texture *text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		len = std::to_string(gameHeight).size() * rndWidth / 25;
		rect = {(rndWidth - len) / 2, rndHeight / 12 * 4,
				len, rndHeight / 12};
		surf = TTF_RenderText_Blended(font,
			std::to_string(gameHeight).c_str(), SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);

		len = std::to_string(gameWinlen).size() * rndWidth / 25;
		rect = {(rndWidth - len) / 2, rndHeight / 12 * 6,
				len, rndHeight / 12};
		surf = TTF_RenderText_Blended(font,
			std::to_string(gameWinlen).c_str(), SDL_Color{255, 220, 0, 255});
		text = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_RenderCopy(rnd, text, nullptr, &rect);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(surf);
	}

	void drawBTNS (int mouseX, int mouseY){
		int sBtnWidth = rndWidth / 12 ;
		int bBtnWidth = rndWidth / 12 * 4;
		int sBtnHeight = rndHeight / 12;

		activeBtn = 0;

		SDL_Rect rect;

		rect.x = rndWidth / 12;
		rect.y = rndHeight / 12 * 2;
		rect.w = sBtnWidth;
		rect.h = sBtnHeight;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["minusA"], nullptr, &rect);

			activeBtn = 1;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["minus"], nullptr, &rect);
		}

		rect.x = rndWidth / 12 * 10;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["plusA"], nullptr, &rect);

			activeBtn = 2;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["plus"], nullptr, &rect);
		}

		rect.y = rndHeight / 12 * 4;
		rect.x = rndWidth / 12;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["minusA"], nullptr, &rect);

			activeBtn = 3;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["minus"], nullptr, &rect);
		}

		rect.x = rndWidth / 12 * 10;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["plusA"], nullptr, &rect);

			activeBtn = 4;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["plus"], nullptr, &rect);
		}

		rect.y = rndHeight / 12 * 6;
		rect.x = rndWidth / 12;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["minusA"], nullptr, &rect);

			activeBtn = 5;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["minus"], nullptr, &rect);
		}

		rect.x = rndWidth / 12 * 10;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["plusA"], nullptr, &rect);

			activeBtn = 6;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["plus"], nullptr, &rect);
		}

		rect.w = bBtnWidth;
		rect.y = rndHeight / 12 * 8;
		rect.x = rndWidth / 12;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			if (againstBot){
				SDL_RenderCopy(rnd, textures["botA"], nullptr, &rect);
			}
			else{
				SDL_RenderCopy(rnd, textures["friendA"], nullptr, &rect);
			}

			activeBtn = 7;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			if (againstBot){
				SDL_RenderCopy(rnd, textures["bot"], nullptr, &rect);
			}
			else{
				SDL_RenderCopy(rnd, textures["friend"], nullptr, &rect);
			}
		}

		if (againstBot){
			rect.x = rndWidth / 12 * 7;
			if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
				mouseY >= rect.y && mouseY <= rect.y + rect.h){
				SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
				if (playerFirst){
					SDL_RenderCopy(rnd, textures["playerA"], nullptr, &rect);
				}
				else{
					SDL_RenderCopy(rnd, textures["botA"], nullptr, &rect);
				}

				activeBtn = 8;
			}
			else{
				SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
				if (playerFirst){
					SDL_RenderCopy(rnd, textures["player"], nullptr, &rect);
				}
				else{
					SDL_RenderCopy(rnd, textures["bot"], nullptr, &rect);
				}
			}
		}

		rect.x = rndWidth / 12 * 4;
		rect.y = rndHeight / 12 * 10;

		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["saveA"], nullptr, &rect);

			activeBtn = 9;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["save"], nullptr, &rect);
		}

		rect.x = rndWidth / 12;
		rect.w = rndHeight / 12 * 2;

		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["backA"], nullptr, &rect);

			activeBtn = 10;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["back"], nullptr, &rect);
		}
	}

	void update(int mouseX, int mouseY, bool &mouseDown, int &nextLevelNum){
		drawBG();
		drawBTNS(mouseX, mouseY);
		if (mouseDown){
			if (activeBtn == 1){
				if (gameWidth){
					gameWidth--;
				}
			}
			else if (activeBtn == 2){
				if (gameWidth < 100){
					gameWidth++;
				}
			}
			else if (activeBtn == 3){
				if (gameHeight){
					gameHeight--;
				}
			}
			else if (activeBtn == 4){
				if (gameHeight < 100){
					gameHeight++;
				}
			}
			else if (activeBtn == 5){
				if (gameWinlen){
					gameWinlen--;
				}
			}
			else if (activeBtn == 6){
				if (gameWinlen < 100){
					gameWinlen++;
				}
			}
			else if (activeBtn == 7){
				againstBot = !againstBot;
			}
			else if (activeBtn == 8){
				playerFirst = !playerFirst;
			}
			else if (activeBtn == 9){
				savePrefs();
			}
			else if (activeBtn == 10){
				nextLevelNum = 0;
			}
			mouseDown = 0;
		}
	}
};

#endif
