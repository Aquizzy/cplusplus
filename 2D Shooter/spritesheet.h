#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

using std::cout;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture(SDL_Renderer*);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string);

	SDL_Texture* getTexture(int, int);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(SDL_Rect*, SDL_Rect*);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* renderer;

	//Image dimensions
	int mWidth;
	int mHeight;
};

class Spritesheet {

public:
	Spritesheet(SDL_Renderer*);

	void draw();
	void draw(int, SDL_Rect*);
	void drawHealth(int, SDL_Rect*);
	void drawBackground();
	void drawUiBackground();
	void drawUi(int, SDL_Rect*);
	void drawUiBorder();
	void drawBorder();
	void drawLogo();

	void drawFont(const char*, int, int, int);
	void drawFontUi(const char*, int, int, int);
	

	void setClips(int);
	void setHealthClips(int);
	void setBackgroundClips();
	void setBuildingClips();
	void setLogoClips();
	void setBorderClips(int,int,int);
	
	void createBorder(int,int,int,int,int);
	void createBackground();
	void createUIBackground();

	~Spritesheet();

	SDL_Renderer* renderer;

	SDL_Rect backgroundClip;
	LTexture* backgroundTexture;
	SDL_Rect backgroundPos[5][5];

	SDL_Rect characterClip;
	LTexture* characterTextures;

	SDL_Rect healthClip;
	LTexture* healthTextures;

	SDL_Rect borderClip[9];
	LTexture* borderTexture;
	SDL_Rect borderPos[9];

	SDL_Rect backgroundUiPos[5][2];

	SDL_Rect buildingClip;
	LTexture* buildingTexture;
	SDL_Rect buildingPos[4];

	SDL_Rect emptyBuildingClip;
	LTexture* emptyBuildingTexture;
	SDL_Rect emptyBuildingPos;

	SDL_Rect logoClip;
	LTexture* logoTexture;
	SDL_Rect logoPos;

	void loadMedia();

	enum Sprites
	{
		enemy1,
		enemy2,
		playerBullet,
		spaceShip,
		playerShip,
		playerShipPlaceholder,
		empty1,
		enemy3,
		enemy4,
		spaceShipBullet0,
		leftBarrier100,
		rightBarrier100,
		spaceShipBullet1,
		empty2,
		enemy5,
		enemy6,
		bulletHit,
		leftBarrier75,
		rightBarrier75,
		empty3,
		empty4,
		enemy7,
		enemy8,
		bulletExplode1,
		leftBarrier50,
		rightBarrier50,
		leftArrow,
		rightArrow,
		enemy9,
		enemy10,
		bulletExplode2,
		leftBarrier25,
		rightBarrier25,
		empty5, 
		empty6,
		SPRITELENGTH
	};
	Sprites sprites;

	SDL_Rect uiViewport;
	SDL_Rect gameViewport;

};