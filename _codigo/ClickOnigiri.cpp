#include "ClickOnigiri.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

ClickOnigiri::ClickOnigiri(){
	live = false;
	x = 0;
	y = 0;
		
	maxFrameX = 19;
	curFrameX = 0;
	frameCountX = 0;
	frameWidth = 34;
	
	image = NULL;
}

void ClickOnigiri::InitClickOnigiri(ALLEGRO_BITMAP *image){
	live = false;
	this->image = image;
}
void ClickOnigiri::DrawClickOnigiri(){
	if(live){
	
		int fx = curFrameX * frameWidth;

		al_draw_bitmap_region(image, fx, 0, frameWidth, 29, x - frameWidth / 2, y - 29 / 2, 0);
	}
}
void ClickOnigiri::ClickClickOnigiri(int mouseX, int mouseY){
	if(!live){
		x = mouseX;
		y = mouseY;
		live = true;
	}
}
void ClickOnigiri::UpdateClickOnigiri(){
	if(live){
		y -= 2;
		curFrameX++;
		if(curFrameX > maxFrameX){
			live = false;
			curFrameX = 0;
		}
	}
}
