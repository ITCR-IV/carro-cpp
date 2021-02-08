#pragma once

//30px = 1 metro


void reloj(int ptiempo, ALLEGRO_FONT*fuente) {
	char buffer[10];
	int minutos = ptiempo / 60;
	int segundos = ptiempo % 60;

	//si ha pasado un día completo
	if (ptiempo >= 1440) {
		minutos -= 24 * (ptiempo / 1440);
	}

	//imprimir los minutos
	sprintf(buffer, "%i", minutos);

	if (minutos < 10) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 105, 50, ALLEGRO_ALIGN_CENTRE, "0");
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 115, 50, ALLEGRO_ALIGN_CENTRE, buffer);
	}
	if (minutos >= 10) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 110, 50, ALLEGRO_ALIGN_CENTRE, buffer);
	}
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 50, ALLEGRO_ALIGN_CENTRE, ":");

	//imprimir los segundos
	sprintf(buffer, "%i", segundos);
	if (segundos < 10) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 135, 50, ALLEGRO_ALIGN_CENTRE, "0");
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 145, 50, ALLEGRO_ALIGN_CENTRE, buffer);
	}
	if (segundos >= 10) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 140, 50, ALLEGRO_ALIGN_CENTRE, buffer);
	}
}


void dibujarMensajes(car &car, ALLEGRO_FONT*fuente) {
	int pos = 470;
	if (!road.diaynoche | u_car.lluvia | u_car.neblina) {
		if (!u_car.luces) {
			al_draw_text(fuente, al_map_rgb(255, 240, 51), 125, pos, ALLEGRO_ALIGN_CENTER, "Enciende las luces");
			pos += 20;
		}
	}
	if (u_car.proxFrente > 0) {
		al_draw_text(fuente, al_map_rgb(255, 240, 51), 125, pos, ALLEGRO_ALIGN_CENTER, "Baja la velocidad");
		pos += 20;
	}
	if (u_car.speed > 12) {
		if (!u_car.AC) {
			al_draw_text(fuente, al_map_rgb(255, 240, 51), 125, pos, ALLEGRO_ALIGN_CENTER, "Enciende el Aire Condicionado");
			pos += 20;
		}
	}
	if (u_car.friccion) {
		al_draw_text(fuente, al_map_rgb(255, 240, 51), 125, pos, ALLEGRO_ALIGN_CENTER, "Entra a la carretera");
		pos += 20;
	}
	if (u_car.bateria / 1000 <= 50) {
		al_draw_text(fuente, al_map_rgb(255, 51, 51), 125, pos, ALLEGRO_ALIGN_CENTER, "Cuida de la bateria");
		pos += 20;
	}
	if (u_car.combustible / 1000 <= 50) {
		al_draw_text(fuente, al_map_rgb(255, 51, 51), 125, pos, ALLEGRO_ALIGN_CENTER, "Cuida del combustible");
		pos += 20;
	}
	pos = 550;
	if (!autopilotconditions(u_car)) {
		al_draw_text(fuente, al_map_rgb(178, 34, 34), 125, pos, ALLEGRO_ALIGN_CENTER, "Para activar el piloto automa-");
		pos += 12;
		al_draw_text(fuente, al_map_rgb(178, 34, 34), 125, pos, ALLEGRO_ALIGN_CENTER, "tico debe apuntar en la dirección");
		pos += 12;
		al_draw_text(fuente, al_map_rgb(178, 34, 34), 125, pos, ALLEGRO_ALIGN_CENTER, "correcta y estar en la calle");
	}
}

//1 velocidad 2 noche 3 lluvia 4 neblina 5 carro al frente 6 bateria 7 combustible

void dibujarDash(car &car, ALLEGRO_FONT*fuente, int tiempo) {
	//Forma
	al_draw_filled_rectangle(0, 0, 250, 600, al_map_rgb(0, 0, 0));
	al_draw_rectangle(5, 5, 250, 595, al_map_rgb(255, 51, 131), 10.0);
	al_draw_filled_rectangle(1078, 0, 1328, 600, al_map_rgb(0, 0, 0));
	al_draw_rectangle(1073, 5, 1322, 595, al_map_rgb(255, 51, 131), 10.0);
	char buffer[50];

	//lado izquierdo del dash
	//Reloj
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 30, ALLEGRO_ALIGN_CENTRE, "> Reloj <");
	reloj(tiempo, fuente);

	//indicadores
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 90, ALLEGRO_ALIGN_CENTER, "> Indicadores <");
	u_car.vi = (u_car.speed*7.2); //7.2 es el factor de conversión de px/fps a km/h
	sprintf(buffer, "%i", u_car.vi);
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 130, ALLEGRO_ALIGN_CENTER, "Velocidad (km/h)");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 150, ALLEGRO_ALIGN_CENTER, buffer);
	sprintf(buffer, "%.2f", u_car.aceleracion);
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 190, ALLEGRO_ALIGN_CENTER, "Aceleracion (m/s^2)");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 210, ALLEGRO_ALIGN_CENTER, buffer);
	sprintf(buffer, "%i", u_car.bateria / 1000);
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 250, ALLEGRO_ALIGN_CENTER, "Bateria");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 115, 270, ALLEGRO_ALIGN_CENTER, buffer);
	if ((u_car.bateria / 1000) < 100) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 135, 270, ALLEGRO_ALIGN_CENTER, "%");
	}
	if ((u_car.bateria / 1000) >= 100) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 145, 270, ALLEGRO_ALIGN_CENTER, "%");
	}
	sprintf(buffer, "%i", u_car.combustible / 1000);
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 310, ALLEGRO_ALIGN_CENTER, "Combustible");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 330, ALLEGRO_ALIGN_CENTER, buffer);
	if ((u_car.combustible / 1000) < 100) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 145, 330, ALLEGRO_ALIGN_CENTER, "%");
	}
	if ((u_car.combustible / 1000) >= 100) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 155, 330, ALLEGRO_ALIGN_CENTER, "%");
	}
	u_car.kilometraje += u_car.speed/30000; //30000px = 1 km
	sprintf(buffer, "%.2f", u_car.kilometraje);
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 370, ALLEGRO_ALIGN_CENTER, "Recorrido (km)");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 390, ALLEGRO_ALIGN_CENTER, buffer);

	al_draw_text(fuente, al_map_rgb(255, 255, 255), 125, 430, ALLEGRO_ALIGN_CENTER, "> Mensajes <");

	//lado derecho del dash
	//sensores
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 30, ALLEGRO_ALIGN_CENTER, "> Sensores <");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 70, ALLEGRO_ALIGN_CENTER, "LLuvia");
	if (u_car.lluvia) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 90, ALLEGRO_ALIGN_CENTER, "ON");
	}
	if (!u_car.lluvia) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 90, ALLEGRO_ALIGN_CENTER, "OFF");
	}
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 130, ALLEGRO_ALIGN_CENTER, "Neblina");
	if (u_car.neblina) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 150, ALLEGRO_ALIGN_CENTER, "ON");
	}
	if (!u_car.neblina) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 150, ALLEGRO_ALIGN_CENTER, "OFF");
	}
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 190, ALLEGRO_ALIGN_CENTER, "Friccion");
	if (u_car.friccion) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 210, ALLEGRO_ALIGN_CENTER, "ON");
	}
	if (!u_car.friccion) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 210, ALLEGRO_ALIGN_CENTER, "OFF");
	}
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 250, ALLEGRO_ALIGN_CENTER, "Hora del dia");
	if (road.diaynoche) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 270, ALLEGRO_ALIGN_CENTER, "Dia");
	}
	if (!road.diaynoche) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 270, ALLEGRO_ALIGN_CENTER, "Noche");
	}

	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 310, ALLEGRO_ALIGN_CENTER, "Proximidad");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 330, ALLEGRO_ALIGN_CENTER, "Frente");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 350, ALLEGRO_ALIGN_CENTER, "Izquierda");
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, 370, ALLEGRO_ALIGN_CENTER, "Derecha");

	//controles
	int pos = 410;
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "> Controles <");
	pos += 30;
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "Luces (L)");
	pos += 20;
	if (u_car.luces) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "ON");
	}
	if (!u_car.luces) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "OFF");
	}
	pos += 30;
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "Aire Condicionado (K)");
	pos += 20;
	if (u_car.AC) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "ON");
	}
	if (!u_car.AC) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "OFF");
	}
	pos += 30;
	al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "Piloto Automatico (J)");
	pos += 20;
	if (u_car.autopilot) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "ON");
	}
	if (!u_car.autopilot) {
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 1203, pos, ALLEGRO_ALIGN_CENTER, "OFF");
	}
}
