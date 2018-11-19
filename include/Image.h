#ifndef IMAGE_H
#define IMAGE_H

class Image{
	public:
		// 描画関数
		virtual void drawImage(int, int) = 0;
		// void drawBox(int, int, int, int, bool);
		// void drawLine(int, int, int, int);
};

#endif
