#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdint.h>
#include <iostream>

#include "gameloop.h"
#include "menu.h"
#include "menuManager.h"
#include "hiscores.h"

using std::cout;
using std::cin;

bool init();

SDL_Window* window;
SDL_Renderer* renderer;
Spritesheet* spritesheet;
MenuManager* menuManager;

//	coudl make this a custom data type for score, name and such.
int score = 0;

const uint16_t WIDTH = 576;
const uint16_t HEIGHT = 1024;

bool closeWindow = false;


int main(int argc, char* args[])
{
	if (!init()) {
		cout << "failed to init" << std::endl;
		return 1;
	}

	menuManager = new MenuManager();	
	menuManager->currentMenu = menuManager->mainMenu;

	while (!menuManager->getCloseWindow()) {
		switch (menuManager->currentMenu)
		{
			///	check input here.
		case menuManager->mainMenu:
		{
			Menu* menu = new Menu(spritesheet, renderer, menuManager);
			while (!menu->getMenuOver()) {
				menu->input();
				menu->update();
				menu->draw();
			}
			delete menu;
			menu = NULL;
		}
			break;

		case menuManager->gameplay:
		{
			Gameloop* loop = new Gameloop(renderer, spritesheet, menuManager);
			loop->init();
			while (!loop->getGameOver()) {
				loop->input();
				loop->update();
				loop->draw();
			}
			score = loop->getPlayer()->getScore();
			delete loop;
			loop = NULL;
		}
		break;

		case menuManager->hiscores: 
		{
			Hiscores* hiscores = new Hiscores(menuManager, spritesheet, renderer, score);
			while (!hiscores->getMenuOver()) {
				hiscores->input();
				hiscores->update();
				hiscores->draw();
			}
			delete hiscores;
			hiscores = NULL;
		}
			break;

		case 4:
			break;
		}
	}
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();

	return 0;
}

bool init() {
	bool flag = true;
	///	Init SDL.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: ", SDL_GetError();
		flag = false;
	}
	else
	{	///	Set texture filerting to linear.
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
			cout << "Warning: Linear texture filterint not enabled!";
		}
		///	Create window.
		window = SDL_CreateWindow("2D Shooter Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL Error: ", SDL_GetError();
			flag = false;
		}
		else
		{	///	Create renderer.
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				cout << " Renderer could not be created! SDL Error: ", SDL_GetError();
				flag = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

				///	Init PNG Loading.
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					cout << "SDL_image could not initalize! SDL_image error: ", IMG_GetError();
					flag = false;
				}
			}
		}
	}
	if (TTF_Init() < 0) cout << "Coulnt initalise TTF";
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) cout << "Could not initalise mixer." << Mix_GetError();
	spritesheet = new Spritesheet(renderer);

	return flag;
}

