#ifndef MOVE_C_OBJ_H
#define MOVE_C_OBJ_H

#include "CollideObj.h"

class MoveCObj : public CollideObj{
	protected:
		double leftX;
		double rightX;
		double topY;
		double bottomY;
		double preLeftX;
		double preTopY;

	public:
		MoveCObj();
		~MoveCObj();
		void setLeftX(double);
		void setTopY(double);

		virtual double getLeftX();
		virtual double getTopY();
		virtual double getRightX();
		virtual double getBottomY();
		virtual void activate(double, double, double, double);
		virtual void setInactive();
		virtual void interact(CollideObj *);
};

#endif
