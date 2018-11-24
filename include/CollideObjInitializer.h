#ifndef COLLIDE_OBJ_INITIALIZER_H
#define COLLIDE_OBJ_INITIALIZER_H

class CollideObj;

class CollideObjInitializer{
	public:
		virtual ~CollideObjInitializer(){}
		virtual void initObjs(CollideObj *, int) = 0;
};

#endif
