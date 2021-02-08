#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <random>
#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>




using namespace std;
//Globales creación de variables globales
//**********************************************************
const int dim_Y = 600;
const int dim_X = 1328;
const int lastY = floor(dim_Y / 14) * 14;
const int lastX = floor(dim_X / 8) * 8;
#define FPS 60.0
enum Direction { UP = 1, DOWN, RIGHT, LEFT, FORWARD = 1, BACKWARD, STOP = 5 }; //up=1 down=2, right=3, left=4,	forward=1, backward=2		stop=5


//Inclusión de headers
//**********************************************************
#include "Random ints.h"
#include "angles.h"
#include "Road.h"
#include "User Car.h"
#include "Bot Cars.h"
#include "Autopilot.h"
#include "Dash.h"

void must_init(bool test, const char *description) //función para inicializar cosas de allegro
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	al_show_native_message_box(NULL, "ERROR", "Error", "check console for more info", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	exit(1);
}

int main() {
	//Inicialización de las matrices del mapa
	LoadMatrices();

	//inicialización de allegro
	//***************************************************
	must_init(al_init(), "allegro");

	//Definición de la ventana
	//***************************************************
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

	ALLEGRO_DISPLAY *screen;
	screen = al_create_display(dim_X, dim_Y);
	al_set_window_position(screen, 0, 0);
	al_set_window_title(screen, "Simulator");
	must_init(screen, "display");


	//Funcionalidad de imágenes
	//**********************************************************
	must_init(al_init_image_addon(), "images addon");

	ALLEGRO_BITMAP *bluecar = al_load_bitmap("carsprite.png");
	must_init(bluecar, "carsprite.png");
	
	u_car.bmp = bluecar;

	ALLEGRO_BITMAP *bluecarON = al_load_bitmap("carspriteON.png");
	must_init(bluecarON, "carspriteON.png");

	ALLEGRO_BITMAP *botcar = al_load_bitmap("botsprite.png");
	must_init(botcar, "botsprite.png");

	ALLEGRO_BITMAP *brujula = al_load_bitmap("brujula.png");
	must_init(brujula, "brujula.png");

	ALLEGRO_BITMAP *reloj = al_load_bitmap("reloj.png");
	must_init(reloj, "reloj.png");

	//Funcionalidad fuentes de texto
	//***************************************************
	al_init_font_addon();
	must_init(al_init_ttf_addon(), "ttf addon");

	ALLEGRO_FONT *ASCII;
	ASCII = al_load_font("cour.ttf", 13, NULL);
	must_init(ASCII, "cour.ttf");
	
	ALLEGRO_FONT *minecraft;
	minecraft = al_load_font("minecraft.ttf", 20, NULL);
	must_init(minecraft, "minecraft.ttf");

	ALLEGRO_FONT *minecraftSmall;
	minecraftSmall = al_load_font("minecraft.ttf", 15, NULL);
	must_init(minecraftSmall, "minecraft.ttf");


	//Funcionalidad dibujar objetos
	//***************************************************
	must_init(al_init_primitives_addon(), "primitives addon");

	//Funcionalidad del teclado
	//***************************************************
	ALLEGRO_KEYBOARD_STATE keystate;
	must_init(al_install_keyboard(), "keyboard");

	
	//Funcionalidad audios
	//***************************************************
	//must_init(al_install_audio(),"audio addon");
	//must_init(al_init_acodec_addon(), "codec addon");
	//al_reserve_samples(1);

	//ALLEGRO_SAMPLE *music;
	//music = al_load_sample("Light2.wav"); 
	//must_init(music,"music")

	//ALLEGRO_SAMPLE_ID id;
	//al_play_sample(musica, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &id);

	//Definición de los timers que se necesitarán para el juego
	//***************************************************
	ALLEGRO_TIMER *Timer1 = al_create_timer(1 / FPS);
	ALLEGRO_TIMER *TryChange = al_create_timer(1);
	ALLEGRO_TIMER *CreateBots = al_create_timer(1);

	//Creación de colas de eventos
	//***************************************************
	ALLEGRO_EVENT_QUEUE *changing_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE *timer_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE *bot_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE *exit_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE *keyboard_queue = al_create_event_queue();

	//Registro de los eventos en las colas de eventos
	//***************************************************
	al_register_event_source(changing_queue, al_get_timer_event_source(TryChange));
	al_register_event_source(timer_queue, al_get_timer_event_source(Timer1));
	al_register_event_source(bot_queue, al_get_timer_event_source(CreateBots));
	al_register_event_source(exit_queue, al_get_display_event_source(screen));
	al_register_event_source(keyboard_queue, al_get_keyboard_event_source());

	//Inicialización de los timers
	//***************************************************
	al_start_timer(Timer1);
	al_start_timer(TryChange);
	al_start_timer(CreateBots);

	//Inicialización de arrays
	//***************************************************


	//Creación de los eventos
	//***************************************************
	ALLEGRO_EVENT timer;
	ALLEGRO_EVENT exits;
	ALLEGRO_EVENT change;
	ALLEGRO_EVENT makebot;
	ALLEGRO_EVENT keypress;

	//Tiempo
	//*********************
	time_t inicio = time(NULL);

	//Ciclo del juego
	//***************************************************

	bool finito = false;
	while (!finito) {

		if (al_get_next_event(keyboard_queue, &keypress)) {
			if (keypress.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (!u_car.autopilot) {
					if (keypress.keyboard.keycode == ALLEGRO_KEY_L) {
						u_car.luces = !(u_car.luces);
					}
					if (keypress.keyboard.keycode == ALLEGRO_KEY_K) {
						u_car.AC = !(u_car.AC);
					}
				}
				if (autopilotconditions(u_car)) {
					if (keypress.keyboard.keycode == ALLEGRO_KEY_J) {
						u_car.autopilot = !(u_car.autopilot);
					}
				}
			}
		}


		//generar bots
		if (al_get_next_event(bot_queue, &makebot)) {
			initializeBot(botcar);
		}
		
		//randoms del clima
		if (randomint(0, 1000) == 10) {
			road.lluvia = !road.lluvia;
			u_car.lluvia = !u_car.lluvia;
		}
		if (randomint(0, 1000) == 10) {
			road.neblina = !road.neblina;
			u_car.neblina = !u_car.neblina;
		}

		//SENSORES

		//aceleración
		if (al_get_next_event(changing_queue, &change)) {
			u_car.aceleracion = (u_car.speed - u_car.velocidad_vieja) * 2;
			u_car.velocidad_vieja = u_car.speed;
		}

		//luces y AC bajan bateria
		if (u_car.luces) {//luces bajan bateria
			u_car.bateria -= 3;
		}
		if (u_car.AC) {//AC bajan bateria
			u_car.bateria -= 3;
		}

		//tiempo
		time_t fin = time(NULL);
		int tiempo = difftime(fin, inicio)*5 +420;
			
		//sensor dia y noche
		if (360 <= tiempo % 1440 < 1080) {//dia
			road.diaynoche = true;	
		}
		if ((tiempo % 1440 >= 1080) | (tiempo % 1440 < 360)) {//noche
			road.diaynoche = false;
		}

		//friccion

		if (checkRoad(u_car.pos_X, u_car.pos_Y) == false) {
			u_car.friccion = true;
		}
		if (checkRoad(u_car.pos_X, u_car.pos_Y) == true) {
			u_car.friccion = false;
		}

		//instruciones PILOTO AUTOMÁTICO
		/*if (u_car.speed > 12) {//PILOTO AUTOMATICO
			u_car.AC = true;
		}
		if (u_car.speed <= 12){//PILOTO AUTOMATICO
			u_car.AC = false;
		}

		if ((u_car.lluvia) | (u_car.neblina) | (u_car.diaynoche)) {//PILOTO AUTOMATICO
			u_car.luces = true;
		}
		if ((!u_car.lluvia) & (!u_car.neblina) & (u_car.diaynoche)) {//PILOTO AUTOMATICO
			u_car.luces = false;
		}*/


		al_wait_for_event(timer_queue, &timer);
		al_get_keyboard_state(&keystate);
		if (!u_car.autopilot) {
			if (al_key_down(&keystate, ALLEGRO_KEY_W) || al_key_down(&keystate, ALLEGRO_KEY_UP)) {
				accelerate(u_car, FORWARD, u_car.friccion);
			}
			if (al_key_down(&keystate, ALLEGRO_KEY_S) || al_key_down(&keystate, ALLEGRO_KEY_DOWN)) {
				accelerate(u_car, BACKWARD, u_car.friccion);
			}
			if (!(al_key_down(&keystate, ALLEGRO_KEY_W) || al_key_down(&keystate, ALLEGRO_KEY_UP)) && !(al_key_down(&keystate, ALLEGRO_KEY_S) || al_key_down(&keystate, ALLEGRO_KEY_DOWN))) {
				accelerate(u_car, 0, u_car.friccion);
			}
			if (al_key_down(&keystate, ALLEGRO_KEY_SPACE)) {
				accelerate(u_car, STOP, u_car.friccion);
			}
			if (al_key_down(&keystate, ALLEGRO_KEY_D) || al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) {
				rotate(u_car, RIGHT);
			}
			if (al_key_down(&keystate, ALLEGRO_KEY_A) || al_key_down(&keystate, ALLEGRO_KEY_LEFT)) {
				rotate(u_car, LEFT);
			}
			if (!(al_key_down(&keystate, ALLEGRO_KEY_D) || al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) && !(al_key_down(&keystate, ALLEGRO_KEY_A) || al_key_down(&keystate, ALLEGRO_KEY_LEFT))) {
				rotate(u_car, 0);
			}
		}if (u_car.autopilot) {
			lookaround(&bots[2]);
			automove(u_car);
		}

		if (road.diaynoche) {
			al_clear_to_color(al_map_rgb(200, 200, 200));
		}
		if (!road.diaynoche) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		updateBMP(bluecar, bluecarON);
		moveCar(u_car, screen);
		moveBots(); //moveBots OCUPA estar entre moveCar y moveMap
		moveMap(u_car.speed, u_car.angle);
		//drawboolMap(ASCII);
		drawMap(ASCII);
		drawCar(u_car);
		drawBots();
		inactivateBots();
		dibujarDash(u_car, minecraft, tiempo);
		al_draw_scaled_bitmap(brujula, -1, -1, 160, 160, 20, 30, 50, 50, NULL);
		al_draw_scaled_bitmap(reloj, -1, -1, 160, 160, 180, 30, 50, 50, NULL);
		dibujarMensajes(u_car, minecraftSmall);

		al_flip_display();

		if (al_get_next_event(exit_queue, &exits)) {
			if (exits.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				finito = true;
			}
		}
	}

	//	al_stop_sample(&id);
	//	al_destroy_sample(music);
	al_destroy_event_queue(timer_queue);
	al_destroy_event_queue(exit_queue);
	al_destroy_display(screen);
	al_destroy_timer(Timer1);
	al_destroy_font(ASCII);
	al_destroy_bitmap(bluecar);
	al_destroy_bitmap(botcar);
	return 0;
}
