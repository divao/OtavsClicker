#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include <stdlib.h>
#include <time.h>

#include "Background.h"
#include "BackOnigiri.h"
#include "ClickOnigiri.h"

#include <iostream>
using namespace std;

//Variaveis globais
const int WIDTH = 1080;
const int HEIGHT = 720;
const int NUM_CLICK_ONIGIRIS = 20;

enum STATE{TITLE, INSTRUCTIONS, PLAYING, END};

//Funcoes globais
//void ChangeState(int &state, int newState);

int main(void){
	
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int state = -1;
	int posX = WIDTH / 2;
	int posY = HEIGHT / 2;
	int clickOnigCont = 0;

	//object variables
	Background back;
	BackOnigiri backOnigiri[16];
	ClickOnigiri clickOnigiri[NUM_CLICK_ONIGIRIS];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_SAMPLE *omfgDogs;
	ALLEGRO_FONT *fontDevil = NULL;
	ALLEGRO_BITMAP *backImage = NULL;
	ALLEGRO_BITMAP *backOnigiriImage = NULL;
	ALLEGRO_BITMAP *clickOnigiriImage = NULL;

	//Initialization Functions
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	al_reserve_samples(1);

	omfgDogs = al_load_sample("audio/omfgDogs.ogg");
	
	backImage = al_load_bitmap("img/background.png");
	backOnigiriImage = al_load_bitmap("img/backOnigiri.png");
	al_convert_mask_to_alpha(backOnigiriImage, al_map_rgb(33, 45, 84));
	clickOnigiriImage = al_load_bitmap("img/clickSprite.png");

//	srand(time(NULL));

//	ChangeState(state, TITLE);

	back.InitBackground(0, 0, 1080, 720, backImage);
	
	for(int i = 0; i < 4; i++){
			backOnigiri[i].InitBackOnigiri(i % 4 * 260 + 90, 0 * 180 + 28, backOnigiriImage);	
	}
	for(int i = 4; i < 8; i++){
			backOnigiri[i].InitBackOnigiri(i % 4 * 260 + 90, 1 * 180 + 28, backOnigiriImage);	
	}
	for(int i = 8; i < 12; i++){
			backOnigiri[i].InitBackOnigiri(i % 4 * 260 + 90, 2 * 180 + 28, backOnigiriImage);	
	}
	for(int i = 12; i < 16; i++){
			backOnigiri[i].InitBackOnigiri(i % 4 * 260 + 90, 3 * 180 + 28, backOnigiriImage);	
	}
	
	for(int initCont = 0; initCont < NUM_CLICK_ONIGIRIS; initCont++){
		clickOnigiri[initCont].InitClickOnigiri(clickOnigiriImage);
	}	
	

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_play_sample(omfgDogs, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
			
			for(int updateCont = 0; updateCont < NUM_CLICK_ONIGIRIS; updateCont++){	
				clickOnigiri[updateCont].UpdateClickOnigiri();
			}
			
			
		/*	if(state == TITLE){
			}
			else if(state == PLAYING)
			{}
			else if(state == END)
			{}*/
		
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1){
				
			//	if(posX >= 0 && posX <= 400 && posY >= 0 && posY <= 400){          !!!!!!!!!!!!! POSICAO DO OTAVIO !!!!!!!!!!!!!!!!!!!!!
					clickOnigiri[clickOnigCont].ClickClickOnigiri(posX, posY);
					clickOnigCont++;
					if(clickOnigCont >= NUM_CLICK_ONIGIRIS){
						clickOnigCont = 0;
					}
			//	}

				
			/*	if(state == TITLE){
				
				}else if(state == INSTRUCTIONS){
					
				}else if(state == END){
					
				}*/
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			posX = ev.mouse.x;
			posY = ev.mouse.y;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue)){
			redraw = false; 
						
			back.DrawBackground();
			
			for(int i = 0; i < 16; i++){
				if(++backOnigiri[i].frameCountX >= backOnigiri[i].frameDelay){
					if(++backOnigiri[i].curFrameX >= backOnigiri[i].maxFrameX)
						backOnigiri[i].curFrameX = 0;

					backOnigiri[i].frameCountX = 0;
				
					if(++backOnigiri[i].curFrameY >= backOnigiri[i].maxFrameY)
						backOnigiri[i].curFrameY = 0;

					backOnigiri[i].frameCountY = 0;
				}
				
			backOnigiri[i].DrawBackOnigiri();
			}
			
			for(int drawCont = 0; drawCont < NUM_CLICK_ONIGIRIS; drawCont++){
				clickOnigiri[drawCont].DrawClickOnigiri();
			}

		/*	if(state == TITLE){
				
			}
			else if(state == INSTRUCTIONS){
				
				
			}
			else if(state == PLAYING){
			}*/
		
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	
	
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_sample(omfgDogs);
	al_destroy_bitmap(backImage);
	al_destroy_bitmap(backOnigiriImage);
	al_destroy_bitmap(clickOnigiriImage);
	al_destroy_display(display);						//destroy our display object

	return 0;
}
/*
void ChangeState(int &state, int newState){
	if(state == TITLE){
	}
	else if(state == PLAYING){
		pCaipira.desempilhaTudo();
		pDiabo.desempilhaTudo();
		if(venceu)
			caipiraScore++;
		else
			diaboScore++;
	}
	else if(state == INSTRUCTIONS){
	}
	else if(state == END){
	}

	state = newState;

	if(state == TITLE){
	}
	else if(state == PLAYING){
		contador = 1;
		antCont = 13;
		Pilha <int> pAux;
		Pilha <int> pEmbaralhada;
		for(int i = 0; i < 52; i++){
			pAux.empilha(i);
		}
		pEmbaralhada = *pAux.embaralha();
		int jorge;
		for(int i = 0; i < 26; i++){
			pEmbaralhada.desempilha(jorge);
			pCaipira.empilha(jorge);
			pEmbaralhada.desempilha(jorge);
			pDiabo.empilha(jorge);
		}
		desempilhaOk = true;
	}
	else if(state == INSTRUCTIONS){
	}
	else if(state == END){
	}
}*/
