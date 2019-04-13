#include "Otavs.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
		
Otavs::Otavs(){
	this->x = 0;
	this->y = 0;
	this->maxFrame = 0;
	this->frameWidth = 0;
	this->frameHeight = 0;
	this->scale = 0;
	this->image = NULL;
}

void Otavs::InitOtavs(int x, int y, ALLEGRO_BITMAP *image){
	this->x = x;
	this->y = y;
	this->maxFrame = 0;      // MUDAR
	this->frameWidth = 0;    // ISSO
	this->frameHeight = 0;   // PLEASE
	this->scale = 1;
	this->image = image;
}

void Otavs::DrawOtavs(){
/*	al_draw_tinted_scaled_rotated_bitmap_region(image,
   sx, sy, sw, sh,      // source bitmap region
   al_map_rgb(1, 1, 1), // color, just use white if you don't want a tint
   cx, cy,              // center of rotation/scaling
   float dx, float dy,  // destination
   xscale, yscale,      // scale
   0, 0));              // angle and flags */
}

void Otavs::setX(int x){
	this->x = x;
}

void Otavs::setY(int y){
	this->y = y;
}

void Otavs::setScale(double scale){
	this->scale = scale;
}

int Otavs::getX(){
	return this->x;
}

int Otavs::getY(){
	return this->y;
}

int Otavs::getMaxFrame(){
	return this->maxFrame;
}

int Otavs::getFrameWidth(){
	return this->frameWidth;
}

int Otavs::getFrameHeight(){
	return this->frameHeight;
}

double Otavs::getScale(){
	return this->scale;
}
