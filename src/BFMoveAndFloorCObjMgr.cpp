#include "BFMoveAndFloorCObjMgr.h"
#include "MoveCObj.h"
#include "FloorCObj.h"
#include "CollideObjInitializer.h"

BFMoveAndFloorCObjMgr::BFMoveAndFloorCObjMgr(){
	this->moveCObjLength = 5;
	this->floorCObjLength = 25;
	this->moveCObjs = new MoveCObj[this->moveCObjLength];
	this->floorCObjs = new FloorCObj[this->floorCObjLength];
}

BFMoveAndFloorCObjMgr::~BFMoveAndFloorCObjMgr(){
	delete[] this->moveCObjs;
	delete[] this->floorCObjs;
}

MoveCObj *BFMoveAndFloorCObjMgr::getFreeMoveCObj(){
	for(int i = 0; i < this->moveCObjLength; i++){
		if(!this->moveCObjs[i].isActive()){
			return (moveCObjs + i);
		}
	}
	return nullptr;
}

FloorCObj *BFMoveAndFloorCObjMgr::getFreeFloorCObj(){
	for(int i = 0; i < this->floorCObjLength; i++){
		if(!this->floorCObjs[i].isActive()){
			return (floorCObjs + i);
		}
	}
	return nullptr;
}

void BFMoveAndFloorCObjMgr::initFloors(CollideObjInitializer *initializer){
	initializer->initObjs(this->floorCObjs, this->floorCObjLength);
}

void BFMoveAndFloorCObjMgr::collisionCalc(){
	for(int i = 0; i < this->moveCObjLength; i++){
		for(int j = 0; j < this->floorCObjLength; j++){
			this->moveCObjs[i].interact(this->floorCObjs + j);
		}
	}
}

void BFMoveAndFloorCObjMgr::resetObjs(){
	for(int i = 0; i < this->moveCObjLength; i++){
		this->moveCObjs[i].setInactive();
	}
	for(int i = 0; i < this->floorCObjLength; i++){
		this->floorCObjs[i].setInactive();
	}
}
