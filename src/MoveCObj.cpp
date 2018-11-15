#include "MoveCObj.h"

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

void MoveCObj::setLeftX(int, bool){
}

void MoveCObj::setTopY(int, bool){

}

int MoveCObj::getLeftX(){
	return this->leftX;
}

int MoveCObj::getTopY(){
	return this->topY;
}

int MoveCObj::getRightX(){
	return this->rightX;
}

int MoveCObj::getBottomY(){
	return this->bottomY;
}

void MoveCObj::activate(int leftX, int topY, int width, int height){
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

void MoveCObj::interact(CollideObj &){
}

