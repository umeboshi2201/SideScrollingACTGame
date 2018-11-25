#ifndef PLAYER_ENTITY_BRAIN_H
#define PLAYER_ENTITY_BRAIN_H

#include "GameEntityBrain.h"

class GameEntityBrain;
class GameEntityCamera;
class Input;

class PlayerEntityBrain : public GameEntityBrain{
	private:
		Input *input;
	public:
		PlayerEntityBrain(GameEntityCamera *, MoveAndFloorCObjMgr *, Input *);
		virtual ~PlayerEntityBrain();
		virtual void updateEntity(double *, double *, double *, double *, GameEntityState *, CollideObj *, CollideObj *, unsigned int *, unsigned int *, bool *);
		virtual void initEntity(double *, double *, double *, double *, GameEntityState *, CollideObj **, CollideObj **, unsigned int *, unsigned int *, bool *);

};

#endif
