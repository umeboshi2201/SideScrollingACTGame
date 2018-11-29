#include <typeinfo>
#include "StageMgr.h"
#include "TestStageMgr.h"
#include "CollideObj.h"
#include "FloorCObj.h"
#include "GameCamera.h"
#include "ImageMaker.h"
#include "GameEntityBrainMaker.h"
#include "GameEntity.h"

TestStageMgr::TestStageMgr(GameCamera *camera, GameEntityBrainMaker *brainMaker, ImageMaker *imageMaker) : StageMgr(camera, brainMaker, imageMaker){
	this->initializer = new TestStageMgr::TestStageMgrInitializer();
}

TestStageMgr::~TestStageMgr(){
	delete this->initializer;
}

CollideObjInitializer *TestStageMgr::getFloorCObjInitializer(){
	return this->initializer;
}

// フラット
//this->imgs[1] = new DxlibTestBoxAndLineImage(100, 0, true);
// 右上に上がる
//this->imgs[2] = new DxlibTestBoxAndLineImage(100, -100, true);
// 右下に下がる
//this->imgs[3] = new DxlibTestBoxAndLineImage(100, 100, true);
void TestStageMgr::drawFloor(){
	int imageLength;
	Image **imgs = imageMaker->getImages(&imageLength);

	camera->setImage(0, 400, imgs[1], 1);
	camera->setImage(100, 400, imgs[2], 1);
	camera->setImage(200, 300, imgs[1], 1);
	camera->setImage(300, 300, imgs[3], 1);
	camera->setImage(400, 400, imgs[1], 1);
	camera->setImage(500, 400, imgs[2], 1);
	camera->setImage(600, 300, imgs[3], 1);
	camera->setImage(700, 400, imgs[2], 1);
	camera->setImage(800, 300, imgs[3], 1);
	camera->setImage(900, 400, imgs[1], 1);
}

void TestStageMgr::gameEntInit(GameEntity *ents, int entLength){
	const int STAGE_ENTITY_LENGTH = 2;

	if(entLength <= STAGE_ENTITY_LENGTH){
		return;
	}

	int brainLength;
	GameEntityBrain **brains = brainMaker->getBrains(&brainLength);
	
	ents[0].activate(10, 100, brains[0]);
}


TestStageMgr::TestStageMgrInitializer::TestStageMgrInitializer(){
}

TestStageMgr::TestStageMgrInitializer::~TestStageMgrInitializer(){
}

// ステージの床を生成
void TestStageMgr::TestStageMgrInitializer::initObjs(CollideObj *objs, int length){

	const int STAGE_FLOOR_LENGTH = 10;

	// 長さが足りなかったら何もしない
	if(length < STAGE_FLOOR_LENGTH){
		return;
	}

	// 渡されたのがFloorCObjじゃなかったら何もしない
	if(typeid(objs) != typeid(FloorCObj *)){
		return;
	}

	// ダウンキャスト
	FloorCObj *floors = (FloorCObj *)objs;

	// endX < startX のとき床
	floors[0].activate(1000, 400, 900, 400);
	floors[1].activate(900, 400, 800, 300);
	floors[2].activate(800, 300, 700, 400);
	floors[3].activate(700, 400, 600, 300);
	floors[4].activate(600, 300, 500, 400);
	floors[5].activate(500, 400, 400, 400);
	floors[6].activate(400, 400, 300, 300);
	floors[7].activate(300, 300, 200, 300);
	floors[8].activate(200, 300, 100, 400);
	floors[9].activate(100, 400, 0, 400);

	// startXYに接続しているのがpre
	// endXYに接続してるのがNext
	floors[0].setPreFloor(nullptr);
	floors[0].setNextFloor(&floors[1]);

	floors[1].setPreFloor(&floors[0]);
	floors[1].setNextFloor(&floors[2]);

	floors[2].setPreFloor(&floors[1]);
	floors[2].setNextFloor(&floors[3]);

	floors[3].setPreFloor(&floors[2]);
	floors[3].setNextFloor(&floors[4]);

	floors[4].setPreFloor(&floors[3]);
	floors[4].setNextFloor(&floors[5]);

	floors[5].setPreFloor(&floors[4]);
	floors[5].setNextFloor(&floors[6]);

	floors[6].setPreFloor(&floors[5]);
	floors[6].setNextFloor(&floors[7]);

	floors[7].setPreFloor(&floors[6]);
	floors[7].setNextFloor(&floors[8]);

	floors[8].setPreFloor(&floors[7]);
	floors[8].setNextFloor(&floors[9]);

	floors[9].setPreFloor(&floors[8]);
	floors[9].setNextFloor(nullptr);

	return;
}
