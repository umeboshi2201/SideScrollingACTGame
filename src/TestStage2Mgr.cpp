#include <typeinfo>
#include "StageMgr.h"
#include "TestStage2Mgr.h"
#include "CollideObj.h"
#include "FloorCObj.h"
#include "GameCamera.h"
#include "ImageMaker.h"
#include "GameEntityBrainMaker.h"
#include "GameEntity.h"

TestStage2Mgr::TestStage2Mgr(GameCamera *camera, GameEntityBrainMaker *brainMaker, ImageMaker *imageMaker) : StageMgr(camera, brainMaker, imageMaker){
	this->initializer = new TestStage2Mgr::TestStage2MgrInitializer();
	this->stageWidth = 4000;
	this->stageHeight = 1200;
}

TestStage2Mgr::~TestStage2Mgr(){
	delete this->initializer;
}

CollideObjInitializer *TestStage2Mgr::getFloorCObjInitializer(){
	return this->initializer;
}

// フラット
//this->imgs[1] = new DxlibTestBoxAndLineImage(100, 0, true);
// 右上に上がる
//this->imgs[2] = new DxlibTestBoxAndLineImage(100, -100, true);
// 右下に下がる
//this->imgs[3] = new DxlibTestBoxAndLineImage(100, 100, true);
void TestStage2Mgr::drawFloor(){
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

	int widthCount = stageWidth / 100;
	int heightCount = stageHeight / 100;
	for(int i = 0; i < widthCount; i++){
		camera->setImage(100 * i, -400, imgs[1], 1);
		camera->setImage(100 * i, 800, imgs[1], 1);
	}
	for(int i = 0; i < heightCount; i++){
		camera->setImage(0, 100 * i - 400, imgs[4], 1);
		camera->setImage(4000, 100 * i - 400, imgs[4], 1);
	}
	for(int i = 0; i < 4; i++){
		camera->setImage(1000, 400 + 100 * i, imgs[4], 1);
	}
	camera->setImage(1800, 800, imgs[2], 1);
	camera->setImage(1900, 700, imgs[1], 1);
	camera->setImage(600, 1700, imgs[4], 1);
	camera->setImage(500, 1600, imgs[3], 1);
	camera->setImage(500, 1600, imgs[3], 1);
}

void TestStage2Mgr::gameEntInit(GameEntity *ents, int entLength){
	const int STAGE_ENTITY_LENGTH = 2;

	if(entLength <= STAGE_ENTITY_LENGTH){
		return;
	}

	int brainLength;
	GameEntityBrain **brains = brainMaker->getBrains(&brainLength);
	
	ents[0].activate(10, 100, brains[0]);
}


TestStage2Mgr::TestStage2MgrInitializer::TestStage2MgrInitializer(){
}

TestStage2Mgr::TestStage2MgrInitializer::~TestStage2MgrInitializer(){
}

// ステージの床を生成
void TestStage2Mgr::TestStage2MgrInitializer::initObjs(CollideObj *objs, int length){

	const int STAGE_FLOOR_LENGTH = 11;

	// 長さが足りなかったら何もしない
	if(length < STAGE_FLOOR_LENGTH){
		return;
	}

	// 渡されたのがFloorCObjじゃなかったら何もしない
	if(typeid(*objs) != typeid(FloorCObj)){
		return;
	}

	// ダウンキャスト
	FloorCObj *floors = (FloorCObj *)objs;

	// endX < startX のとき床
	floors[0].activate(2000, 400, 1000, 400);
	floors[1].activate(1000, 400, 900, 400);
	floors[2].activate(900, 400, 800, 300);
	floors[3].activate(800, 300, 700, 400);
	floors[4].activate(700, 400, 600, 300);
	floors[5].activate(600, 300, 500, 400);
	floors[6].activate(500, 400, 400, 400);
	floors[7].activate(400, 400, 300, 300);
	floors[8].activate(300, 300, 200, 300);
	floors[9].activate(200, 300, 100, 400);
	floors[10].activate(100, 400, 0, 400);

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
