#include "DxlibImageMaker.h"
#include "Image.h"
#include "DxlibTestBoxAndLineImage.h"

DxlibImageMaker::DxlibImageMaker(){
	this->imgLength = 6;
	this->imgs = new Image*[imgLength];
	this->imgs[0] = new DxlibTestBoxAndLineImage(40, 50, false, 0, 255, 0);
	this->imgs[1] = new DxlibTestBoxAndLineImage(100, 0, true, 255, 0, 0);
	this->imgs[2] = new DxlibTestBoxAndLineImage(100, -100, true, 255, 0, 0);
	this->imgs[3] = new DxlibTestBoxAndLineImage(100, 100, true, 255, 0, 0);
	this->imgs[4] = new DxlibTestBoxAndLineImage(0, 100, true, 255, 0, 0);
	this->imgs[5] = new DxlibTestBoxAndLineImage(1000, 1000, false, 255, 255, 255);
}

DxlibImageMaker::~DxlibImageMaker(){
	for(int i = 0; i < this->imgLength; i++){
		delete this->imgs[i];
	}
	delete[] this->imgs;
}

Image **DxlibImageMaker::getImages(int *length){
	*length = this->imgLength;
	return this->imgs;
}
