#ifndef TEST_G_E_B_MAKER_H
#define TEST_G_E_B_MAKER_H

#include "GameEntityBrainMaker.h"

class GameEntityBrain;
class GameCamera;
class ImageMaker;

class TestGEBMaker : public GameEntityBrainMaker{
	private:
		GameEntityBrain **brains;
		int brainLength;
	public:
		TestGEBMaker(GameCamera *, ImageMaker *, MoveAndFloorCObjMgr *, Input *);
		virtual ~TestGEBMaker();
		virtual GameEntityBrain **getBrains(int *length);
};

#endif
