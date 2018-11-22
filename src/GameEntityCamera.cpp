#include "GameEntityCamera.h"
#include "Image.h"

GameEntityCamera::GameEntityCamera(double width, double height, int layerCount, int nodeCount){
	this->leftX = 0;
	this->topY = 0;
	this->width = width;
	this->height = height;
	if(layerCount <= 0){
		this->layerCount = 1;
	}
	else{
		this->layerCount = layerCount;
	}
	if(nodeCount <= 0){
		this->nodeCount = 1;
	}
	else{
		this->nodeCount = nodeCount;
	}
	this->nodeIndex = 0;
	nodes = new gameEntityCameraNS::ImageNode[nodeCount];
	heads = new gameEntityCameraNS::ImageNode*[layerCount];
	tails = new gameEntityCameraNS::ImageNode*[layerCount];
	for(int i = 0; i < layerCount; i++){
		heads[i] = tails[i] = nullptr;
	}
}

GameEntityCamera::~GameEntityCamera(){
	delete[] nodes;
	delete[] heads;
	delete[] tails;
}

void GameEntityCamera::pushImageNode(gameEntityCameraNS::ImageNode *nodePointer, int layerNum){
	int drawLayer = layerNum - 1;

	if(drawLayer < 0){
		drawLayer = 0;
	}
	else if(this->layerCount <= drawLayer){
		drawLayer = this->layerCount - 1;
	}

	if(heads[drawLayer] == nullptr){
		heads[drawLayer] = tails[drawLayer] = nodePointer;
	}
	else{
		tails[drawLayer]->next = nodePointer;
		tails[drawLayer] = nodePointer;
	}

	return;
}

double GameEntityCamera::getLeftX(){
	return this->leftX;
}

double GameEntityCamera::getTopY(){
	return this->topY;
}

void GameEntityCamera::setLeftX(double leftX){
	this->leftX = leftX;
	return;
}

void GameEntityCamera::setTopY(double topY){
	this->topY = topY;
	return;
}

void GameEntityCamera::setImage(double leftX, double topY, Image *img, int layerNum){

	// 画面に表示できるイメージの数が限界を超えていたら何もしない
	if(this->nodeCount <= this->nodeIndex){
		return;
	}

	nodes[nodeIndex].drawLeftX = leftX;
	nodes[nodeIndex].drawTopY = topY;
	nodes[nodeIndex].img = img;
	nodes[nodeIndex].next = nullptr;
	this->pushImageNode(&nodes[nodeIndex], layerNum);
	nodeIndex++;

	return;
}

void GameEntityCamera::draw(){

	for(int i = 0; i < this->layerCount; i++){
		for(gameEntityCameraNS::ImageNode *tmpHead = this->heads[i]; tmpHead != nullptr; tmpHead = tmpHead->next){
			if((this->leftX - this->width <= tmpHead->drawLeftX) && (tmpHead->drawLeftX <= this->leftX + this->width * 2) && (this->topY - this->height <= tmpHead->drawTopY) && (tmpHead->drawTopY <= this->topY + this->height * 2)){
				double dDisplayAreaX = tmpHead->drawLeftX - this->leftX;
				double dDisplayAreaY = tmpHead->drawTopY - this->topY;
				int iDisplayAreaX = (int)dDisplayAreaX;
				int iDisplayAreaY = (int)dDisplayAreaY;
				tmpHead->img->drawImage(iDisplayAreaX, iDisplayAreaY);
			}
		}

		heads[i] = tails[i] = nullptr;
	}

	this->nodeIndex = 0;
	return;
}
