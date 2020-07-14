#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "menuManager.h"
#include "spritesheet.h"

using namespace std;

class MenuManager;
class Spritesheet;

class Hiscores {

public:

	Hiscores(MenuManager*, Spritesheet*, SDL_Renderer*, int);

	void input();
	void draw();
	void update();

	bool getMenuOver() { return menuOver; }
	void setMenuOver() { menuOver = true; }

	void getFile();
	void setFile();
	void createFile();
	
	~Hiscores();

private:

	MenuManager* menuManager;
	Spritesheet* spritesheet;
	SDL_Renderer* renderer;

	SDL_Event e;

	int scores[11];

	bool menuOver = false;

};