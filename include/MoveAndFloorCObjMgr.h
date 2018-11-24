#ifndef MOVE_AND_FLOOR_C_OBJ_MGR_H
#define MOVE_AND_FLOOR_C_OBJ_MGR_H

class MoveCObj;
class FloorCObj;
class CollideObjInitializer;

class MoveAndFloorCObjMgr{
	public:
		virtual ~MoveAndFloorCObjMgr();
		virtual MoveCObj *activateMoveCObj() = 0;
		virtual FloorCObj *activateFloorCObj() = 0;
		virtual void initFloors(CollideObjInitializer *) = 0;
		virtual void resetObjs() = 0;
};

#endif
