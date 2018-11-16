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
	// �A�N�e�B�u�łȂ�������
	if(!this->active){
		return;
	}

	// ������p�̃I�u�W�F�N�g���n����ĂȂ�������
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
		if((fObj->getEndX() < moveObjCenterX) && (moveObjCenterX < fObj->getStartX())){
			const double landingPointY = fObj->getStartY() + (moveObjCenterX - fObj->getStartX()) * fObj->getTangent();

			// ���n�|�C���g��艺��������
			if(landingPointY < this->bottomY){
				const double moveDeltaY = this->bottomY - landingPointY;
			}
		}
		else{
		}

	}
	// �E���ɔ���̂���ǂȂ�
	else if(fObj->isWallWithCollideRight()){
		
	}
	// �����ɔ���̂���ǂȂ�
	else if(fObj->isWallWithCollideLeft()){
		
	}
	// �V�䔻��Ȃ�
	else if(fObj->isCeiling()){

	}

	return;
}

