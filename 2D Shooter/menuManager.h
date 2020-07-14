#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

class MenuManager {
public:

	MenuManager() {};
	
	bool getCloseWindow() { return closeWindow; }
	void setCloswWindow() { closeWindow = true; }

	enum MenuOptions {
		mainMenu,
		gameplay,
		hiscores
	};

	MenuOptions menuOptions;
	int currentMenu;
	
	~MenuManager() {};

private:
	bool closeWindow = false;
};