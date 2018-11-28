#include "GameEntityBrainMaker.h"

class GameCamera;
class ImageMaker;

GameEntityBrainMaker::GameEntityBrainMaker(GameCamera *camera, ImageMaker *imageMaker, MoveAndFloorCObjMgr *mAFCObjMgr, Input *input){
	this->camera = camera;
	this->imageMaker = imageMaker;
	this->mAFCObjMgr = mAFCObjMgr;
	this->input = input;
}
