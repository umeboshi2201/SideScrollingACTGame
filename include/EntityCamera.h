#ifndef ENTITY_CAMERA_H
#define ENTITY_CAMERA_H

#include "Image.h"

class EntityCamera{
	public:
		virtual double getLeftX() = 0;
		virtual double getTopY() = 0;
		virtual void setLeftX(double) = 0;
		virtual void setTopY(double) = 0;
		virtual void setImage(double, double, Image, int) = 0;
		virtual void draw() = 0;
};

#endif
