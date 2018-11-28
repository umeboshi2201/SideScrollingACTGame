#ifndef STAGE_MGR_H
#define STAGE_MGR_H

class CollideObjInitializer;
class GameCamera;
class GameEntityBrainMaker;
class ImageMaker;
class GameEntity;

class StageMgr{
	protected:
		GameCamera *camera;
		GameEntityBrainMaker *brainMaker;
		ImageMaker *imageMaker;
	public:
		StageMgr(GameCamera *, GameEntityBrainMaker *, ImageMaker *);
		virtual ~StageMgr(){}
		virtual CollideObjInitializer *getFloorCObjInitializer() = 0;
		virtual void drawFloor() = 0;
		virtual void gameEntInit(GameEntity *, int) = 0;
};

#endif
