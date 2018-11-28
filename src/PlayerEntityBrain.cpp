#include <typeinfo>
#include "PlayerEntityBrain.h"
#include "GameEntityBrain.h"
#include "Input.h"
#include "GameEntityState.h"
#include "CollideObj.h"
#include "MoveCObj.h"
#include "MoveAndFloorCObjMgr.h"
#include "Image.h"
#include "GameCamera.h"

PlayerEntityBrain::PlayerEntityBrain(GameCamera *camera, MoveAndFloorCObjMgr *mgr, Input *input, Image *playerImage) : GameEntityBrain(camera, mgr){
	this->input = input;
	this->image = playerImage;
}

PlayerEntityBrain::~PlayerEntityBrain(){
}

void PlayerEntityBrain::updateEntity(double *leftX, double *topY, double *width, double *height, GameEntityState *state, CollideObj *collisionObj, CollideObj *pMoveObj, unsigned int *liveFrame, unsigned int *stateFrame, bool *activeFlag){
	// もし渡されたCollideObjがMoveCObjじゃなかったら何もしない
	if(typeid(pMoveObj) != typeid(MoveCObj *)){
		return;
	}

	const double GRAVITY = 1; 
	const double JUMPV0 = 10;
	const double moveDeltaX = 3;

	// ダウンキャスト
	MoveCObj *bufMoveObj = (MoveCObj *)pMoveObj;

	bool isOnFloor = bufMoveObj->isOnFloor();
	bool isOnWallWithRightCollision = bufMoveObj->isOnWallWithRightCollision();
	bool isOnWallWithLeftCollision = bufMoveObj->isOnWallWithLeftCollision();
	bool isOnCeiling = bufMoveObj->isOnCeiling();

	// STATE1 空中下降状態
	// STATE2 地上
	// STATE3 空中上昇状態
	switch(*state){

		case GameEntityState::STATE1:

			*topY = *topY + GRAVITY * (*stateFrame + 1);

			if(this->input->getLeftButtonState()){
				*leftX -= moveDeltaX;
			}
			if(this->input->getRightButtonState()){
				*leftX += moveDeltaX;
			}

			bufMoveObj->setLeftTopXY(*leftX, *topY);

			// 着地したら
			if(isOnFloor){
				*state = GameEntityState::STATE2;
				*stateFrame = 0;
			}

			break;

		case GameEntityState::STATE2:

			if(this->input->getLeftButtonState()){
				*leftX -= moveDeltaX;
			}
			if(this->input->getRightButtonState()){
				*leftX += moveDeltaX;
			}
			
			bufMoveObj->setLeftTopXY(*leftX, *topY);

			// ジャンプボタンを押したら
			if(this->input->getJumpButtonState()){
				*state = GameEntityState::STATE3;
				*stateFrame = 0;
			}

			break;

		case GameEntityState::STATE3:

			*topY = (*topY) - JUMPV0 + GRAVITY * (*stateFrame);
			
			if(this->input->getLeftButtonState()){
				*leftX -= moveDeltaX;
			}
			if(this->input->getRightButtonState()){
				*leftX += moveDeltaX;
			}

			bufMoveObj->setLeftTopXY(*leftX, *topY);

			// ジャンプボタンを離したら
			if(!this->input->getJumpButtonState()){
				*state = GameEntityState::STATE1;
				*stateFrame = 0;
			}

			break;

		default:
			break;

	}

	this->camera->setImage(*leftX, *topY, this->image, 0);

	return;
}

void PlayerEntityBrain::initEntity(double *leftX, double *topY, double *width, double *height, GameEntityState *state, CollideObj **ppCollisionObj, CollideObj **ppMoveObj, unsigned int *liveFrame, unsigned int *stateFrame, bool *activeFlag){
	*width = 20;
	*height = 50;
	*state = GameEntityState::STATE1;
	*ppCollisionObj = nullptr;
	*ppMoveObj = this->mAFCObjMgr->getFreeMoveCObj();
	(*ppMoveObj)->activate(*leftX, *height, *leftX + *width, *topY + *height);
	*liveFrame = 0;
	*stateFrame = 0;
	*activeFlag = true;
}
