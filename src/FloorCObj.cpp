#include "FloorCObj.h"

FloorCObj::FloorCObj(){
	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
	this->tangent = 0;
	this->active = false;
}

FloorCObj::~FloorCObj(){

}

bool FloorCObj::isFloor(){
	if(this->endX < this->startX){
		return true;
	}
	return false;
}

bool FloorCObj::isRightCollideWall(){
	if(this->startX == this->endX){
		if(this->startY < this->endY){
			return true;
		}
	}
	return false;
}

bool FloorCObj::isLeftCollideWall(){
	if(this->startX == this->endX){
		if(this->endY < this->startY){
			return true;
		}
	}
	return false;
}

bool FloorCObj::isCeiling(){
	if(this->startX < this->endX){
		return true;
	}
	return false;
}

double FloorCObj::getTangent(){
	return this->tangent;
}

int FloorCObj::getLeftX(){
	if(this->startX < this->endX){
		return this->startX;
	}
	return this->endX;
}

int FloorCObj::getTopY(){
	if(this->startY < this->endY){
		return this->startY;
	}
	return this->endY;
}

int FloorCObj::getRightX(){
	if(this->startX < this->endX){
		return this->endX;
	}
	return this->startX;
}

int FloorCObj::getBottomY(){
	if(this->startY < this->endY){
		return this->endY;
	}
	return this->startY;
}

void FloorCObj::activate(int startX, int endX, int startY, int endY){
	this->startX = startX;
	this->endX = endX;
	this->startY = startY;
	this->endY = endY;

	const double deltaX = endX - startX;
	const double deltaY = endY - startY;
	if(endX != startX){
		this->tangent = deltaY / deltaX;
	}
	this->tangent = 0;
}

void FloorCObj::setInactive(){
	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
	this->tangent = 0;
	this->active = false;
}

void FloorCObj::interact(CollideObj &){
}
