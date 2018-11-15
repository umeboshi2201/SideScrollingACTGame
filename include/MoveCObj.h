#ifndef MOVE_C_OBJ_H
#define MOVE_C_OBJ_H

#include "CollideObj.h"

class MoveCObj : public CollideObj{
	protected:
		int leftX;
		int rightX;
		int topY;
		int bottomY;
		int preLeftX;
		int preTopY;

	public:
		MoveCObj();
		~MoveCObj();
		void setLeftX(int, bool);
		void setTopY(int, bool);

		virtual int getLeftX();
		virtual int getTopY();
		virtual int getRightX();
		virtual int getBottomY();
		virtual void activate(int, int, int, int);
		virtual void setInactive();
		virtual void interact(CollideObj &);
};

#endif
