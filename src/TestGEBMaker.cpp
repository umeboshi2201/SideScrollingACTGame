#include "TestGEBMaker.h"
#include "GameEntityBrain.h"

class GameEntityCamera;

TestGEBMaker::TestGEBMaker(GameEntityCamera *camera, ImageMaker *imageMaker) : GameEntityBrainMaker(camera, imageMaker){
	this->brainLength = 2;
	this->brains = new GameEntityBrain*[brainLength];
}

TestGEBMaker::~TestGEBMaker(){
	delete[] brains;
}

GameEntityBrain **TestGEBMaker::getBrains(int *length){
	*length = this->brainLength;
	return this->brains;
}
