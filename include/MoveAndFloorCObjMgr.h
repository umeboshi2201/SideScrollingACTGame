#ifndef MOVE_AND_FLOOR_C_OBJ_MGR_H
#define MOVE_AND_FLOOR_C_OBJ_MGR_H

class MoveCObj;
class FloorCObj;

class MoveAndFloorCObjMgr{
	protected:
	public:
		MoveAndFloorCObjMgr();
		~MoveAndFloorCObjMgr();
		MoveCObj *activateMoveCObj();
		FloorCObj *activateFloorCObj();
};

#endif
