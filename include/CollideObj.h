#ifndef COLLIDE_OBJ_H
#define COLLIDE_OBJ_H

class CollideObj{
	protected:
		bool active;

	public:
		CollideObj();
		virtual ~CollideObj();
		virtual int getLeftX() = 0;
		virtual int getTopY() = 0;
		virtual int getRightX() = 0;
		virtual int getBottomY() = 0;
		virtual bool isActive();
		virtual void activate(int, int, int, int) = 0;
		virtual void setInactive() = 0;
		virtual void interact(CollideObj &) = 0;
};

#endif
