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
	if(typeid(*pMoveObj) != typeid(MoveCObj)){
		return;
	}

	const double GRAVITY = 0.5; 
	const double JUMPV0 = 10;
	const double moveDeltaX = 4;

	double deltaX = 0;
	double deltaY = 0;

	// ダウンキャスト
	MoveCObj *bufMoveObj = (MoveCObj *)pMoveObj;

	// 衝突判定の変化分の補正をかける
	*leftX = deltaX = pMoveObj->getLeftX();
	*topY = deltaY = pMoveObj->getTopY();

	// STATE1 空中下降状態
	// STATE2 地上
	// STATE3 空中上昇状態
	switch(*state){

		case GameEntityState::STATE1:

			// 着地したら
			if(bufMoveObj->isOnFloor()){
				*state = GameEntityState::STATE2;
				*stateFrame = 0;
				bufMoveObj->setLeftTopXY(deltaX, deltaY);
				break;
			}

			break;

		case GameEntityState::STATE2:

			// 足場から離れてしまったら
			if(!bufMoveObj->isOnFloor()){
				*state = GameEntityState::STATE1;
				*stateFrame = 0;
			}

			// ジャンプボタンを押したら
			if(this->input->getJumpButtonState()){
				*state = GameEntityState::STATE3;
				*stateFrame = 0;
			}

			break;

		case GameEntityState::STATE3:

			// ジャンプボタンを離したら
			if(!this->input->getJumpButtonState()){
				*state = GameEntityState::STATE1;
				*stateFrame = 0;
			}

			// 上昇が終わったら
			if(- JUMPV0 + GRAVITY * (*stateFrame) > 0.0){
				*state = GameEntityState::STATE1;
				*stateFrame = 0;
			}

			break;

		default:

			break;

	}

	switch(*state){

		case GameEntityState::STATE1:

			deltaY = deltaY + GRAVITY * (*stateFrame + 1);

			if(this->input->getLeftButtonState()){
				deltaX -= moveDeltaX;
			}
			if(this->input->getRightButtonState()){
				deltaX += moveDeltaX;
			}

			bufMoveObj->setLeftTopXY(deltaX, deltaY);

			*stateFrame = *stateFrame + 1;

			break;

		case GameEntityState::STATE2:

			deltaY = deltaY + 2 * moveDeltaX;

			if(this->input->getLeftButtonState()){
				deltaX -= moveDeltaX;
			}
			if(this->input->getRightButtonState()){
				deltaX += moveDeltaX;
			}
			
			bufMoveObj->setLeftTopXY(deltaX, deltaY);

			*stateFrame = *stateFrame + 1;

			break;

		case GameEntityState::STATE3:

			deltaY = (deltaY) - JUMPV0 + GRAVITY * (*stateFrame);
			
			if(this->input->getLeftButtonState()){
				deltaX -= moveDeltaX;
			}
			if(this->input->getRightButtonState()){
				deltaX += moveDeltaX;
			}

			bufMoveObj->setLeftTopXY(deltaX, deltaY);

			*stateFrame = *stateFrame + 1;

			break;

		default:

			break;

	}

	this->camera->setImage(*leftX, *topY, this->image, 1);

	return;
}

void PlayerEntityBrain::initEntity(double *leftX, double *topY, double *width, double *height, GameEntityState *state, CollideObj **ppCollisionObj, CollideObj **ppMoveObj, unsigned int *liveFrame, unsigned int *stateFrame, bool *activeFlag){
	*width = 20;
	*height = 50;
	*state = GameEntityState::STATE1;
	*ppCollisionObj = nullptr;
	*ppMoveObj = this->mAFCObjMgr->getFreeMoveCObj();
	(*ppMoveObj)->activate(*leftX, *topY, *width, *height);
	*liveFrame = 0;
	*stateFrame = 0;
	*activeFlag = true;
}
