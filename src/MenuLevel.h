#ifndef MENU_LEVEL_H
#define MENU_LEVEL_H
#include "Level.h"
#include <map>
#include <string>
#include "tttIncludes.h"


class Menu : public Level {
	SDL_Renderer *rnd;
	std::map<std::string, SDL_Texture *> textures;
	int rndWidth;
	int rndHeight;
	int activeBtn = 0;
	
public:
	Menu (SDL_Renderer *rnd, std::map<std::string, SDL_Texture *> textures) :
		rnd(rnd), textures(textures){
		SDL_GetRendererOutputSize(rnd, &rndWidth, &rndHeight);
	}
	
private:
	void drawBG (){
		SDL_RenderCopy(rnd, textures["MenuBG"], nullptr, nullptr);
		SDL_Rect rect {rndWidth / 4, 5, rndWidth / 2,  rndHeight / 10 * 3 - 10};
		SDL_RenderCopy(rnd, textures["TTT"], nullptr, &rect);
	}
	
	void drawBTNS (int mouseX, int mouseY){
		int btnWidth = rndWidth / 12 * 4;
		int btnHeight = rndHeight / 5;
		
		activeBtn = 0;
		
		SDL_Rect rect;
		rect.w = btnWidth;
		rect.h = btnHeight;
		rect.x = rndWidth / 12 * 4;
		rect.y = rndHeight / 10 * 3;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["PlayBtnA"], nullptr, &rect);
			
			activeBtn = 1;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["PlayBtn"], nullptr, &rect);
		}
		
		rect.y = rndHeight / 10 * 6;
		if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h){
			SDL_RenderCopy(rnd, textures["BtnA"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["SettBtnA"], nullptr, &rect);
			
			activeBtn = 2;
		}
		else{
			SDL_RenderCopy(rnd, textures["Btn"], nullptr, &rect);
			SDL_RenderCopy(rnd, textures["SettBtn"], nullptr, &rect);
		}
	}
	
public:
	void update (int mouseX, int mouseY, bool &mouseDown, int &nextLevelNum){
		drawBG();
		drawBTNS(mouseX, mouseY);
		if (mouseDown){
			if (activeBtn == 1){
				nextLevelNum = 1; //game level
			}
			else if (activeBtn == 2){
				nextLevelNum = 2; //settings level
			}
			mouseDown = 0;
		}
	}
};

#endif