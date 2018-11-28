#ifndef TEST_STAGE_MGR_H
#define TEST_STAGE_MGR_H

#include "StageMgr.h"
#include "CollideObjInitializer.h"

class GameCamera;
class GameEntityBrainMaker;
class ImageMaker;
class GameEntity;

class TestStageMgr : public StageMgr{
	private:

		class TestStageMgrInitializer : public CollideObjInitializer{
			public:
				TestStageMgrInitializer();
				virtual ~TestStageMgrInitializer();
				virtual void initObjs(CollideObj *, int);
		};

		TestStageMgrInitializer *initializer;

	public:
		TestStageMgr(GameCamera *, GameEntityBrainMaker *, ImageMaker *);
		virtual ~TestStageMgr();
		virtual CollideObjInitializer *getFloorCObjInitializer();
		virtual void drawFloor();
		virtual void gameEntInit(GameEntity *, int);
};

#endif
