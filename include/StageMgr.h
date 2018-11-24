#ifndef STAGE_MGR_H
#define STAGE_MGR_H

class CollideObjInitializer;

class StageMgr{
	public:
		virtual ~StageMgr(){}
		virtual CollideObjInitializer *getFloorCObjInitializer() = 0;
		virtual void drawFloor() = 0;
		virtual void gameEntInit(GameEntity *, int) = 0;
};

#endif
