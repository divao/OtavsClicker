#include "Melhoria.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

Melhoria::Melhoria(){
	id = 0;
	x = 0;
	y = 0;
	custo = 99999;
	live = false;
		
	curFrame = 0;
	maxFrame = 3;
	frameWidth = 320;
	frameHeight = 75;
		
	image = NULL;
}

void Melhoria::InitMelhoria(int id, int x, int y, int custo, ALLEGRO_BITMAP *image){
	this->id = id;
	this->x = x;
	this->y = y;
	this->custo = custo;
	this->live = true;
		
	curFrame = 0;
	maxFrame = 3;
	frameWidth = 320;
	frameHeight = 75;
		
	this->image = image;
}

void Melhoria::DrawMelhoria(){
	al_draw_bitmap_region(image, curFrame * frameWidth, id * frameHeight, frameWidth, frameHeight, x, y, 0);
}

void Melhoria::setX(int x){
	this->x = x;
}

void Melhoria::setY(int y){
	this->y = y;
}

void Melhoria::setCurFrame(int curFrame){
	this->curFrame = curFrame;
}

int Melhoria::getX(){
	return this->x;
}

int Melhoria::getY(){
	return this->y;
}

int Melhoria::getCurFrame(){
	return this->curFrame;
}

int Melhoria::getFrameWidth(){
	return this->frameWidth;
}

int Melhoria::getFrameHeight(){
	return this->frameHeight;
}

bool Melhoria::operator!=(const Melhoria &m) const{
	if(this->id != m.id)
		return true;
	else
		return false;
}

bool Melhoria::operator==(const Melhoria &m) const{
	if(this->id == m.id)
		return true;
	else
		return false;
}

int Melhoria::getCusto(){
	return this->custo;
}

void Melhoria::setLive(bool live){
	this->live = live;
}

bool Melhoria::isLive(){
	return this->live;
}
