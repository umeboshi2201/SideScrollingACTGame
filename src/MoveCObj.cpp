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
	// �k���|�C���^�Ȃ牽�����Ȃ�
	if(fObj == nullptr){
		return;
	}

	const double height = this->bottomY - this->topY;
	const double moveObjCenterX = this->leftX + (this->rightX - this->leftX) / 2;
	// ���̍ŏ��̓_�ƈړ��̂̒��S�Ƃ̍�
	const double deltaX = moveObjCenterX - fObj->getStartX();
	// y���̒��n�_
	const double destinationY = deltaX * fObj->getTangent() + fObj->getStartY();

	this->moveToXY(this->leftX, destinationY - height);

	return;
}

void MoveCObj::setWallWithRightCollisionSurface(FloorCObj *fObj){
	// �k���|�C���^�Ȃ牽�����Ȃ�
	if(fObj == nullptr){
		return;
	}

	const double destinationX = fObj->getStartX();
	
	this->moveToXY(destinationX, this->topY);

	return;
}

void MoveCObj::setWallWithLeftCollisionSurface(FloorCObj *fObj){
	// �k���|�C���^�Ȃ牽�����Ȃ�
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
	// ���̍ŏ��̓_�ƈړ��̂̒��S�Ƃ̍�
	const double deltaX = moveObjCenterX - fObj->getStartX();
	// �ړ��̂̒��S�_�ɑΉ����鏰�̍��W
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
	// �A�N�e�B�u�łȂ�������
	if(!this->active){
		return;
	}

	// ������p�̃I�u�W�F�N�g���n����ĂȂ�������
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
	// �v�Z�񐔌��炷����AND���Z�q���g��
	// �Ԃ���\���̕����Ⴂ����A�Ԃ����ĂȂ��Ƃ��͑S���̘_�����Z�����Ȃ��œr���Ŕ����Ăق���
	// �{����!(judge1 && judge2 && judge3 && judge4)�̘_�����Z��������肾����
	// �R���p�C������肢���Ƃ���Ă��ꂻ���ȋC�����邪
	
	// ��`�͈͓��łԂ����ĂȂ�������
	if(!(targetLeftX < this->rightX) || !(this->leftX < targetRightX) || !(targetTopY < this->bottomY) || !(this->topY < targetBottomY)){
		// �������Ȃ�
		return;
	}

	// �_�E���L���X�g
	FloorCObj *fObj = (FloorCObj*)obj;

	// ������Ȃ�
	if(fObj->isFloor()){
		const double moveObjCenterX = this->leftX + (this->rightX - this->leftX) / 2;

		// ���S�_�����̕��̒��ɂ�������
		if((fObj->getEndX() <= moveObjCenterX) && (moveObjCenterX <= fObj->getStartX())){

			// �X�V�O�̈ړ��̂����̏�ɂ������Ȃ�
			if(isUpperSideOfFloor(this->preLeftX, this->preTopY, fObj)){

				// �X�V��̈ړ��̂����̉��ɂ������Ȃ�
				if(!isUpperSideOfFloor(this->leftX, this->topY, fObj)){
					// ���n������
					this->setFloorSurface(fObj);
					this->onFloorFlag = true;
				}

				// �X�V��̈ړ��̂����̉��ɖ����̂Ȃ炱�̏��Ƃ͉������Ȃ�

			}

			// �X�V�O�̈ړ��̂����̏�ɖ����Ȃ炱�̏��Ƃ͉������Ȃ�

		}

		// ���S�_�����̕��̒��ɖ����A�����ɂ͂ݏo�Ă����ԂȂ�
		else if((fObj->getEndX() <= this->rightX) && (this->rightX <= fObj->getStartX())){

			FloorCObj* tmpNext = fObj->getNextFloor();

			if(tmpNext == nullptr){

				// �X�V�O�̈ړ��̂����̏�ɂ������Ȃ�
				if(isUpperSideOfFloor(this->preLeftX, this->preTopY, fObj)){

					// �X�V��̈ړ��̂����̉��ɂ������Ȃ�
					if(!isUpperSideOfFloor(this->leftX, this->topY, fObj)){
						// ���n������
						this->setFloorSurface(fObj);
						this->onFloorFlag = true;
					}

					// �X�V��̈ړ��̂����̉��ɖ����̂Ȃ炱�̏��Ƃ͉������Ȃ�

				}

			}

			else{

				// �X�V�O�̈ړ��̂����̏�ɂ������Ȃ�
				//if(isUpperSideOfFloor(this->preLeftX, this->preTopY, tmpNext)){

					// �X�V��̈ړ��̂����̉��ɂ������Ȃ�
					if(!isUpperSideOfFloor(this->leftX, this->topY, tmpNext)){
						// ���n������
						this->setFloorSurface(tmpNext);
						this->onFloorFlag = true;
					}

					// �X�V��̈ړ��̂����̉��ɖ����̂Ȃ炱�̏��Ƃ͉������Ȃ�

				//}

			}

		}
		
		// ���S�_�����̕��̒��ɖ����A�E���ɂ͂ݏo�Ă����ԂȂ�
		else if((fObj->getEndX() <= this->leftX) && (this->leftX <= fObj->getStartX())){

			FloorCObj* tmpPre = fObj->getPreFloor();

			if(tmpPre == nullptr){

				// �X�V�O�̈ړ��̂����̏�ɂ������Ȃ�
				if(isUpperSideOfFloor(this->preLeftX, this->preTopY, fObj)){

					// �X�V��̈ړ��̂����̉��ɂ������Ȃ�
					if(!isUpperSideOfFloor(this->leftX, this->topY, fObj)){
						// ���n������
						this->setFloorSurface(fObj);
						this->onFloorFlag = true;
					}

					// �X�V��̈ړ��̂����̉��ɖ����̂Ȃ炱�̏��Ƃ͉������Ȃ�

				}

			}

			else{

				// �X�V�O�̈ړ��̂����̏�ɂ������Ȃ�
				//if(isUpperSideOfFloor(this->preLeftX, this->preTopY, tmpPre)){

					// �X�V��̈ړ��̂����̉��ɂ������Ȃ�
					if(!isUpperSideOfFloor(this->leftX, this->topY, tmpPre)){
						// ���n������
						this->setFloorSurface(tmpPre);
						this->onFloorFlag = true;
					}

					// �X�V��̈ړ��̂����̉��ɖ����̂Ȃ炱�̏��Ƃ͉������Ȃ�

				//}

			}
		}


	}
	// �E���ɔ���̂���ǂȂ�
	else if(fObj->isWallWithRightCollision()){
		
	}
	// �����ɔ���̂���ǂȂ�
	else if(fObj->isWallWithLeftCollision()){
		
	}
	// �V�䔻��Ȃ�
	else if(fObj->isCeiling()){

	}

	return;
}

