#include "PlayerEntityBrain.h"
#include "GameEntityBrain.h"
#include "Input.h"
#include "GameEntityState.h"
#include "CollideObj.h"
#include "MoveCObj.h"

PlayerEntityBrain::PlayerEntityBrain(GameEntityCamera *camera, MoveAndFloorCObjMgr *mgr, Input *input) : GameEntityBrain(camera, mgr){
	this->input = input;
}

PlayerEntityBrain::~PlayerEntityBrain(){
}

void PlayerEntityBrain::updateEntity(double *leftX, double *topY, double *width, double *height, GameEntityState *state, CollideObj *collisionObj, CollideObj *moveObj, unsigned int *liveFrame, unsigned int *stateFrame, bool *activeFlag){
}

void PlayerEntityBrain::initEntity(double *leftX, double *topY, double *width, double *height, GameEntityState *state, CollideObj **collisionObj, CollideObj **moveObj, unsigned int *liveFrame, unsigned int *stateFrame, bool *activeFlag){

}
