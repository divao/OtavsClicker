#include "BackOnigiri.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

BackOnigiri::BackOnigiri(){
	this->x = 0;
	this->y = 0;
	this->maxFrameX = 10;
	this->maxFrameY = 8;
	this->curFrameX = 0;
	this->curFrameY = 0;
	this->frameCountX = 0;
	this->frameCountY = 0;
	this->frameDelay = 2;
	this->frameWidth = 120;
	this->frameHeight = 120;
	this->image = NULL;
}

void BackOnigiri::InitBackOnigiri(float x, float y, ALLEGRO_BITMAP *image){
	this->x = x;
	this->y = y;
	this->maxFrameX = 10;
	this->maxFrameY = 8;
	this->curFrameX = 0;
	this->curFrameY = 0;
	this->frameCountX = 0;
	this->frameCountY = 0;
	this->frameDelay = 2;
	this->frameWidth = 120;
	this->frameHeight = 120;
	this->image = image;
}

void BackOnigiri::DrawBackOnigiri(){
	al_draw_bitmap_region(image, curFrameX * frameWidth, curFrameY * frameHeight, frameWidth, frameHeight, x, y, 0);
}
