#ifndef PLAYER_ENTITY_BRAIN_H
#define PLAYER_ENTITY_BRAIN_H

#include "GameEntityBrain.h"

class GameEntityBrain;
class GameCamera;
class Input;
class Image;

class PlayerEntityBrain : public GameEntityBrain{
	private:
		Input *input;
		Image *image;
	public:
		PlayerEntityBrain(GameCamera *, MoveAndFloorCObjMgr *, Input *, Image *);
		virtual ~PlayerEntityBrain();
		virtual void updateEntity(double *, double *, double *, double *, GameEntityState *, CollideObj *, CollideObj *, unsigned int *, unsigned int *, bool *);
		virtual void initEntity(double *, double *, double *, double *, GameEntityState *, CollideObj **, CollideObj **, unsigned int *, unsigned int *, bool *);

};

#endif
