#include "StageMgr.h"

StageMgr::StageMgr(GameCamera *camera, GameEntityBrainMaker *brainMaker, ImageMaker *imageMaker){
	this->camera = camera;
	this->brainMaker = brainMaker;
	this->imageMaker = imageMaker;
}
