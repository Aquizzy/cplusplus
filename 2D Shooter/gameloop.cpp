#include "gameloop.h"

///	@warning Empty constructor body.
Gameloop::Gameloop(SDL_Renderer* _renderer, Spritesheet* _spritesheet, MenuManager* _menuManager) {
	renderer = _renderer;
	spritesheet = _spritesheet;
	menuManager = _menuManager;

	cout << "LEFT ARROW TO MOVE LEFT " << endl;
	cout << "RIGHT ARROW TO MOVE RIGHT " << endl;
	cout << "SPACE TO SHOOT ARROW " << endl;
	cout << "A TO LOSE HEALTH " << endl;
}

///	Destroys the game window and renderer. Quits all SDL subsystems.
Gameloop::~Gameloop() {
	delete ui;
	ui = nullptr;
	delete barrierManager;
	barrierManager = nullptr;
	delete bulletManager;
	bulletManager = nullptr;
	delete player;
	player = nullptr;
	delete enemyManager;
	enemyManager = nullptr;
	spritesheet = nullptr;
	delete soundManager;
	soundManager = nullptr;
	delete collision;
	collision = nullptr;
	renderer = nullptr;
	window = nullptr;
}

///	Update the player, enemies and bullets.
void Gameloop::update() {
	player->update();
	enemyManager->update();
	if(bulletManager->isShooting()) bulletManager->update();
	collision->update();
}

///	Draws player, barrier, enemies, ui and bullets on the window.
void Gameloop::draw() {
	SDL_RenderClear(renderer);

	spritesheet->drawBackground();
	spritesheet->drawUiBackground();
	player->draw();
	barrierManager->draw();
	enemyManager->draw();
	ui->draw();
	if (bulletManager->isShooting()) bulletManager->draw();

	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

///	Check the keyboard for input. If any is detected it will empty off the queue. 
///	Methods such as playerMove and and shoot are called here.
void Gameloop::input() {
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			setGameOver();
			menuManager->setCloswWindow();
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				break;

			case SDLK_SPACE:
				bulletManager->shoot();
				soundManager->playShot();
				break;

			case SDLK_LEFT:
				player->playerMovement(-1);
				break;

			case SDLK_RIGHT:
				player->playerMovement(1);
				break;
			case SDLK_a:
				player->loseHealth(1);
				break;

			default:
				cout << "Player input switch is not working.";
				break;
			}
		}
	}
}

///	Initalises all the SDL subsystems, windows, sound and images that will be used.
///	Also creates all the classes the game needs to run.
bool Gameloop::init() {
	bool success = true;
	
	soundManager = new SoundManager();
	spritesheet = new Spritesheet(renderer);
	ui = new UI(renderer, spritesheet);
	player = new Player(ui, spritesheet, menuManager, this);
	barrierManager = new BarrierManager(spritesheet);
	bulletManager = new BulletManager(player, spritesheet);
	enemyManager = new EnemyManager(spritesheet, ui);
	collision = new Collision(bulletManager, enemyManager, barrierManager, player);

	return success;
};


