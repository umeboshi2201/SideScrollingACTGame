#ifndef DXLIB_IMAGE_MAKER_H
#define DXLIB_IMAGE_MAKER_H

#include "ImageMaker.h"

class Image;

class DxlibImageMaker : public ImageMaker{
	private:
		Image **imgs;
		int imgLength;
	public:
		DxlibImageMaker();
		virtual ~DxlibImageMaker();
		virtual Image **getImages(int *length);
};

#endif
