#include <typeinfo>
#include "MoveCObj.h"
#include "FloorCObj.h"

MoveCObj::MoveCObj(){
	this->leftX = 0;
	this->rightX = 0;
	this->topY = 0;
	this->bottomY = 0;
	this->preLeftX = 0;
  this->preTopY = 0;
	this->active = false;
}

MoveCObj::~MoveCObj(){

}

void MoveCObj::setLeftTopXY(double leftX, double topY){
	const double deltaX = leftX - this->leftX;
	const double deltaY = topY - this->topY; 
	this->leftX = leftX;
	this->topY = topY;
	this->rightX = this->rightX + deltaX;
	this->bottomY = this->bottomY + deltaY;
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
	this->active = true;
}

void MoveCObj::setInactive(){
	this->leftX = 0;
	this->rightX = 0;
	this->topY = 0;
	this->bottomY = 0;
	this->preLeftX = 0;
  this->preTopY = 0;
	this->active = false;
}

void MoveCObj::interact(CollideObj *obj){
	// アクティブでなかったら
	if(!this->active){
		return;
	}

	// 床判定用のオブジェクトが渡されてなかったら
	if(typeid(obj) != typeid(FloorCObj*)){
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
		if((fObj->getEndX() < moveObjCenterX) && (moveObjCenterX < fObj->getStartX())){
			const double landingPointY = fObj->getStartY() + (moveObjCenterX - fObj->getStartX()) * fObj->getTangent();

			// 着地ポイントより下だったら
			if(landingPointY < this->bottomY){
				const double moveDeltaY = this->bottomY - landingPointY;
			}
		}
		else{
		}

	}
	// 右側に判定のある壁なら
	else if(fObj->isWallWithCollideRight()){
		
	}
	// 左側に判定のある壁なら
	else if(fObj->isWallWithCollideLeft()){
		
	}
	// 天井判定なら
	else if(fObj->isCeiling()){

	}

	return;
}

