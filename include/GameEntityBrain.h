#ifndef GAME_ENTITY_BRAIN_H
#define GAME_ENTITY_BRAIN_H

#include "GameEntityState.h"

class GameEntityBrain{
	public:
		virtual ~GameEntityBrain(){}
		void updateEntity(double *, double *, GameEntityState *, CollideObj *, CollideObj *, unsigned int *, unsigned int *, bool *) = 0;
};

#endif
