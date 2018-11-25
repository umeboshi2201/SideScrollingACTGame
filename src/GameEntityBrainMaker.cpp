#include "GameEntityBrainMaker.h"

class GameEntityCamera;
class ImageMaker;

GameEntityBrainMaker::GameEntityBrainMaker(GameEntityCamera *camera, ImageMaker *imageMaker){
	this->camera = camera;
	this->imageMaker = imageMaker;
}
