#ifndef TEST_STAGE3_MGR_H
#define TEST_STAGE3_MGR_H

#include "StageMgr.h"
#include "CollideObjInitializer.h"

class GameCamera;
class GameEntityBrainMaker;
class ImageMaker;
class GameEntity;

class TestStage3Mgr : public StageMgr{
	private:

		class TestStage3MgrInitializer : public CollideObjInitializer{
			public:
				TestStage3MgrInitializer();
				virtual ~TestStage3MgrInitializer();
				virtual void initObjs(CollideObj *, int);
		};

		TestStage3MgrInitializer *initializer;

	public:
		TestStage3Mgr(GameCamera *, GameEntityBrainMaker *, ImageMaker *);
		virtual ~TestStage3Mgr();
		virtual CollideObjInitializer *getFloorCObjInitializer();
		virtual void drawFloor();
		virtual void gameEntInit(GameEntity *, int);
};

#endif
