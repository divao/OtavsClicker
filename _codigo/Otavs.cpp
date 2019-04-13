#include "Otavs.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
		
Otavs::Otavs(){
	this->x = 0;
	this->y = 0;
	this->curFrame = 0;
	this->frameWidth = 300;
	this->frameHeight = 340;
	this->image = NULL;
}

void Otavs::InitOtavs(int x, int y, ALLEGRO_BITMAP *image){
	this->x = x;
	this->y = y;
	this->curFrame = 0;
	this->frameWidth = 300;    
	this->frameHeight = 340;
	this->image = image;
}

void Otavs::DrawOtavs(){
	al_draw_bitmap_region(image, curFrame * frameWidth, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Otavs::setX(int x){
	this->x = x;
}

void Otavs::setY(int y){
	this->y = y;
}

void Otavs::setCurFrame(int curFrame){
	this->curFrame = curFrame;
}

int Otavs::getX(){
	return this->x;
}

int Otavs::getY(){
	return this->y;
}

int Otavs::getCurFrame(){
	return this->curFrame;
}

int Otavs::getFrameWidth(){
	return this->frameWidth;
}

int Otavs::getFrameHeight(){
	return this->frameHeight;
}
