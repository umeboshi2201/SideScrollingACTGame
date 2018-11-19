#include "Image.h"
#include "DxLib.h"

void Image::drawBox(int leftX, int topY, int rightX, int bottomY, bool fillFlag){
	unsigned int Cr;
	
	// 青色の値を取得
	Cr = GetColor(0, 0, 255);
	
	// 四角形を描画
	DrawBox(leftX, topY, rightX - 1, bottomY - 1, Cr, fillFlag);

	return;
}

void Image::drawLine(int startX, int startY, int endX, int endY){
	unsigned int Cr;
	
	// 白色の値を取得
	Cr = GetColor( 255 , 255 , 255 ) ;
	
	// 線を描画
	DrawLine(startX, startY, endX, endY, Cr);

	return;
}
