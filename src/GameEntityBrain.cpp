#include "GameEntityBrain.h"

class GameEntityCamera;
class MoveAndFloorCObjMgr;

GameEntityBrain::GameEntityBrain(GameEntityCamera *camera, MoveAndFloorCObjMgr *mgr){
	this->camera = camera;
	this->mAFCObjMgr = mgr;
}
