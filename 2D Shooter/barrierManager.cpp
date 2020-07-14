#include "barrierManager.h"

///	Sets all the positions, widths for the barriers so they can be drawn on the screen.
///	@param _spritesheet This is a reference to the spritesheet which will draw to the screen.
///	@note Using one loop with modulo 64 to determing left or right could increase readability.
BarrierManager::BarrierManager(Spritesheet* _spritesheet) {
	spritesheet = _spritesheet;
	for (uint8_t i = 0; i < 4; i++)
	{
		barrierPos[i] = { 64 + (i * 128), 654, 32, 32 };
		barrier[i] = new Barrier(barrierPos[i], spritesheet);
	}
	for (uint8_t x = 0; x < 4; x++)
	{
		barrierPos[x + 4] = { 96 + (x * 128), 654, 32, 32 };
		barrier[x + 4] = new Barrier(barrierPos[x+4], spritesheet);
	}
}

///	Sets all the pointers to NULL.
BarrierManager::~BarrierManager() {
	delete barrier[8];
	barrier[8] = NULL;
	spritesheet = NULL;
}

///	Calls all barriers to draw to the screen.
void BarrierManager::draw() {
	for (uint8_t i = 0; i < 8; i++)
	{
		if (barrier[i] != NULL) {
			barrier[i]->draw();
		}
	}
}

void BarrierManager::deleteBarrier(int x, int y) {
	delete barrier[x];
	barrier[x] = NULL;
	delete barrier[y];
	barrier[y] = NULL;
}

///	@warning This was used for debugging. UP ARROW damages all barriers.
void BarrierManager::damage(uint8_t _state, uint8_t _damageAmount) {

	switch (_state)
	{
	case 0:
		barrier[0]->loseHealth(5);
		barrier[4]->loseHealth(5);
		break;
	case 1:
		barrier[1]->loseHealth(5);
		barrier[5]->loseHealth(5);
		break;
	case 2:
		barrier[2]->loseHealth(5);
		barrier[6]->loseHealth(5);
		break;
	case 3:
		barrier[3]->loseHealth(5);
		barrier[7]->loseHealth(5);
		break;
		
	default:
		cout << "Default barrier damage switch hit" << std::endl;
		break;
	}
}