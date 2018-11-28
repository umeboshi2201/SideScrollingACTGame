#include "DxlibImageMaker.h"
#include "Image.h"
#include "DxlibTestBoxAndLineImage.h"

DxlibImageMaker::DxlibImageMaker(){
	this->imgLength = 4;
	//this->imgs = new DxlibTestBoxAndLineImage[imgLength]{DxlibTestBoxAndLineImage(100, 0, true), DxlibTestBoxAndLineImage(100, -100, true), DxlibTestBoxAndLineImage(100, 100, true)};
	this->imgs = new Image*[imgLength];
	this->imgs[0] = new DxlibTestBoxAndLineImage(20, 50, false);
	this->imgs[1] = new DxlibTestBoxAndLineImage(100, 0, true);
	this->imgs[2] = new DxlibTestBoxAndLineImage(100, -100, true);
	this->imgs[3] = new DxlibTestBoxAndLineImage(100, 100, true);
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
