#include <typeinfo>
#include "StageMgr.h"
#include "TestStage3Mgr.h"
#include "CollideObj.h"
#include "FloorCObj.h"
#include "GameCamera.h"
#include "ImageMaker.h"
#include "GameEntityBrainMaker.h"
#include "GameEntity.h"

TestStage3Mgr::TestStage3Mgr(GameCamera *camera, GameEntityBrainMaker *brainMaker, ImageMaker *imageMaker) : StageMgr(camera, brainMaker, imageMaker){
	this->initializer = new TestStage3Mgr::TestStage3MgrInitializer();
}

TestStage3Mgr::~TestStage3Mgr(){
	delete this->initializer;
}

CollideObjInitializer *TestStage3Mgr::getFloorCObjInitializer(){
	return this->initializer;
}

// フラット
//this->imgs[1] = new DxlibTestBoxAndLineImage(100, 0, true);
// 右上に上がる
//this->imgs[2] = new DxlibTestBoxAndLineImage(100, -100, true);
// 右下に下がる
//this->imgs[3] = new DxlibTestBoxAndLineImage(100, 100, true);
void TestStage3Mgr::drawFloor(){
	int imageLength;
	Image **imgs = imageMaker->getImages(&imageLength);

	camera->setImage(0, 400, imgs[1], 2);
	camera->setImage(100, 400, imgs[2], 2);
	camera->setImage(200, 300, imgs[1], 2);
	camera->setImage(300, 300, imgs[3], 2);
	camera->setImage(400, 400, imgs[1], 2);
	camera->setImage(500, 400, imgs[2], 2);
	camera->setImage(600, 300, imgs[3], 2);
	camera->setImage(700, 400, imgs[2], 2);
	camera->setImage(800, 300, imgs[3], 2);
	camera->setImage(900, 400, imgs[1], 2);
	camera->setImage(1000, 400, imgs[1], 2);
	camera->setImage(1100, 400, imgs[2], 2);
	camera->setImage(1200, 300, imgs[1], 2);
	camera->setImage(1000, 300, imgs[1], 2);
	camera->setImage(900, 200, imgs[3], 2);
	camera->setImage(800, 200, imgs[1], 2);
	camera->setImage(1000, 200, imgs[1], 2);
	camera->setImage(1100, 200, imgs[2], 2);
	camera->setImage(1200, 100, imgs[1], 2);
	camera->setImage(-400, 0, imgs[5], 1);
}

void TestStage3Mgr::gameEntInit(GameEntity *ents, int entLength){
	const int STAGE_ENTITY_LENGTH = 2;

	if(entLength <= STAGE_ENTITY_LENGTH){
		return;
	}

	int brainLength;
	GameEntityBrain **brains = brainMaker->getBrains(&brainLength);
	
	ents[0].activate(10, 100, brains[0]);
}


TestStage3Mgr::TestStage3MgrInitializer::TestStage3MgrInitializer(){
}

TestStage3Mgr::TestStage3MgrInitializer::~TestStage3MgrInitializer(){
}

// ステージの床を生成
void TestStage3Mgr::TestStage3MgrInitializer::initObjs(CollideObj *objs, int length){

	const int STAGE_FLOOR_LENGTH = 20;

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
	floors[0].activate(1100, 400, 1000, 400);
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

	floors[11].activate(1200, 300, 1100, 400);
	floors[12].activate(1300, 300, 1200, 300);
	floors[13].activate(1100, 300, 1000, 300);
	floors[14].activate(1000, 300, 900, 200);
	floors[15].activate(900, 200, 800, 200);
	floors[16].activate(1100, 200, 1000, 200);
	floors[17].activate(1200, 100, 1100, 200);
	floors[18].activate(1300, 100, 1200, 100);

	// startXYに接続しているのがpre
	// endXYに接続してるのがNext
	floors[0].setPreFloor(&floors[11]);
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
	floors[9].setNextFloor(&floors[10]);

	floors[10].setPreFloor(&floors[9]);
	floors[10].setNextFloor(nullptr);

	floors[11].setPreFloor(&floors[12]);
	floors[11].setNextFloor(&floors[0]);

	floors[12].setPreFloor(nullptr);
	floors[12].setNextFloor(&floors[11]);

	floors[13].setPreFloor(nullptr);
	floors[13].setNextFloor(&floors[14]);

	floors[14].setPreFloor(&floors[13]);
	floors[14].setNextFloor(&floors[15]);

	floors[15].setPreFloor(&floors[14]);
	floors[15].setNextFloor(nullptr);

	floors[16].setPreFloor(&floors[17]);
	floors[16].setNextFloor(nullptr);

	floors[17].setPreFloor(&floors[18]);
	floors[17].setNextFloor(&floors[16]);

	floors[18].setPreFloor(nullptr);
	floors[18].setNextFloor(&floors[17]);
	return;
}
