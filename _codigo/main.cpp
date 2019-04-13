#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include <stdlib.h>
#include <time.h>

#include "ListaCadastral.cpp"
#include "Background.h"
#include "BackOnigiri.h"
#include "OtavsTitle.h"
#include "Melhoria.h"
#include "Otavs.h"
#include "ClickOnigiri.h"
#include "Creditos.h"

#include <iostream>
using namespace std;

//Variaveis globais
const int WIDTH = 1080;
const int HEIGHT = 720;
const int NUM_CLICK_ONIGIRIS = 20;
const int NUM_MELHORIAS = 8;

//Musicas e efeitos sonoros
ALLEGRO_SAMPLE *omfgDogs = NULL;
ALLEGRO_SAMPLE_INSTANCE *omfgDogsInstance = NULL;
ALLEGRO_SAMPLE *klezmerParty = NULL;
ALLEGRO_SAMPLE_INSTANCE *klezmerPartyInstance = NULL;
ALLEGRO_SAMPLE *sadHokage = NULL;
ALLEGRO_SAMPLE_INSTANCE *sadHokageInstance = NULL; 
ALLEGRO_SAMPLE *arnoldSonim = NULL;
ALLEGRO_SAMPLE_INSTANCE *arnoldSonimInstance = NULL;

enum STATE{TITLE, INSTRUCTIONS, PLAYING, TWIST, END};

ListaCadastral<int> listaAntes;
ListaCadastral<int> listaDepois;

//Funcoes globais
void ChangeState(int &state, int newState);

int main(void){
	
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int state = -1;
	int posX = WIDTH / 2;
	int posY = HEIGHT / 2;
	
	int contadorGeral = 0;
	int otavsTitleFrame = 0;
	int otavsFrame = 0;
	bool isOtavsDeOculos = false;
	bool isMouseEsquerdoApertado = false;
	int clickOnigCont = 0;
	int otavsTwistFrame = 0;
	int curOnigiri = 0;
	int valorDoClick = 1;
	int vaiAcabar = 0;
	
	int melhoriaXinicial = 20;
	int melhoriaYinicial = 100;
	int custo = 99999;
	
	int segundos = 0;
	int minutos = 0;
	bool homem = false;
	int caracolFrame = 0;
	int contadorPlaying = 0;

	//object variables
	Background back;
	BackOnigiri backOnigiri[16];
	OtavsTitle otavsTitle;
	Melhoria melhoria[NUM_MELHORIAS];
	Otavs otavs;
	ClickOnigiri clickOnigiri[NUM_CLICK_ONIGIRIS];
	OtavsTitle otavsTwist;
	OtavsTitle caracolAlado;
	Creditos creditos;
	int playWidth = 0, playHeight = 0, playMouseWidth = 0, playMouseHeight = 0, twistWidth = 0, twistHeight = 0, twistMouseWidth = 0, twistMouseHeight = 0;
	int melhoriaXantes[NUM_MELHORIAS];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *fontTimes = NULL;
	ALLEGRO_BITMAP *backImage = NULL;
	ALLEGRO_BITMAP *backOnigiriImage = NULL;
	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *otavsTitleImage = NULL;
	ALLEGRO_BITMAP *playButton = NULL;
	ALLEGRO_BITMAP *playMouse = NULL;
	ALLEGRO_BITMAP *infosImage = NULL;
	ALLEGRO_BITMAP *curOnigiriImage = NULL;
	ALLEGRO_BITMAP *lojaImage = NULL;
	ALLEGRO_BITMAP *inventarioImage = NULL;
	ALLEGRO_BITMAP *melhoriasSpriteImage = NULL;
	ALLEGRO_BITMAP *checkImage = NULL;
	ALLEGRO_BITMAP *vazioImage = NULL;
	ALLEGRO_BITMAP *otavsImage = NULL;
	ALLEGRO_BITMAP *clickOnigiriImage = NULL;
	ALLEGRO_BITMAP *otavsTwistImage = NULL;
	ALLEGRO_BITMAP *twistTextoImage = NULL;
	ALLEGRO_BITMAP *twistButton = NULL;
	ALLEGRO_BITMAP *twistMouse = NULL;
	ALLEGRO_BITMAP *caracolImage = NULL;
	ALLEGRO_BITMAP *fade = NULL;
	ALLEGRO_BITMAP *creditosImage = NULL;
	ALLEGRO_SAMPLE *nham = NULL;
	ALLEGRO_SAMPLE *uee = NULL;
	ALLEGRO_SAMPLE *caracol = NULL;
	ALLEGRO_SAMPLE *partiuBauru = NULL;
	ALLEGRO_SAMPLE *otavsNinja = NULL;
	ALLEGRO_SAMPLE *sim = NULL;

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
	
	al_reserve_samples(10);

	omfgDogs = al_load_sample("audio/omfgDogs.ogg");
	klezmerParty = al_load_sample("audio/klezmerParty.ogg");
	arnoldSonim = al_load_sample("audio/arnoldSonim.ogg");
	sadHokage = al_load_sample("audio/sadHokage.ogg");
	
	omfgDogsInstance = al_create_sample_instance(omfgDogs);
	al_set_sample_instance_playmode(omfgDogsInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(omfgDogsInstance, al_get_default_mixer());
	
	klezmerPartyInstance = al_create_sample_instance(klezmerParty);
	al_set_sample_instance_playmode(klezmerPartyInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(klezmerPartyInstance, al_get_default_mixer());
	
	sadHokageInstance = al_create_sample_instance(sadHokage);
	al_set_sample_instance_playmode(sadHokageInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sadHokageInstance, al_get_default_mixer());
	
	arnoldSonimInstance = al_create_sample_instance(arnoldSonim);
	al_set_sample_instance_playmode(arnoldSonimInstance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(arnoldSonimInstance, al_get_default_mixer());
	
	backImage = al_load_bitmap("img/background.png");
	backOnigiriImage = al_load_bitmap("img/backOnigiri.png");
	al_convert_mask_to_alpha(backOnigiriImage, al_map_rgb(33, 45, 84));
	titleImage = al_load_bitmap("img/title.png");
	otavsTitleImage = al_load_bitmap("img/otavsTitleSprite.png");
	playButton = al_load_bitmap("img/play128.png");
	playMouse = al_load_bitmap("img/playMouse.png");
	infosImage = al_load_bitmap("img/infos.png");
	lojaImage = al_load_bitmap("img/loja.png");
	inventarioImage = al_load_bitmap("img/inventario.png");
	melhoriasSpriteImage = al_load_bitmap("img/melhoriasSprite.png");
	checkImage = al_load_bitmap("img/check.png");
	vazioImage = al_load_bitmap("img/vazio.png");
	curOnigiriImage = al_load_bitmap("img/curOnigiriNew.png");
	otavsImage = al_load_bitmap("img/otavsSpriteSheet.png");
	clickOnigiriImage = al_load_bitmap("img/clickSprite.png");
	otavsTwistImage = al_load_bitmap("img/otavsTwist.png");
	twistTextoImage = al_load_bitmap("img/twistTexto.png");
	twistButton = al_load_bitmap("img/twistButton.png");
	twistMouse = al_load_bitmap("img/twistMouse.png");
	caracolImage = al_load_bitmap("img/caracol.png");
	fade = al_load_bitmap("img/fade.png");
	creditosImage = al_load_bitmap("img/creditos.png");
	
	nham = al_load_sample("audio/nham.ogg");
	uee = al_load_sample("audio/uee.ogg");
	caracol = al_load_sample("audio/caracol.ogg");
	partiuBauru = al_load_sample("audio/partiuBauru.ogg");
	otavsNinja = al_load_sample("audio/otavsNinja.ogg");
	sim = al_load_sample("audio/sim.ogg");
	
	fontTimes = al_load_font("fontes/timesbd.ttf", 32, 0);

	playWidth = al_get_bitmap_width(playButton);
	playHeight = al_get_bitmap_height(playButton);
	playMouseWidth = al_get_bitmap_width(playMouse);
	playMouseHeight = al_get_bitmap_height(playMouse);
	twistWidth = al_get_bitmap_width(twistButton);
	twistHeight = al_get_bitmap_height(twistButton);
	twistMouseWidth = al_get_bitmap_width(twistMouse);
	twistMouseHeight = al_get_bitmap_height(twistMouse);

	ChangeState(state, TITLE);

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
	
	otavsTitle.InitOtavsTitle(WIDTH / 2, HEIGHT / 2 + 20, 230, 370, otavsTitleImage);
	
	for(int i = 0; i < NUM_MELHORIAS; i++){	
		switch(i){
			case 0:
				custo = 50;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial, custo, melhoriasSpriteImage);
				break;
			case 1:
				custo = 200;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + melhoria[i].getFrameHeight() + 2, custo, melhoriasSpriteImage);
				break;
			case 2:
				custo = 400;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + (melhoria[i].getFrameHeight() * 2) + 4, custo, melhoriasSpriteImage);
				break;
			case 3:
				custo = 2000;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + (melhoria[i].getFrameHeight() * 3) + 6, custo, melhoriasSpriteImage);
				break;
			case 4:
				custo = 4000;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + (melhoria[i].getFrameHeight() * 4) + 8, custo, melhoriasSpriteImage);
				break;
			case 5:
				custo = 16000;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + (melhoria[i].getFrameHeight() * 5) + 10, custo, melhoriasSpriteImage);
				break;
			case 6:
				custo = 32000;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + (melhoria[i].getFrameHeight() * 6) + 12, custo, melhoriasSpriteImage);
				break;
			case 7:
				custo = 96000;
				melhoria[i].InitMelhoria(i, melhoriaXinicial, melhoriaYinicial + (melhoria[i].getFrameHeight() * 7) + 14, custo, melhoriasSpriteImage);
				break;
		}
		melhoriaXantes[i] = melhoria[i].getX();
		melhoria[i].setCurFrame(0);
		listaAntes.Insere(i);
		
	}
	
	otavs.InitOtavs(WIDTH / 2, HEIGHT / 2, otavsImage);
	
	for(int initCont = 0; initCont < NUM_CLICK_ONIGIRIS; initCont++){
		clickOnigiri[initCont].InitClickOnigiri(clickOnigiriImage);
	}
	
	otavsTwist.InitOtavsTitle(181, HEIGHT / 2, 282, 435, otavsTwistImage);
	caracolAlado.InitOtavsTitle(WIDTH / 2 + 6, 680, 69, 64, caracolImage);
	
	creditos.InitCreditos(creditosImage);
	creditos.ReadyCreditos();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
			
			if(state == TITLE){
			}
			else if(state == PLAYING){
				if(!listaAntes.EstaNaLista(5)){
					isOtavsDeOculos = true;
				}
				
				if(posX >= WIDTH / 2 - 100 && posX <= WIDTH / 2 + 84 && posY >= 190 + 34 && posY <= 190 + 290){
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
					if(isMouseEsquerdoApertado){
						otavsFrame = 3;
					}else{
						otavsFrame = 2;
					}
					
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					if(isOtavsDeOculos){
						otavsFrame = 1;
					}else{
						otavsFrame = 0;
					}
				}
				
				for(int updateCont = 0; updateCont < NUM_CLICK_ONIGIRIS; updateCont++){	
					clickOnigiri[updateCont].UpdateClickOnigiri();
				}
				
				contadorPlaying++;
				if(contadorPlaying >= 60){
					contadorPlaying = 0;
					segundos++;
				}
				if(segundos >= 60){
					segundos = 0;
					minutos++;
				}
				if(minutos >= 12){
					homem = true;
					minutos = 12;
				}
			}
			else if(state == END){
				creditos.UpdateCreditos();
			}
			
			contadorGeral++;
			if(contadorGeral >= 60){
				contadorGeral = 0;
			}
			
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1){
				isMouseEsquerdoApertado = true;
				
				if(state == TITLE){
					if((posX >= WIDTH / 2 - playWidth / 2) && (posX <= WIDTH / 2 - playWidth / 2 + playWidth) &&
						(posY >= 630 - playHeight / 2) && (posY <= 630 - playHeight / 2 + playHeight)){
							ChangeState(state, INSTRUCTIONS);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
				
				}else if(state == INSTRUCTIONS){
					
					if((posX >= WIDTH / 2 - playWidth / 2) && (posX <= WIDTH / 2 - playWidth / 2 + playWidth) &&
						(posY >= 630 - playHeight / 2) && (posY <= 630 - playHeight / 2 + playHeight)){
							ChangeState(state, PLAYING);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
					
				}else if(state == PLAYING){
						if(posX >= WIDTH / 2 - 100 && posX <= WIDTH / 2 + 84 && posY >= 190 + 34 && posY <= 190 + 290){
							clickOnigiri[clickOnigCont].ClickClickOnigiri(posX, posY);
							clickOnigCont++;
							if(clickOnigCont >= NUM_CLICK_ONIGIRIS){
								clickOnigCont = 0;
							}
							curOnigiri += valorDoClick;
							if(curOnigiri >= 99999){
								curOnigiri = 99999;
							}
						}
						for(int i = 0; i < NUM_MELHORIAS; i++){
							if(posX >= melhoria[i].getX() && posX <= melhoria[i].getX() + melhoria[i].getFrameWidth() && 
								posY >= melhoria[i].getY() && posY <= melhoria[i].getY() + melhoria[i].getFrameHeight()){
									if(curOnigiri >= melhoria[i].getCusto() && melhoria[i].isLive()){
										valorDoClick *= 2;
										curOnigiri -= melhoria[i].getCusto();
										listaAntes.Retira(i);
										switch(i){
											case 0:
												al_play_sample(nham, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 1:
												al_play_sample(uee, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 2:
												al_play_sample(nham, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 3:
												al_play_sample(caracol, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 4:
												al_play_sample(otavsNinja, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 5:
												al_play_sample(sim, 2.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 6:
												al_play_sample(partiuBauru, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
											case 7:
												al_play_sample(uee, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
												break;
										}
										listaDepois.Insere(i);
										melhoria[i].setLive(false);
									}
							}
						}
						
				}
				else if(state == TWIST){
					if((posX >= 701 - twistWidth / 2) && (posX <= 701 - twistWidth / 2 + twistWidth) &&
						(posY >= (3 * HEIGHT / 4) - 20 - twistHeight / 2) && (posY <= (3 * HEIGHT / 4) - 20 - twistHeight / 2 + twistHeight)){
							ChangeState(state, END);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
				}
				else if(state == END){
					
				}
			}	
		}else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			isMouseEsquerdoApertado = false;
		}else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
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
						
			
			//if um por um 1
			if(state == TITLE){
				
			}
			else if(state == INSTRUCTIONS){
				
			}
			else if(state == PLAYING){
				
			}else if(state == END){
				creditos.DrawCreditos();
				if(creditos.getForaDaTela())
					done = true;
			}
			
			//if geral 1
			if(state == TITLE || state == INSTRUCTIONS || state == PLAYING || state == TWIST){
				back.DrawBackground();
			}
			
			//if um por um 2
			if(state == TITLE){
				al_draw_bitmap(titleImage, WIDTH / 2 - 333 / 2, 20, 0);
				
				otavsTitleFrame = (contadorGeral / 30) % 2;
				otavsTitle.setCurFrame(otavsTitleFrame);
				otavsTitle.DrawOtavsTitle();
				
				if((posX >= WIDTH / 2 - playWidth / 2) && (posX <= WIDTH / 2 - playWidth / 2 + playWidth) &&
					(posY >= 630 - playHeight / 2) && (posY <= 630 - playHeight / 2 + playHeight)){
						al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
						al_draw_bitmap(playMouse, WIDTH / 2 - playMouseWidth / 2, 630 - playMouseHeight / 2, 0);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2, 630 - playHeight / 2, 0);
				}
				
			}
			else if(state == INSTRUCTIONS){
				
				al_draw_bitmap(infosImage, 20, 110, 0);
				
				if((posX >= WIDTH / 2 - playWidth / 2) && (posX <= WIDTH / 2 - playWidth / 2 + playWidth) &&
					(posY >= 630 - playHeight / 2) && (posY <= 630 - playHeight / 2 + playHeight)){
						al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
						al_draw_bitmap(playMouse, WIDTH / 2 - playMouseWidth / 2, 630 - playMouseHeight / 2, 0);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2, 630 - playHeight / 2, 0);
				}
				
			}
			else if(state == PLAYING){
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
				
				al_draw_bitmap(lojaImage, 20, 25, 0);
				al_draw_bitmap(inventarioImage, 740, 25, 0);
				
				for(int i = 0; i < NUM_MELHORIAS; i++){
					if(listaAntes.EstaNaLista(i)){
						if(curOnigiri >= melhoria[i].getCusto() / 2 && curOnigiri < melhoria[i].getCusto() && melhoria[i].isLive()){
							melhoria[i].setCurFrame(1);
							melhoria[i].setJorge(true);
						}else if(curOnigiri >= melhoria[i].getCusto() && melhoria[i].isLive()){
							melhoria[i].setCurFrame(2);
							melhoria[i].setJorge(true);
						}else if(curOnigiri < melhoria[i].getCusto() && !melhoria[i].isJorge()){
							melhoria[i].setCurFrame(0);
						}else if(curOnigiri < melhoria[i].getCusto() && melhoria[i].isJorge()){
							melhoria[i].setCurFrame(1);
						}
						
						al_draw_bitmap(vazioImage, 740, melhoria[i].getY(), 0);
					}else{
						melhoria[i].setX(740);
						al_draw_bitmap(checkImage, melhoriaXantes[i], melhoria[i].getY(), 0);
					}
					
					if(!melhoria[i].isLive()){
						melhoria[i].setCurFrame(3);
					}
					melhoria[i].DrawMelhoria();
				}
				
				al_draw_bitmap(curOnigiriImage, WIDTH / 2 - 78, 100 - 20, 0);
				al_draw_textf(fontTimes, al_map_rgb(223, 143, 0), WIDTH / 2 - 12, 82, ALLEGRO_ALIGN_LEFT, "%d", curOnigiri);
				
				otavs.setCurFrame(otavsFrame);
				otavs.DrawOtavs();
				
				for(int drawCont = 0; drawCont < NUM_CLICK_ONIGIRIS; drawCont++){
					clickOnigiri[drawCont].DrawClickOnigiri();
				}
				
				if(listaAntes.Vazia()){
					vaiAcabar++;
					al_draw_tinted_bitmap(fade, al_map_rgba_f(0, 0, 0, vaiAcabar * 0.005), 0, 0, 0);	
					if(vaiAcabar >= 200){
						ChangeState(state, TWIST);
					}
				}
				
			}else if(state == TWIST){
				otavsTwistFrame = (contadorGeral / 30) % 2;
				otavsTwist.setCurFrame(otavsTwistFrame);
				otavsTwist.DrawOtavsTitle();
				
				al_draw_bitmap(twistTextoImage, 362, (HEIGHT / 4) - 40, 0);
				
				if((posX >= 701 - twistWidth / 2) && (posX <= 701 - twistWidth / 2 + twistWidth) &&
					(posY >= (3 * HEIGHT / 4) - 20 - twistHeight / 2) && (posY <= (3 * HEIGHT / 4) - 20 - twistHeight / 2 + twistHeight)){
						al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
						al_draw_bitmap(twistMouse, 701 - twistMouseWidth / 2, (3 * HEIGHT / 4) - 20 - twistMouseHeight / 2, 0);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					al_draw_bitmap(twistButton, 701 - twistWidth / 2, (3 * HEIGHT / 4) - 20 - twistHeight / 2, 0);
				}
		
			}
			else if(state == END){
				
			}
			
			if(state == PLAYING || state == TWIST){
				if(homem){
					caracolFrame = (contadorGeral / 10) % 2;
					caracolAlado.setCurFrame(caracolFrame);
					caracolAlado.DrawOtavsTitle();
				}else{
					al_draw_textf(fontTimes, al_map_rgb(223, 143, 0), WIDTH / 2, 680, ALLEGRO_ALIGN_CENTRE, "%02d:%02d", minutos, segundos);
				}
			}
			if(state == PLAYING){
				if(listaAntes.Vazia()){
					vaiAcabar++;
					al_draw_tinted_bitmap(fade, al_map_rgba_f(0, 0, 0, vaiAcabar * 0.005), 0, 0, 0);	
					if(vaiAcabar >= 200){
						ChangeState(state, TWIST);
					}
				}
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	
	
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_sample(klezmerParty);
	al_destroy_sample_instance(klezmerPartyInstance);
	al_destroy_sample(omfgDogs);
	al_destroy_sample_instance(omfgDogsInstance);
	al_destroy_sample(sadHokage);
	al_destroy_sample_instance(sadHokageInstance);
	al_destroy_sample(arnoldSonim);
	al_destroy_sample_instance(arnoldSonimInstance);
	al_destroy_font(fontTimes);
	al_destroy_bitmap(backImage);
	al_destroy_bitmap(backOnigiriImage);
	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(otavsTitleImage);
	al_destroy_bitmap(playButton);
	al_destroy_bitmap(playMouse);
	al_destroy_bitmap(melhoriasSpriteImage);
	al_destroy_bitmap(checkImage);
	al_destroy_bitmap(vazioImage);
	al_destroy_bitmap(curOnigiriImage);
	al_destroy_bitmap(otavsImage);
	al_destroy_bitmap(clickOnigiriImage);
	al_destroy_bitmap(otavsTwistImage);
	al_destroy_bitmap(twistTextoImage);
	al_destroy_bitmap(twistButton);
	al_destroy_bitmap(twistMouse);
	al_destroy_bitmap(caracolImage);
	al_destroy_bitmap(fade);
	al_destroy_sample(nham);
	al_destroy_sample(uee);
	al_destroy_sample(caracol);
	al_destroy_sample(partiuBauru);
	al_destroy_sample(otavsNinja);
	al_destroy_sample(sim);
	al_destroy_bitmap(creditosImage);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void ChangeState(int &state, int newState){
	if(state == TITLE){
	}
	else if(state == PLAYING){
		for(int i = 0; i < NUM_MELHORIAS; i++){
			listaDepois.Retira(i);
		}
		al_stop_sample_instance(omfgDogsInstance);
	}
	else if(state == INSTRUCTIONS){
		al_stop_sample_instance(klezmerPartyInstance);
	}
	else if(state == TWIST){
		al_stop_sample_instance(sadHokageInstance);
	}
	else if(state == END){
		al_stop_sample_instance(arnoldSonimInstance);
	}

	state = newState;

	if(state == TITLE){
		al_play_sample_instance(klezmerPartyInstance);
	}
	else if(state == PLAYING){
		al_play_sample_instance(omfgDogsInstance);
	}
	else if(state == INSTRUCTIONS){
	}
	else if(state == TWIST){
		al_play_sample_instance(sadHokageInstance);
	}
	else if(state == END){
		al_play_sample_instance(arnoldSonimInstance);
	}
}
