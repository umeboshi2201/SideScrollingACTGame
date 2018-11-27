#include "GameEntityBrain.h"

class GameCamera;
class MoveAndFloorCObjMgr;

GameEntityBrain::GameEntityBrain(GameCamera *camera, MoveAndFloorCObjMgr *mgr){
	this->camera = camera;
	this->mAFCObjMgr = mgr;
}
