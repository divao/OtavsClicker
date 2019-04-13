#include "OtavsTitle.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
		
OtavsTitle::OtavsTitle(){
	this->x = 0;
	this->y = 0;
	this->curFrame = 0;
	this->frameWidth = 230;
	this->frameHeight = 370;
	this->image = NULL;
}

void OtavsTitle::InitOtavsTitle(int x, int y, ALLEGRO_BITMAP *image){
	this->x = x;
	this->y = y;
	this->curFrame = 0;
	this->frameWidth = 230;    
	this->frameHeight = 370;
	this->image = image;
}

void OtavsTitle::DrawOtavsTitle(){
	al_draw_bitmap_region(image, curFrame * frameWidth, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void OtavsTitle::setX(int x){
	this->x = x;
}

void OtavsTitle::setY(int y){
	this->y = y;
}

void OtavsTitle::setCurFrame(int curFrame){
	this->curFrame = curFrame;
}

int OtavsTitle::getX(){
	return this->x;
}

int OtavsTitle::getY(){
	return this->y;
}

int OtavsTitle::getCurFrame(){
	return this->curFrame;
}

int OtavsTitle::getFrameWidth(){
	return this->frameWidth;
}

int OtavsTitle::getFrameHeight(){
	return this->frameHeight;
}
