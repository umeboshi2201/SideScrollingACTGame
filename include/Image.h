#ifndef IMAGE_H
#define IMAGE_H

class Image{
	public:
		virtual ~Image(){}
		// 描画関数
		// 指定された座標に画像の左上が来るように描画する
		virtual void drawImage(int, int) = 0;
};

#endif
