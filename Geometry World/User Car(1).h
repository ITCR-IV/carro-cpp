#pragma once
#include "angles.h"


struct car {
	float pos_X = 400;
	float pos_Y = 300;
	float speed = 0;
	float resistance = 0;
	int angledir = 0;          //anglediff dicta hacia qué lado está girando (1=derecha, -1=izquierda, 0=no gira)
	double angle = -pi/2;
	ALLEGRO_BITMAP* bmp = NULL;
	ALLEGRO_DISPLAY* backbuffer = NULL;
}; 

struct user_car :car {
}u_car; //u_car viene de user car

void accelerate(car &car,int direction) {	//direction determina si acelera hacia adelante (1) o atrás (-1) o no se acelera (0)
	if (direction == FORWARD) { //aceleración o frenos si está yendo en reversa
		if (car.speed > -0.4) {
			car.speed += 0.08;
			car.resistance = 0.005;
		}
		else {
			car.resistance = 0.05;
		}
	}
	if (direction == BACKWARD) { //reversa o frenos si está yendo hacia delante
		if (car.speed < 0.4) {
			car.speed -= 0.08;
			car.resistance = 0.005;
		}
		else {
			car.resistance = 0.05;
		}
	}
	if (direction == STOP) {  //frenos
		car.resistance = 0.06;
		if (fabs(car.speed) < 0.5) {
			car.speed = 0;
		}
	}
	if (direction == 0) {  //dejar soltar
		car.resistance=0.03;
		if (fabs(car.speed) < 0.2) {
			car.speed = 0;
		}
	}
	return;
}

void rotate(car &car, int orientation) {	//side determina si gira hacia la  derecha (1) o izquierda (-1) o no gira (0)

		if (orientation == RIGHT) {
			car.angledir = 1;
		}
		if (orientation == LEFT) {
			car.angledir = -1;
		}
		if (orientation == 0) {
			car.angledir = 0;
		}

	//este es para que cuando vaya en reversa sea consistente con como se comportan los carros reales
		if (car.speed < 0) {
			car.angledir = car.angledir*-1;
		}
	

	return;
}


void move(car &car, ALLEGRO_DISPLAY * display) { //traduce todos los datos del carro como fricción, velocidad actual y si está doblando a movimiento real y al final lo dibuja

	//updetea velocidad del carro basado en velocidad y aceleración actual(desaceleración natural y frenos)
	//***************************************************************
	car.speed -= car.speed*car.resistance;
	//***************************************************************




	//updetea posición del carro
	//***************************************************************
	car.pos_X += cos(car.angle)*car.speed;
	car.pos_Y += sin(car.angle)*car.speed;
	//***************************************************************
	printf("speed: %f x: %f y: %f \n", u_car.speed, u_car.pos_X, u_car.pos_Y);


	//updetea ángulo del carro
	//***************************************************************
	if (car.speed >= 2 || car.speed <=-2) {
		car.angle += degrees(car.angledir*(0.0035*pow(fabs(car.speed) - 30, 2)));}
	else{
		car.angle += degrees(car.angledir*(-0.686*pow(fabs(car.speed) - 2, 2) + 2.744));}
	//***************************************************************


	//Estas son temporales solo para probar todo, hacen que salga por el otro lado de la pantalla
	if (car.pos_X > al_get_display_width(display)) {
		car.pos_X = 1;
	}
	if(car.pos_Y > al_get_display_height(display)) {
		car.pos_Y = 1;
	}
	if (car.pos_X < 0) {
		car.pos_X = al_get_display_width(display)-1;
	}
	if (car.pos_Y < 0) {
		car.pos_Y = al_get_display_height(display)-1;
	}


	//dibuja al carro
	//***************************************************************
	al_clear_to_color(al_map_rgb(0, 0, 0));	
	al_draw_rotated_bitmap(car.bmp,19.5,15, car.pos_X, car.pos_Y, car.angle, 0);
	al_draw_filled_circle(car.pos_X, car.pos_Y, 2, al_map_rgb(250, 0, 0));
	//***************************************************************
}