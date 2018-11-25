#ifndef GAME_ENTITY_BRAIN_MAKER_H
#define GAME_ENTITY_BRAIN_MAKER_H

class GameEntityBrain;
class GameEntityCamera;
class ImageMaker;

class GameEntityBrainMaker{
	protected:
		GameEntityCamera *camera;
		ImageMaker *imageMaker;
	public:
		GameEntityBrainMaker(GameEntityCamera *, ImageMaker *);
		virtual ~GameEntityBrainMaker(){}
		virtual GameEntityBrain **getBrains(int *length) = 0;
};

#endif
