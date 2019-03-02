#include "DxlibTestBoxAndLineImage.h"
#include "DxLib.h"

DxlibTestBoxAndLineImage::DxlibTestBoxAndLineImage(int nextX, int nextY, bool isLine, int rc, int gc, int bc){
	this->nextX = nextX;
	this->nextY = nextY;
	this->isLine = isLine;
	this->rc = rc;
	this->gc = gc;
	this->bc = bc;
}

void DxlibTestBoxAndLineImage::drawImage(int startX, int startY){
	unsigned int Cr;

	if(isLine){
		// 白色の値を取得
		Cr = GetColor(this->rc, this->gc, this->bc);
		
		// 線を描画
		// 終端座標までは描き切られないので、＋１することで書ききらせる
		DrawLine(startX, startY, startX + this->nextX, startY + this->nextY, Cr);

	}
	else{
		// 青色の値を取得
		Cr = GetColor(this->rc, this->gc, this->bc);
		
		// 四角形を描画
		// 指定された点に描画させるための補正
		DrawBox(startX, startY, startX + this->nextX + 1, startY + this->nextY + 1, Cr, true);
	}

	return;
}
