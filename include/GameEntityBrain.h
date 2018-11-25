#ifndef GAME_ENTITY_BRAIN_H
#define GAME_ENTITY_BRAIN_H

#include "GameEntityState.h"

class GameEntityCamera;
class MoveAndFloorCObjMgr;
class CollideObj;

class GameEntityBrain{
	protected:
		GameEntityCamera *camera;
		MoveAndFloorCObjMgr *mAFCObjMgr;
	public:
		GameEntityBrain(GameEntityCamera *, MoveAndFloorCObjMgr *mAFCObjMgr);
		virtual ~GameEntityBrain(){}
		virtual void updateEntity(double *, double *, double *, double *, GameEntityState *, CollideObj *, CollideObj *, unsigned int *, unsigned int *, bool *) = 0;
		virtual void initEntity(double *, double *, double *, double *, GameEntityState *, CollideObj **, CollideObj **, unsigned int *, unsigned int *, bool *) = 0;
};

#endif
