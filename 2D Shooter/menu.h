#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "spritesheet.h"
#include "menuManager.h"

using namespace std;

class Spritesheet;
class MenuManager;

class Menu {

public:

	Menu(Spritesheet*, SDL_Renderer*, MenuManager*);

	void draw();
	void update();
	void input();

	bool getMenuOver() { return menuOver; }
	void setMenuOver() { menuOver = true; }

	~Menu();

private:

	MenuManager* menuManager;
	Spritesheet* spritesheet;
	SDL_Renderer* renderer;

	SDL_Event e;

	bool menuOver = false;

};

