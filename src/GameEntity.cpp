#include "GameEntity.h"
#include "GameEntityState.h"
#include "GameEntityBrain.h"

GameEntity::GameEntity(){
	this->leftX = 0;
	this->topY = 0;
	this->width = 0;
	this->height = 0;
	this->state = GameEntityState::STAND_BY;
	this->collideObj1 = nullptr;
	this->collideObj2 = nullptr;
	this->entAI = nullptr;
	this->liveFrame = 0;
	this->stateFrame = 0;
	this->activeFlag = false;
}

GameEntity::~GameEntity(){
}

double GameEntity::getLeftX(){
	return this->leftX;
}

double GameEntity::getTopY(){
	return this->topY;
}

double GameEntity::getRightX(){
	return this->leftX + this->width;
}

double GameEntity::getBottomY(){
	return this->topY + this->height;
}

bool GameEntity::getActive(){
	return this->activeFlag;
}

void GameEntity::activate(double leftX, double topY, GameEntityBrain *brain){
	this->leftX = leftX;
	this->topY = topY;
	this->entAI = brain;
	this->entAI->initEntity(&this->leftX, &this->topY, &this->width, &this->height, &this->state, &this->collideObj1, &this->collideObj2, &this->liveFrame, &this->stateFrame, &this->activeFlag);
}

void GameEntity::setInactive(){
	this->leftX = 0;
	this->topY = 0;
	this->width = 0;
	this->height = 0;
	this->state = GameEntityState::STAND_BY;
	this->collideObj1 = nullptr;
	this->collideObj2 = nullptr;
	this->entAI = nullptr;
	this->liveFrame = 0;
	this->stateFrame = 0;
	this->activeFlag = false;
}

void GameEntity::update(){
	this->entAI->updateEntity(&leftX, &topY, &width, &height, &state, collideObj1, collideObj2, &liveFrame, &stateFrame, &activeFlag);
}
