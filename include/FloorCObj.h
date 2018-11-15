#ifndef FLOOR_C_OBJ_H
#define FLOOR_C_OBJ_H

#include "CollideObj.h"

class FloorCObj : public CollideObj{
	protected:
		int startX;
		int startY;
		int endX;
		int endY;
		// 左手座標系 時計回りの方向が正の角度
		double tangent;

	public:
		FloorCObj();
		~FloorCObj();
		bool isFloor();
		bool isRightCollideWall();
		bool isLeftCollideWall();
		bool isCeiling();
		double getTangent();

		virtual int getLeftX();
		virtual int getTopY();
		virtual int getRightX();
		virtual int getBottomY();
		virtual void activate(int, int, int, int);
		virtual void setInactive();
		virtual void interact(CollideObj &);
};

#endif
