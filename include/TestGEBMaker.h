#ifndef TEST_G_E_B_MAKER_H
#define TEST_G_E_B_MAKER_H

#include "GameEntityBrainMaker.h"

class GameEntityBrain;
class GameEntityCamera;
class ImageMaker;

class TestGEBMaker : public GameEntityBrainMaker{
	private:
		GameEntityBrain **brains;
		int brainLength;
	public:
		TestGEBMaker(GameEntityCamera *, ImageMaker *);
		virtual ~TestGEBMaker();
		virtual GameEntityBrain **getBrains(int *length);
};

#endif
