#include "TestGEBMaker.h"
#include "GameEntityBrain.h"
#include "GameCamera.h"
#include "PlayerEntityBrain.h"
#include "ImageMaker.h"

class MoveAndFloorCObjMgr;
class Input;

TestGEBMaker::TestGEBMaker(GameCamera *camera, ImageMaker *imageMaker, MoveAndFloorCObjMgr *mAFCObjMgr, Input *input) : GameEntityBrainMaker(camera, imageMaker, mAFCObjMgr, input){
	this->brainLength = 1;
	this->brains = new GameEntityBrain*[brainLength];


	int imgLength;
	Image **images = this->imageMaker->getImages(&imgLength);

	this->brains[0] = new PlayerEntityBrain(this->camera, this->mAFCObjMgr, this->input, images[0]);

}

TestGEBMaker::~TestGEBMaker(){
	for(int i = 0; i < this->brainLength; i++){
		delete brains[i];
	}
	delete[] brains;
}

GameEntityBrain **TestGEBMaker::getBrains(int *length){
	*length = this->brainLength;
	return this->brains;
}
