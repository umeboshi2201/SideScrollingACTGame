#ifndef IMAGE_MAKER_H
#define IMAGE_MAKER_H

class Image;

class ImageMaker{
	public:
		virtual ~ImageMaker(){}
		virtual Image **getImages(int *length) = 0;
};

#endif
