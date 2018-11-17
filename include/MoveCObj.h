#ifndef MOVE_C_OBJ_H
#define MOVE_C_OBJ_H

#include "CollideObj.h"

class FloorCObj;

class MoveCObj : public CollideObj{
	private:
		// ��`�𓮂������������֓������ۂɁA�Ίp�ɂƂ����_��S�čX�V��������p�֐�
		// ���̂Ƃ����̑��݂Ȃǂ��l�������C���͍s��Ȃ�
		void moveToXY(double, double);
		// �w�肳�ꂽ���̕\�ʂ�, MoveCObj�̉������S�������I�Ɉړ�����������p�֐�
		void setFloorSurface(FloorCObj *);
		// �w�肳�ꂽ�ǂ̕\�ʂɋ����I�Ɉړ�����������p�֐�
		void setWallWithRightCollisionSurface(FloorCObj *);
		void setWallWithLeftCollisionSurface(FloorCObj *);
		// ����̍��W�ɂ�����MoveCObj�̉������A�����ォ�������肷������p�֐�
		// �ݒu��Ԃ͏�Ɣ��肳���
		bool isUpperSideOfFloor(double, double, FloorCObj *);
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
		void setLeftTopXY(double, double);
		bool isOnWall();
		bool isOnWallWithRightCollision();
		bool isOnWallWithLeftCollision();
		bool isOnCeiling();

		virtual double getLeftX();
		virtual double getTopY();
		virtual double getRightX();
		virtual double getBottomY();
		virtual void activate(double, double, double, double);
		virtual void setInactive();
		virtual void interact(CollideObj *);
};

#endif
