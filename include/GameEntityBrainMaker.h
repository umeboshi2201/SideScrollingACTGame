#ifndef GAME_ENTITY_BRAIN_MAKER_H
#define GAME_ENTITY_BRAIN_MAKER_H

class GameEntityBrain;

class GameEntityBrainMaker{
	public:
		virtual ~GameEntityBrainMaker(){}
		virtual GameEntityBrain *getBrains(int *length) = 0;
};

#endif
