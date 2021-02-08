#pragma once


struct car {
	float pos_X = 750;
	float pos_Y = 300;
	float speed = 0;
	float resistance = 0;
	int angledir = 0;          //anglediff dicta hacia qué lado está girando (1=derecha, -1=izquierda, 0=no gira)
	double angle = pi/2;
	ALLEGRO_BITMAP* bmp = NULL;
	ALLEGRO_DISPLAY* backbuffer = NULL;
}; 



struct user_car :car {
	//sensores
	float velocidad_vieja = 0;
	int vi = 0;
	double aceleracion = 0;//afecta velocidad
	int bateria = 100000;//se gasta con ac, luces, velocidad
	int combustible = 100000;//se gasta al mover el carro
	bool friccion = false; //true si está fuera del camino, false si está dentro
	float kilometraje = 0;//distancia recorrida
	bool lluvia = false;
	bool neblina = false;
	bool luces = false;
	bool AC = false;//aire condicionado
	int proxIzquierda = 0;//debe haber una distancia minima de separacion a la derecha o izquierda
	int proxDerecha = 0;//si no detectan nada, es cero
	int proxFrente = 0;

	//piloto automático
	bool autopilot = false;
	Direction turn = STOP;
	bool stop = false;
	int maxspeed = 4;
}u_car; //u_car viene de user car

void accelerate(car &ucar,int direction, bool friccion) {	//direction determina si acelera hacia adelante (1) o atrás (-1) o no se acelera (0)
	if (direction == FORWARD) { //aceleración o frenos si está yendo en reversa
		u_car.combustible -= (abs(u_car.speed) / 2);
		if (ucar.speed > -0.4) {
			ucar.speed += 0.08;
			ucar.resistance = 0.005;
			if (friccion == true) {
				ucar.resistance = 0.03;
			}
		}
		else {
			ucar.resistance = 0.05;
		}
	}
	if (direction == BACKWARD) { //reversa o frenos si está yendo hacia delante
		u_car.combustible -= (abs(u_car.speed) / 2);
		if (ucar.speed < 0.4) {
			ucar.speed -= 0.08;
			ucar.resistance = 0.005;
			if (friccion == true) {
				ucar.resistance = 0.03;
			}
		}
		else {
			ucar.resistance = 0.05;
		}
	}
	if (direction == STOP) {  //frenos
		ucar.resistance = 0.06;
		if (fabs(ucar.speed) < 0.7) {
			ucar.speed = 0;
		}
	}
	if (direction == 0) {  //dejar soltar
		ucar.resistance=0.03;
		if (fabs(ucar.speed) < 0.2) {
			ucar.speed = 0;
		}
	}
	return;
}

void rotate(car &ucar, int orientation) {	//side determina si gira hacia la  derecha (1) o izquierda (-1) o no gira (0)

		if (orientation == RIGHT) {
			ucar.angledir = 1;
		}
		if (orientation == LEFT) {
			ucar.angledir = -1;
		}
		if (orientation == 0) {
			ucar.angledir = 0;
		}

	//este es para que cuando vaya en reversa sea consistente con como se comportan los carros reales
		if (ucar.speed < 0) {
			ucar.angledir = ucar.angledir*-1;
		}
	

	return;
}

void moveCar(car &ucar, ALLEGRO_DISPLAY * display) { //traduce todos los datos del carro como fricción, velocidad actual y si está doblando a movimiento real y al final lo dibuja

	//updetea velocidad del carro basado en velocidad y aceleración actual(desaceleración natural y frenos)
	//***************************************************************
	ucar.speed -= ucar.speed*ucar.resistance;
	//***************************************************************


	//NOTA: cudrantes de signo trigonométricos estan invertidos verticalmente (1cositas, 2tantas, 3sentimos, 4todos)

	//updetea posición del carro o mapa
	//***************************************************************
	switch (road.direction) {
		//ucar.pos_X += cos(ucar.angle)*ucar.speed;
		//ucar.pos_Y += sin(ucar.angle)*ucar.speed;
	case UP:
		ucar.pos_X += cos(ucar.angle)*ucar.speed;
		if (ucar.pos_Y <= (dim_Y/1.5) && sin(ucar.angle)*ucar.speed < 0 || (road.changing &&  sin(ucar.angle)*ucar.speed < 0)) {
			road.Y_displacement -= sin(ucar.angle)*ucar.speed;
			if (road.Y_displacement > 14) { 
				road.UPdisplacements = floor(fabs(road.Y_displacement) /14);   
				road.Y_displacement = remainder(road.Y_displacement, 14); }
		}
		else { ucar.pos_Y += sin(ucar.angle)*ucar.speed; }
		break;
	case DOWN:
		ucar.pos_X += cos(ucar.angle)*ucar.speed;
		if (ucar.pos_Y >= (dim_Y/3) && sin(ucar.angle)*ucar.speed > 0 || (road.changing && sin(ucar.angle)*ucar.speed > 0)) {
			road.Y_displacement -= sin(ucar.angle)*ucar.speed;
			if (road.Y_displacement < -14) { 
				road.DOWNdisplacements = floor(fabs(road.Y_displacement) / 14);
				road.Y_displacement = remainder(road.Y_displacement, 14); }
		}
		else { ucar.pos_Y += sin(ucar.angle)*ucar.speed; }
		break;
	case RIGHT:
		ucar.pos_Y += sin(ucar.angle)*ucar.speed;
		if (ucar.pos_X >= (dim_X/3) && cos(ucar.angle)*ucar.speed > 0 || (road.changing && cos(ucar.angle)*ucar.speed > 0)) {
			road.X_displacement -= cos(ucar.angle)*ucar.speed;
			if (road.X_displacement < -8) { 
				road.RIGHTdisplacements = floor(fabs(road.X_displacement) / 8);
				road.X_displacement = remainder(road.X_displacement, 8); }
		}
		else { ucar.pos_X += cos(ucar.angle)*ucar.speed; }
		break;
	case LEFT:
		ucar.pos_Y += sin(ucar.angle)*ucar.speed;
		if (ucar.pos_X <= (dim_X/1.5) && cos(ucar.angle)*ucar.speed < 0 || (road.changing && cos(ucar.angle)*ucar.speed < 0)) {
			road.X_displacement -= cos(ucar.angle)*ucar.speed;
			if (road.X_displacement > 8) { 
				road.LEFTdisplacements = floor(fabs(road.X_displacement) / 8);
				road.X_displacement = remainder(road.X_displacement, 8); 
			}
		}
		else { ucar.pos_X += cos(ucar.angle)*ucar.speed; }
		break;
	}

	//***************************************************************
	printf("speed: %f x: %f y: %f road: %d\n", u_car.speed, u_car.pos_X, u_car.pos_Y,checkRoad(u_car.pos_X,u_car.pos_Y));


	//updetea ángulo del carro
	//***************************************************************
	if (ucar.speed >= 2.5 || ucar.speed <= -2.5) {
		ucar.angle += degrees(ucar.angledir*(0.0035*pow(fabs(ucar.speed) - 30, 2)));
	}
	else {
		ucar.angle += degrees(ucar.angledir*(-0.4235*pow(fabs(ucar.speed) - 2.5, 2) + 2.6468));
	}
	//***************************************************************


	//Para detener al carro cuando llega a los bordes
	if (ucar.pos_X >= 1068 && cos(ucar.angle)*ucar.speed>0) {
		ucar.pos_X -= cos(ucar.angle)*ucar.speed;
	}
	if (ucar.pos_Y >= al_get_display_height(display) && sin(ucar.angle)*ucar.speed > 0) {
		ucar.pos_Y -= sin(ucar.angle)*ucar.speed;;
	}
	if (ucar.pos_X <= 260 && cos(ucar.angle)*ucar.speed < 0) {
		ucar.pos_X -= cos(ucar.angle)*ucar.speed;
	}
	if (ucar.pos_Y <= 0 && sin(ucar.angle)*ucar.speed < 0) {
		ucar.pos_Y -= sin(ucar.angle)*ucar.speed;
	}
}

void drawCar(car ucar){
	//dibuja al carro
	//***************************************************************
	al_draw_rotated_bitmap(ucar.bmp,26,23, ucar.pos_X, ucar.pos_Y, ucar.angle-pi/2, 0);
	//***************************************************************
}

void updateBMP(ALLEGRO_BITMAP* apagado, ALLEGRO_BITMAP* prendido) {
	if (u_car.luces) {
		u_car.bmp = prendido;
	}
	else {
		u_car.bmp = apagado;
	}
}
