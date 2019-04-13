#include "Creditos.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

Creditos::Creditos(){
	foraDaTela = false;
	live = false;
	x = (0 + 1080 - 720) / 2;
	y = 720;
	yFinal = 720 + 720; //720 + altura da imagem
}

void Creditos::InitCreditos(ALLEGRO_BITMAP *image){
	foraDaTela = false;
	live = false;
	x = (0 + 1080 - 720) / 2;
	y = 720;
	yFinal = 720 + 720; //720 + altura da imagem
	this->image = image;
}

void Creditos::DrawCreditos(){
	if(live){
		al_draw_bitmap(image, x, y, 0);
	}
}

void Creditos::ReadyCreditos(){
	if(!live){
		live = true;
	}
}

void Creditos::UpdateCreditos(){
	if(live){
		y -= 2;
		yFinal -= 2;
		if(yFinal <= 0){
			live = false;
			foraDaTela = true;
		}
	}
}

bool Creditos::getForaDaTela(){
	return this->foraDaTela;
}
