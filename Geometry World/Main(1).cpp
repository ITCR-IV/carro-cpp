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


enum direction{UP=1,DOWN,RIGHT,LEFT,FORWARD=1,BACKWARD,STOP=5}; //up=1 down=2, right=3, left=4		forward=1, backward=2		stop=5

#include "User Car.h"
#include "Random ints.h"

using namespace std;
//Globales creación de variables globales
//**********************************************************
const int dim_Y = 600;
const int dim_X = 800;
const int lastY = floor(dim_Y / 20) * 20;
#define FPS 60.0

void must_init(bool test, const char *description) //función para inicializar cosas de allegro
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	al_show_native_message_box(NULL, "ERROR", "Error", "check console for more info", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	exit(1);
}

int main() {

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

	ALLEGRO_BITMAP *arrow = al_load_bitmap("yellowsmol.png");
	must_init(arrow, "yellow.png");

	u_car.bmp = arrow;
	//Funcionalidad fuentes de texto
	//***************************************************
	al_init_font_addon();
	must_init(al_init_ttf_addon(), "ttf addon");

	ALLEGRO_FONT *ASCII;
	ASCII = al_load_font("cour.ttf", 13, NULL);
	must_init(ASCII, "cour.ttf");

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

	//Creación de colas de eventos
	//***************************************************
	ALLEGRO_EVENT_QUEUE *timer_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE *keyboard_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE *exit_queue = al_create_event_queue();

	//Registro de los eventos en las colas de eventos
	//***************************************************
	al_register_event_source(timer_queue, al_get_timer_event_source(Timer1));
	al_register_event_source(keyboard_queue, al_get_keyboard_event_source());
	al_register_event_source(exit_queue, al_get_display_event_source(screen));

	//Inicialización de los timers
	//***************************************************
	al_start_timer(Timer1);

	//Inicialización de arrays
	//***************************************************


	//Creación de los eventos
	//***************************************************
	ALLEGRO_EVENT timer;
	ALLEGRO_EVENT exits;
	//	ALLEGRO_EVENT key;

		//Ciclo del juego
		//***************************************************

	//al_draw_text(ASCII, al_map_rgb(255, 255, 255), 20, 140, NULL, "WWWWWLLLLLLsdfsfsfsfasfsfLLL");
	//for (int c1 = 7; c1 <= 12; c1++) {
	//	for (int c2 = 20; c2 <= 300; c2 += c1) {
	//		al_draw_text(ASCII, al_map_rgb(255, 255, 255), c2, c1*20, NULL, "_");
	//	}
	//}

	//for(int c2=1; c2<=100;c2+=5)
	//for (int c1 = 1; c1 <= 500; c1 += 5) {
	//	al_put_pixel(c1, c2, al_map_rgb(255, 255, 255));
	//}

	bool finito = false;
	while (!finito) {


		//if (al_get_next_event(keyboard_queue, &key)) {
		//	if (key.type == ALLEGRO_EVENT_KEY_DOWN) {
		//		switch (key.keyboard.keycode) {
		//		}
		//	}
		//}

		al_wait_for_event(timer_queue, &timer);
		if (timer.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&keystate);
			if (al_key_down(&keystate, ALLEGRO_KEY_W) || al_key_down(&keystate, ALLEGRO_KEY_UP)) {
				accelerate(u_car, FORWARD);
			}if (al_key_down(&keystate, ALLEGRO_KEY_S) || al_key_down(&keystate, ALLEGRO_KEY_DOWN)) { 
				accelerate(u_car, BACKWARD);
			}if (!(al_key_down(&keystate, ALLEGRO_KEY_W) || al_key_down(&keystate, ALLEGRO_KEY_UP)) && !(al_key_down(&keystate, ALLEGRO_KEY_S) || al_key_down(&keystate, ALLEGRO_KEY_DOWN))) {
				accelerate(u_car, 0);
			}if (al_key_down(&keystate, ALLEGRO_KEY_SPACE)) {
				accelerate(u_car, STOP);
			}
			if (al_key_down(&keystate, ALLEGRO_KEY_D) || al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) {
				rotate(u_car, RIGHT);
			}if (al_key_down(&keystate, ALLEGRO_KEY_A) || al_key_down(&keystate, ALLEGRO_KEY_LEFT)) {
				rotate(u_car, LEFT);
			}
			if (!(al_key_down(&keystate, ALLEGRO_KEY_D) || al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) && !(al_key_down(&keystate, ALLEGRO_KEY_A) || al_key_down(&keystate, ALLEGRO_KEY_LEFT))) {
				rotate(u_car, 0);
			}


			move(u_car, screen);
			al_flip_display();
		}
		if (al_get_next_event(exit_queue, &exits)) {
			if (exits.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				finito = true;
			}
		}
	}


	//	al_stop_sample(&id);
	//	al_destroy_sample(music);
	al_destroy_event_queue(timer_queue);
	al_destroy_event_queue(keyboard_queue);
	al_destroy_event_queue(exit_queue);
	al_destroy_display(screen);
	al_destroy_timer(Timer1);
	al_destroy_font(ASCII);
	al_destroy_bitmap(arrow);
	return 0;
}