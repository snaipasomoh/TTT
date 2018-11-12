#ifndef APP_GUI
#define APP_GUI
#include <iostream>
#include "tttIncludes.h"
#include "MenuLevel.h"
#include "SettingsLevel.h"
#include "GameLevel.h"

#define WINWIDTH 1280
#define WINHEIGHT 960
#define FPS 60

class AppGUI{
	SDL_Window *wnd = nullptr;
	SDL_Renderer *rnd = nullptr;
	std::map<std::string, SDL_Texture *> textures;
	TTF_Font *font = nullptr;

//	int const WINWIDTH = 1280; //640
//	int const WINHEIGHT = 960; //480

public:
	AppGUI (){
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
	}

	~AppGUI (){
		for(auto pair : textures){
			if(pair.second) {SDL_DestroyTexture(pair.second);}
		}
		if (rnd) {SDL_DestroyRenderer(rnd);}
		if (wnd) {SDL_DestroyWindow(wnd);}
		SDL_Quit();
		TTF_Quit();
	}

private:
	void loadFont (){
		font = TTF_OpenFont("res/data-latin.ttf", 90);
		if (!font){
			throw std::runtime_error(TTF_GetError());
		}
	}

	void loadTextures (){
		SDL_Surface *surf = IMG_Load("res/winIcon.png");
		SDL_SetWindowIcon(wnd, surf);
		SDL_FreeSurface(surf);

		surf = IMG_Load("res/btnActive.png");
		SDL_Texture *text = SDL_CreateTextureFromSurface(rnd, surf);
		if (!text){
			throw std::runtime_error(IMG_GetError());
		}
		textures["BtnA"] = text;
		SDL_FreeSurface(surf);

		surf = IMG_Load("res/btnNonActive.png");
		text = SDL_CreateTextureFromSurface(rnd, surf);
		if (!text){
			throw std::runtime_error(IMG_GetError());
		}
		textures["Btn"] = text;
		SDL_FreeSurface(surf);

		surf = IMG_Load("res/MenuBG.png");
		text = SDL_CreateTextureFromSurface(rnd, surf);
		if (!text){
			throw std::runtime_error(IMG_GetError());
		}
		textures["MenuBG"] = text;
		SDL_FreeSurface(surf);

		surf = IMG_Load("res/Xtext.png");
		text = SDL_CreateTextureFromSurface(rnd, surf);
		if (!text){
			throw std::runtime_error(IMG_GetError());
		}
		textures["xtext"] = text;
		SDL_FreeSurface(surf);

		surf = IMG_Load("res/Otext.png");
		text = SDL_CreateTextureFromSurface(rnd, surf);
		if (!text){
			throw std::runtime_error(IMG_GetError());
		}
		textures["otext"] = text;
		SDL_FreeSurface(surf);

		surf = TTF_RenderText_Blended(font, "TIC-TAC-TOE",
									  SDL_Color{255, 220, 0, 255});
		textures["TTT"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Play",
									  SDL_Color{255, 255, 255, 255});
		textures["PlayBtnA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Play",
									  SDL_Color{255, 220, 0, 255});
		textures["PlayBtn"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Settings",
									  SDL_Color{255, 255, 255, 255});
		textures["SettBtnA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Settings",
									  SDL_Color{255, 220, 0, 255});
		textures["SettBtn"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Width",
									  SDL_Color{255, 220, 0, 255});
		textures["width"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Height",
									  SDL_Color{255, 220, 0, 255});
		textures["height"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Winlen",
									  SDL_Color{255, 220, 0, 255});
		textures["winlen"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "+",
									  SDL_Color{255, 220, 0, 255});
		textures["plus"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "+",
									  SDL_Color{255, 255, 255, 255});
		textures["plusA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "-",
									  SDL_Color{255, 220, 0, 255});
		textures["minus"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "-",
									  SDL_Color{255, 255, 255, 255});
		textures["minusA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Bot",
									  SDL_Color{255, 220, 0, 255});
		textures["bot"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Bot",
									  SDL_Color{255, 255, 255, 255});
		textures["botA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Friend",
									  SDL_Color{255, 220, 0, 255});
		textures["friend"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Friend",
									  SDL_Color{255, 255, 255, 255});
		textures["friendA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Player",
									  SDL_Color{255, 220, 0, 255});
		textures["player"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Player",
									  SDL_Color{255, 255, 255, 255});
		textures["playerA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Save",
									  SDL_Color{255, 220, 0, 255});
		textures["save"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Save",
									  SDL_Color{255, 255, 255, 255});
		textures["saveA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Back",
									  SDL_Color{255, 220, 0, 255});
		textures["back"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Back",
									  SDL_Color{255, 255, 255, 255});
		textures["backA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Replay",
									  SDL_Color{255, 220, 0, 255});
		textures["replay"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Replay",
									  SDL_Color{255, 255, 255, 255});
		textures["replayA"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "X wins",
									  SDL_Color{255, 220, 0, 255});
		textures["xWin"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "O wins",
									  SDL_Color{255, 220, 0, 255});
		textures["oWin"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);
		surf = TTF_RenderText_Blended(font, "Draw",
									  SDL_Color{255, 220, 0, 255});
		textures["draw"] = SDL_CreateTextureFromSurface(rnd, surf);
		SDL_FreeSurface(surf);

		SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);
	}

public:
	void start(){
		wnd = SDL_CreateWindow("TicTacToe",
							   SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED,
							   WINWIDTH, WINHEIGHT, 0);
		rnd = SDL_CreateRenderer(wnd, -1, 0);
		loadFont();
		loadTextures();

		bool Exit = false;
		int mouseX = 0;
		int mouseY = 0;
		bool mouseDown = false;
		Level *currLevel = new Menu(rnd, textures);
		int nextLevelNum = -1;
		while(!Exit){
			SDL_Event event;
			while(SDL_PollEvent(&event)){
				if(event.type == SDL_QUIT){
					delete currLevel;
					Exit = true;
					break;
				}
				else if(event.type == SDL_MOUSEMOTION){
					mouseX = event.motion.x;
					mouseY = event.motion.y;
				}
				else if(event.type == SDL_MOUSEBUTTONDOWN){
					mouseDown = true;
				}
			}

			if (Exit){
				break;
			}

			Uint32 start = SDL_GetTicks();

			SDL_RenderClear(rnd);
			currLevel->update(mouseX, mouseY, mouseDown, nextLevelNum);
			if (nextLevelNum == 0){
				delete currLevel;
				currLevel = new Menu(rnd, textures);
				nextLevelNum = -1;
			}
			else if (nextLevelNum == 1){
				delete currLevel;
				currLevel = new Game(rnd, textures, font);
				nextLevelNum = -1;
			}
			else if (nextLevelNum == 2){
				delete currLevel;
				currLevel = new Settings(rnd, textures, font);
				nextLevelNum = -1;
			}
			SDL_RenderPresent(rnd);

			Uint32 end = SDL_GetTicks();

			if (1000 / FPS > end - start){
				SDL_Delay(1000 / FPS - (end - start));
			}
		}
	}
};

#endif
