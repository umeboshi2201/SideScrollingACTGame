#ifndef G_E_B_TEST_FLOOR_H
#define G_E_B_TEST_FLOOR_H

#include "GameEntityBrain.h"

class GameEntityCamera;

class GEBTestFloor : public GameEntityBrain{
	private:
		double startX;
		double startY;
		double endX;
		double endY;
	public:
		GEBTestFloor(double, double, double, double, GameEntityCamera *);
		virtual ~GEBTestFloor();
		virtual void updateEntity(double *, double *, double *, double *, GameEntityState *, CollideObj *, CollideObj *, unsigned int *, unsigned int *, bool *);
};

#endif
