#include <typeinfo>
#include "MoveCObj.h"
#include "FloorCObj.h"

#include "DxLib.h"

MoveCObj::MoveCObj(){
	this->leftX = 0;
	this->rightX = 0;
	this->topY = 0;
	this->bottomY = 0;
	this->preLeftX = 0;
  this->preTopY = 0;
	this->onFloorFlag = false;
	this->onWallWithRightCollisionFlag = false;
	this->onWallWithLeftCollisionFlag = false;
	this->onCeilingFlag = false;
	this->active = false;
}

MoveCObj::~MoveCObj(){

}

void MoveCObj::moveToXY(double leftX, double topY){
	const double width = this->rightX - this->leftX;
	const double height = this->bottomY - this->topY;
	this->leftX = leftX;
	this->topY = topY;
	this->rightX = this->leftX + width;
	this->bottomY = this->topY + height;
}

void MoveCObj::setFloorSurface(FloorCObj *fObj){
	// ヌルポインタなら何もしない
	if(fObj == nullptr){
		return;
	}

	const double height = this->bottomY - this->topY;
	const double moveObjCenterX = this->leftX + (this->rightX - this->leftX) / 2;
	// 床の最初の点と移動体の中心との差
	const double deltaX = moveObjCenterX - fObj->getStartX();
	// y軸の着地点
	const double destinationY = deltaX * fObj->getTangent() + fObj->getStartY();

	this->moveToXY(this->leftX, destinationY - height);

	return;
}

void MoveCObj::setWallWithRightCollisionSurface(FloorCObj *fObj){
	// ヌルポインタなら何もしない
	if(fObj == nullptr){
		return;
	}

	const double destinationX = fObj->getStartX();
	
	this->moveToXY(destinationX, this->topY);

	return;
}

void MoveCObj::setWallWithLeftCollisionSurface(FloorCObj *fObj){
	// ヌルポインタなら何もしない
	if(fObj == nullptr){
		return;
	}

	const double width = this->rightX - this->leftX;
	const double destinationX = fObj->getStartX();

	this->moveToXY(destinationX - width, this->topY);

	return;
}

bool MoveCObj::isUpperSideOfFloor(double leftX, double topY, FloorCObj *fObj){
	if(fObj == nullptr){
		return false;
	}

	const double moveObjCenterX = leftX + (this->rightX - this->leftX) / 2;
	const double height = this->bottomY - this->topY;
	// 床の最初の点と移動体の中心との差
	const double deltaX = moveObjCenterX - fObj->getStartX();
	// 移動体の中心点に対応する床の座標
	const double floorLandingPointY = deltaX * fObj->getTangent() + fObj->getStartY();

	if(topY + height <= floorLandingPointY){
		return true;
	}
	return false;
}

void MoveCObj::setLeftTopXY(double leftX, double topY){
	this->preLeftX = this->leftX;
	this->preTopY = this->topY;
	const double deltaX = leftX - this->leftX;
	const double deltaY = topY - this->topY; 
	this->leftX = leftX;
	this->topY = topY;
	this->rightX = this->rightX + deltaX;
	this->bottomY = this->bottomY + deltaY;
	this->onFloorFlag = false;
	this->onWallWithRightCollisionFlag = false;
	this->onWallWithLeftCollisionFlag = false;
	this->onCeilingFlag = false;
}

bool MoveCObj::isOnFloor(){
	return this->onFloorFlag;
}

bool MoveCObj::isOnWallWithRightCollision(){
	return this->onWallWithRightCollisionFlag;
}

bool MoveCObj::isOnWallWithLeftCollision(){
	return this->onWallWithLeftCollisionFlag;
}

bool MoveCObj::isOnCeiling(){
	return this->onCeilingFlag;
}


double MoveCObj::getLeftX(){
	return this->leftX;
}

double MoveCObj::getTopY(){
	return this->topY;
}

double MoveCObj::getRightX(){
	return this->rightX;
}

double MoveCObj::getBottomY(){
	return this->bottomY;
}

void MoveCObj::activate(double leftX, double topY, double width, double height){
	this->leftX = leftX;
	this->rightX = leftX + width;
	this->topY = topY;
	this->bottomY = topY + height;
	this->preLeftX = this->leftX;
  this->preTopY = this->topY;
	this->onFloorFlag = false;
	this->onWallWithRightCollisionFlag = false;
	this->onWallWithLeftCollisionFlag = false;
	this->onCeilingFlag = false;
	this->active = true;
}

void MoveCObj::setInactive(){
	this->leftX = 0;
	this->rightX = 0;
	this->topY = 0;
	this->bottomY = 0;
	this->preLeftX = 0;
  this->preTopY = 0;
	this->onFloorFlag = false;
	this->onWallWithRightCollisionFlag = false;
	this->onWallWithLeftCollisionFlag = false;
	this->onCeilingFlag = false;
	this->active = false;
}

void MoveCObj::interact(CollideObj *obj){
	// アクティブでなかったら
	if(!this->active){
		return;
	}

	// 床判定用のオブジェクトが渡されてなかったら
	if(typeid(*obj) != typeid(FloorCObj)){
		return;
	}

	const double targetLeftX = obj->getLeftX();
	const double targetTopY = obj->getTopY();
	const double targetRightX = obj->getRightX();
	const double targetBottomY = obj->getBottomY();

	//const bool judge1 = targetLeftX < this->rightX;
	//const bool judge2 = this->leftX < targetRightX;
	//const bool judge3 = targetTopY < this->bottomY;
	//const bool judge4 = this->topY < targetBottomY;
	// 計算回数減らすためAND演算子を使う
	// ぶつかる可能性の方が低いから、ぶつかってないときは全部の論理演算をしないで途中で抜けてほしい
	// 本来は!(judge1 && judge2 && judge3 && judge4)の論理演算をするつもりだった
	// コンパイラが上手いことやってくれそうな気もするが
	
	// 矩形範囲内でぶつかってなかったら
	if(!(targetLeftX < this->rightX) || !(this->leftX < targetRightX) || !(targetTopY < this->bottomY) || !(this->topY < targetBottomY)){
		// 何もしない
		return;
	}

	// ダウンキャスト
	FloorCObj *fObj = (FloorCObj*)obj;

	// 床判定なら
	if(fObj->isFloor()){
		const double moveObjCenterX = this->leftX + (this->rightX - this->leftX) / 2;

		// 中心点が床の幅の中にあったら
		if((fObj->getEndX() <= moveObjCenterX) && (moveObjCenterX <= fObj->getStartX())){

			// 更新前の移動体が床の上にあったなら
			if(isUpperSideOfFloor(this->preLeftX, this->preTopY, fObj)){

				// 更新後の移動体が床の下にあったなら
				if(!isUpperSideOfFloor(this->leftX, this->topY, fObj)){
					// 着地させる
					this->setFloorSurface(fObj);
					this->onFloorFlag = true;
				}

				// 更新後の移動体が床の下に無いのならこの床とは何もしない

			}

			// 更新前の移動体が床の上に無いならこの床とは何もしない

		}

		// 中心点が床の幅の中に無く、左側にはみ出ている状態なら
		else if((fObj->getEndX() <= this->rightX) && (this->rightX <= fObj->getStartX())){

			FloorCObj* tmpNext = fObj->getNextFloor();

			if(tmpNext == nullptr){

				// 更新前の移動体が床の上にあったなら
				if(isUpperSideOfFloor(this->preLeftX, this->preTopY, fObj)){

					// 更新後の移動体が床の下にあったなら
					if(!isUpperSideOfFloor(this->leftX, this->topY, fObj)){
						// 着地させる
						this->setFloorSurface(fObj);
						this->onFloorFlag = true;
					}

					// 更新後の移動体が床の下に無いのならこの床とは何もしない

				}

			}

			else{

				// 更新前の移動体が床の上にあったなら
				//if(isUpperSideOfFloor(this->preLeftX, this->preTopY, tmpNext)){

					// 更新後の移動体が床の下にあったなら
					if(!isUpperSideOfFloor(this->leftX, this->topY, tmpNext)){
						// 着地させる
						this->setFloorSurface(tmpNext);
						this->onFloorFlag = true;
					}

					// 更新後の移動体が床の下に無いのならこの床とは何もしない

				//}

			}

		}
		
		// 中心点が床の幅の中に無く、右側にはみ出ている状態なら
		else if((fObj->getEndX() <= this->leftX) && (this->leftX <= fObj->getStartX())){

			FloorCObj* tmpPre = fObj->getPreFloor();

			if(tmpPre == nullptr){

				// 更新前の移動体が床の上にあったなら
				if(isUpperSideOfFloor(this->preLeftX, this->preTopY, fObj)){

					// 更新後の移動体が床の下にあったなら
					if(!isUpperSideOfFloor(this->leftX, this->topY, fObj)){
						// 着地させる
						this->setFloorSurface(fObj);
						this->onFloorFlag = true;
					}

					// 更新後の移動体が床の下に無いのならこの床とは何もしない

				}

			}

			else{

				// 更新前の移動体が床の上にあったなら
				//if(isUpperSideOfFloor(this->preLeftX, this->preTopY, tmpPre)){

					// 更新後の移動体が床の下にあったなら
					if(!isUpperSideOfFloor(this->leftX, this->topY, tmpPre)){
						// 着地させる
						this->setFloorSurface(tmpPre);
						this->onFloorFlag = true;
					}

					// 更新後の移動体が床の下に無いのならこの床とは何もしない

				//}

			}
		}


	}
	// 右側に判定のある壁なら
	else if(fObj->isWallWithRightCollision()){
		
	}
	// 左側に判定のある壁なら
	else if(fObj->isWallWithLeftCollision()){
		
	}
	// 天井判定なら
	else if(fObj->isCeiling()){

	}

	return;
}

