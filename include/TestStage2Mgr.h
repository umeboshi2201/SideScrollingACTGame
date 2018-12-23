#ifndef TEST_STAGE2_MGR_H
#define TEST_STAGE2_MGR_H

#include "StageMgr.h"
#include "CollideObjInitializer.h"

class GameCamera;
class GameEntityBrainMaker;
class ImageMaker;
class GameEntity;

class TestStage2Mgr : public StageMgr{
	private:

		class TestStage2MgrInitializer : public CollideObjInitializer{
			public:
				TestStage2MgrInitializer();
				virtual ~TestStage2MgrInitializer();
				virtual void initObjs(CollideObj *, int);
		};

		TestStage2MgrInitializer *initializer;

	public:
		TestStage2Mgr(GameCamera *, GameEntityBrainMaker *, ImageMaker *);
		virtual ~TestStage2Mgr();
		virtual CollideObjInitializer *getFloorCObjInitializer();
		virtual void drawFloor();
		virtual void gameEntInit(GameEntity *, int);
};

#endif
