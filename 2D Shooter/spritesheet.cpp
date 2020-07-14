#include "spritesheet.h"

Spritesheet::Spritesheet(SDL_Renderer* _renderer) {
	renderer = _renderer;
	characterTextures = new LTexture(renderer);
	healthTextures = new LTexture(renderer);
	backgroundTexture = new LTexture(renderer);
	borderTexture = new LTexture(renderer);
	buildingTexture = new LTexture(renderer);
	emptyBuildingTexture = new LTexture(renderer);
	logoTexture = new LTexture(renderer);

	loadMedia();
	createBackground();
	createUIBackground();

	uiViewport = { 0,0,576,114 };
	gameViewport = { 0, 114, 576, 910 };

}

///	@warning cant call this destructor something breaks.
Spritesheet::~Spritesheet() {
	renderer = NULL;
	delete backgroundTexture;
	backgroundTexture = NULL;
	delete characterTextures;
	characterTextures = NULL;
	delete healthTextures;
	healthTextures = NULL;
	delete borderTexture;
	borderTexture = NULL;
	delete buildingTexture;
	buildingTexture = NULL;
	delete emptyBuildingTexture;
	emptyBuildingTexture = NULL;
}

void Spritesheet::setClips(int _imageNo) {
	int mod, div;

	///	Height 
	div = _imageNo / 7;

	///	Width
	mod = _imageNo % 7;

	characterClip.x = mod * 16;
	characterClip.y = div * 16;
	characterClip.w = 16;
	characterClip.h = 16;
}

void Spritesheet::setHealthClips(int _healthNo) {
	healthClip.x = 0;
	healthClip.y = _healthNo * 16;
	healthClip.w = 32;
	healthClip.h = 16;
}

void Spritesheet::setBackgroundClips() {
	backgroundClip = { 0,0,64,64 };
}

void Spritesheet::setBorderClips(int _border, int _width, int _height) {
	borderClip[0] = { 0, 0, _border, _border };
	borderClip[1] = { _border, 0, _width - (2 * _border), _border };
	borderClip[2] = { _width - _border, 0, _border, _border };

	borderClip[3] = { 0, _border, _border, _height - (2 * _border) };
	borderClip[4] = { _border,_border, _width - (2 * _border),_height - (2 * _border) };
	borderClip[5] = { _width - _border, _border, _border, _height - (2 * _border) };

	borderClip[6] = { 0, _height - _border, _border, _border };
	borderClip[7] = { _border, _height - _border, _width - (2 * _border), _border };
	borderClip[8] = { _width - _border, _height - _border, _border, _border };
}

void Spritesheet::createBorder(int _x, int _y, int _w, int _h, int _b) {
	borderPos[0] = { _x,_y,_b,_b };
	borderPos[1] = { _x + _b,_y,_w - (2 * _b),_b };
	borderPos[2] = { _x + (_w - _b), _y, _b, _b };
	borderPos[3] = { _x, _y + _b, _b, _h - (2 * _b) };
	borderPos[4] = { _x + _b, _y + _b, _w - (2 * _b), _h - (2 * _b) };
	borderPos[5] = { _x + (_w - _b),_y + _b, _b, _h - (2 * _b) };
	borderPos[6] = { _x, _y + (_h - _b), _b, _b };
	borderPos[7] = { _x + _b,_y + (_h - _b), _w - (2 * _b),_b };
	borderPos[8] = { _x + (_w - _b), _y + (_h - _b), _b, _b };
}

void Spritesheet::setBuildingClips() {
	buildingClip = { 0,0,64,64 };
	emptyBuildingClip = { 0,0,64,64 };
}

void Spritesheet::setLogoClips() {
	logoClip = { 0,0,64,32 };
	logoPos = { 53, 150, 476,238 };
}

void Spritesheet::draw() {
}

void Spritesheet::draw(int item, SDL_Rect* _rect) {
	SDL_RenderSetViewport(renderer, &gameViewport);
	setClips(item);
	characterTextures->render(_rect, &characterClip);
}

void Spritesheet::drawUi(int item, SDL_Rect* _rect) {
	SDL_RenderSetViewport(renderer, &uiViewport);
	setClips(item);
	characterTextures->render(_rect, &characterClip);
}

void Spritesheet::drawHealth(int _health, SDL_Rect* _rect) {
	SDL_RenderSetViewport(renderer, &uiViewport);
	setHealthClips(_health);
	healthTextures->render(_rect, &healthClip);
}

void Spritesheet::drawBackground() {
	SDL_RenderSetViewport(renderer, &gameViewport);
	for (uint8_t i = 0; i < 5; i++)
	{
		for (uint8_t x = 0; x < 5; x++)
		{
			backgroundTexture->render(&backgroundPos[i][x], &backgroundClip);
		}
	}
	for (uint8_t a = 0; a < 4; a++)
	{
		buildingTexture->render(&buildingPos[a], &backgroundClip);
	}
	emptyBuildingTexture->render(&emptyBuildingPos, &emptyBuildingClip);
}

void Spritesheet::createBackground() {
	setBackgroundClips();
	setBuildingClips();
	for (uint8_t i = 0; i < 5; i++)
	{
		for (uint8_t x = 0; x < 5; x++)
		{
			backgroundPos[i][x] = { i * 128, x * 128,128,128 };
		}
	}
	for (uint8_t a = 0; a < 4; a++)
	{
		buildingPos[a] = { a * 144, 500,144,144 };
	}
	emptyBuildingPos = { 0,644, 576, 266 };
}

void Spritesheet::drawUiBackground() {
	SDL_RenderSetViewport(renderer, &uiViewport);
	for (uint8_t i = 0; i < 5; i++)
	{
		for (uint8_t x = 0; x < 2; x++)
		{
			backgroundTexture->render(&backgroundUiPos[i][x], &backgroundClip);
		}
	}
}

void Spritesheet::drawBorder() {
	SDL_RenderSetViewport(renderer, &gameViewport);
	setBorderClips(3, 48, 48);
	createBorder(20, 20, 536, 700, 3);
	for (uint8_t y = 0; y < 9; y++)
	{
		borderTexture->render(&borderPos[y], &borderClip[y]);
	}
}

void Spritesheet::drawUiBorder() {
	SDL_RenderSetViewport(renderer, &uiViewport);
	setBorderClips(3, 48, 48);
	createBorder(20, 20, 536, 74, 3);
	for (uint8_t y = 0; y < 9; y++)
	{
		borderTexture->render(&borderPos[y], &borderClip[y]);
	}
}

void Spritesheet::drawLogo() {
	SDL_RenderSetViewport(renderer, &gameViewport);
	setLogoClips();
	logoTexture->render(&logoPos, &logoClip);

}

void Spritesheet::drawFont(const char* _msg, int _x, int _y, int _size) {
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", _size);
	if (font == NULL) cout << "UI drawFont error: " << TTF_GetError();
	SDL_Color color;
	color.r = 154;
	color.g = 217;
	color.b = 65;
	color.a = 255;

	SDL_Rect rect;
	surface = TTF_RenderText_Solid(font, _msg, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.x = _x;
	rect.y = _y;
	rect.h = surface->h;
	rect.w = surface->w;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, 0, &rect);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void Spritesheet::drawFontUi(const char* _msg, int _x, int _y, int _size) {
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", _size);
	if (font == NULL) cout << "UI drawFont error: " << TTF_GetError();
	SDL_Color color;
	color.r = 154;
	color.g = 217;
	color.b = 65;
	color.a = 255;

	SDL_Rect rect;
	surface = TTF_RenderText_Solid(font, _msg, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.x = _x;
	rect.y = _y;
	rect.h = surface->h;
	rect.w = surface->w;

	SDL_FreeSurface(surface);
	SDL_RenderSetViewport(renderer, &uiViewport);
	SDL_RenderCopy(renderer, texture, 0, &rect);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void Spritesheet::createUIBackground() {
	setBackgroundClips();
	for (uint8_t i = 0; i < 5; i++)
	{
		for (uint8_t x = 0; x < 2; x++)
		{
			backgroundUiPos[i][x] = { i * 128, x * 128,128,128 };
		}
	}
}

LTexture::LTexture(SDL_Renderer* _renderer)
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	renderer = _renderer;
}

LTexture::~LTexture()
{
	//Deallocate
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
	}
	mTexture = NULL;
	renderer = NULL;
}

bool LTexture::loadFromFile(std::string path)
{
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	///Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

SDL_Texture* LTexture::getTexture(int x, int y) {
	return NULL;
}

void LTexture::render(SDL_Rect* _size, SDL_Rect* clip)
{
	////Set rendering space and render to screen
	//SDL_Rect renderQuad = { x, y, 64, 64 };

	//Render to screen
	SDL_RenderCopy(renderer, mTexture, clip, _size);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

void Spritesheet::loadMedia()
{
	//Load sprite sheet texture
	if (!characterTextures->loadFromFile("images/spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
	}
	//Load sprite sheet texture
	if (!healthTextures->loadFromFile("images/healthsheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
	}
	if (!backgroundTexture->loadFromFile("images/background.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
	}
	if (!borderTexture->loadFromFile("images/border.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
	}
	if (!buildingTexture->loadFromFile("images/buildings.png")) {
		cout << "Failed to load buildings.png";
	}
	if (!emptyBuildingTexture->loadFromFile("images/empty.png")) {
		cout << "Failed to load buildings.png";
	}
	if (!logoTexture->loadFromFile("images/logo.png")) {
		cout << "Failed to load buildings.png";
	}

}

