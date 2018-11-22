#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "GameEntityState.h"

class CollideObj;
class GameEntityBrain;

class GameEntity{
	private:
		double leftX;
		double topY;
		GameEntityState state;
		CollideObj *collideObj1;
		CollideObj *collideObj2;
		GameEntityBrain *entAI;
		unsigned int liveFrame;
		unsigned int stateFrame;
		bool activeFlag;
	public:
		GameEntity();
		~GameEntity();
		bool getActive();
		void activate(double, double, GameEntityBrain *);
		void setInactive();
		void update();
};

#endif
