#include "GameEntityBrain.h"

class GameEntityCamera;

GameEntityBrain::GameEntityBrain(GameEntityCamera *camera){
	this->camera = camera;
}
