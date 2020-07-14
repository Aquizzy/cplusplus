#include "hiscores.h"

Hiscores::Hiscores(MenuManager* _menuManager, Spritesheet* _spritesheet, SDL_Renderer* _renderer, int _score) {
	menuManager = _menuManager;
	spritesheet = _spritesheet;
	renderer = _renderer;
	getFile();
	scores[11] = _score;
	sort(scores, scores + 12, greater<>());
	scores[11] = 0;

	setFile();
}

Hiscores::~Hiscores() {
	menuManager = nullptr;
	spritesheet = nullptr;
	renderer = nullptr;
}

void Hiscores::setFile() {
	ofstream myfile("txt/scores.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			myfile << scores[i] << endl;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

void Hiscores::createFile() {
	ofstream myfile("txt/scores.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			myfile << i << endl;
		}
		myfile.close();
	}
}

void Hiscores::getFile() {
	string line;
	ifstream myfile("txt/scores.txt");
	if (myfile.fail()) {
		createFile();
	}
	else if (myfile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			getline(myfile, line);
			scores[i] = stoi(line);
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file";
	}
}

void Hiscores::input() {
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
				menuManager->currentMenu = menuManager->mainMenu;
				break;

			default:
				cout << "Player input switch is not working.";
				break;
			}
		}
	}
}

void Hiscores::draw() {
	SDL_RenderClear(renderer);

	spritesheet->drawUiBackground();
	spritesheet->drawUiBorder();
	spritesheet->drawFontUi("Hiscores", 231, 40, 30);
	spritesheet->drawBackground();
	spritesheet->drawBorder();

	for (int i = 0; i < 10; i++)
	{
		string test = "Player " + to_string(i) + ":                        " + to_string(scores[i]);
		spritesheet->drawFont(test.data(), 105, 85 + (i * 60), 30);
	}

	spritesheet->drawFont("Press enter to continue...", 121, 800, 30);

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void Hiscores::update() {

}




