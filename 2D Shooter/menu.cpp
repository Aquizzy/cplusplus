#include "menu.h"

Menu::Menu(Spritesheet* _spritesheet, SDL_Renderer* _renderer, MenuManager* _menuManager) {
	spritesheet = _spritesheet;
	renderer = _renderer;
	menuManager = _menuManager;
}

Menu::~Menu() {

}

void Menu::draw() {
	SDL_RenderClear(renderer);

	spritesheet->drawUiBackground();
	spritesheet->drawBackground();
	spritesheet->drawFont("Press enter to play...", 151, 800, 30);
	spritesheet->drawLogo();

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void Menu::update() {
}

void Menu::input() {
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			setMenuOver();
			menuManager->setCloswWindow();
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				menuOver = true;
				menuManager->currentMenu = menuManager->gameplay;
				break;

			default:
				cout << "Player input switch is not working.";
				break;
			}
		}
	}

}