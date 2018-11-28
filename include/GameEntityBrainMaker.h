#ifndef GAME_ENTITY_BRAIN_MAKER_H
#define GAME_ENTITY_BRAIN_MAKER_H

class GameEntityBrain;
class GameCamera;
class ImageMaker;
class MoveAndFloorCObjMgr;
class Input;

class GameEntityBrainMaker{
	protected:
		GameCamera *camera;
		ImageMaker *imageMaker;
		MoveAndFloorCObjMgr *mAFCObjMgr;
		Input *input;
	public:
		GameEntityBrainMaker(GameCamera *, ImageMaker *, MoveAndFloorCObjMgr *, Input *);
		virtual ~GameEntityBrainMaker(){}
		virtual GameEntityBrain **getBrains(int *length) = 0;
};

#endif
