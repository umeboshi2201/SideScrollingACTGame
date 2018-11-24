#ifndef B_F_MOVE_AND_FLOOR_C_OBJ_MGR_H
#define B_F_MOVE_AND_FLOOR_C_OBJ_MGR_H

#include "MoveAndFloorCObjMgr.h"

class MoveCObj;
class FloorCObj;
class CollideObjInitializer;

class BFMoveAndFloorCObjMgr : public MoveAndFloorCObjMgr{
	private:
		MoveCObj *moveCObjs;
		FloorCObj *floorCObjs;
		int moveCObjLength;
		int floorCObjLength;
	public:
		BFMoveAndFloorCObjMgr();
		virtual ~BFMoveAndFloorCObjMgr();
		virtual MoveCObj *getFreeMoveCObj();
		virtual FloorCObj *getFreeFloorCObj();
		virtual void initFloors(CollideObjInitializer *);
		virtual void collisionCalc();
		virtual void resetObjs();
};

#endif
